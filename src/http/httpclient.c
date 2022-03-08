
#ifdef MTK_MOD
#include <mrc_base.h>
#include <mrc_network.h>
#elif defined(WIN32)
#define _WIN32_WINNT 0x0600
#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#include <pthread.h>
#elif defined(__linux__)
#include <fcntl.h>
#include <linux/tcp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#endif

// #include <errno.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>
// #include <unistd.h>

#include "array_state.h"
#include "buffer.h"
#include "httpclient.h"

#define PORT 80
#define SERVER_IP "111.123.50.143"
#define _BACKLOG_ 10

int32 net_init_type;

int32 send_len = 0;
// char *local_ip = "127.0.0.1";
int32 socket_state;	 // socket状态 0 gethost 1 connect 2 send 3 recv 4 ok -1

STRING_BUFFER *buffer_http;
HTTP_ONPROGRESS lis_progress;
HTTP_ONSUCCESS lis_onsuccess;
HTTP_ONERROR lis_onerror;
int32 timer_http;

int http_result;	   //与线程通信
int http_result_data;  //result内容
ARR_STATE *arr_websocket;

static HTTP_WEBSOCKET* websocket;

extern char *getHostByName(const char *host);
extern char *getUrlRoad(char *url);
extern char *getUrlHost(char *url);
int getUrlPort(char *url);
void timer_onHttpData(int32 data);
void http_ws_timer(int32 data);


int32 ip_htonl(int32 ip) {
	return ((ip >> 24) & 0xff) | ((ip >> 8) & 0xff00) | ((ip << 8) & 0xff0000) | ((ip << 24) & 0xff000000);
}
int32 str2ip(char *strip) {
	char temp[32];
	
	int type = 0;
	int i = 0;
	int start = 0;
	int len = 0;
	int32 temp_ip = 0;
	len = mrc_strlen(strip);
	mrc_strcpy(temp, strip);
	for (i = 0; i < len; i++) {
		switch (type) {
		case 0:
			if (temp[i] == '.' || i == len - 1) {
				temp[i] = 0;
				temp_ip |= mrc_atoi(temp + start);
				start = i + 1;
				if (i != len - 1)
					temp_ip = temp_ip << 8;
			}
			break;

		default:
			break;
		}
	}
	// mrc_printf("str2ip %s %x\n", strip, temp_ip);
	return temp_ip;
}



void send_result(int result_type, int32 ws, char *msg, int error) {
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	// RESULT_DATA *result_data = (RESULT_DATA *)malloc(sizeof(RESULT_DATA));
	// 
	// memset(result_data, 0, sizeof(RESULT_DATA));
	// result_data->result_type = result_type;
	// result_data->ws = ws;
	// if (msg != NULL) {
	// 	result_data->msg = malloc(strlen(msg) + 2);
	// 	strcpy(result_data->msg, msg);
	// }
	// result_data->error = error;
	// arr_add(arr_websocket, (int32)result_data);
	if(result_type == RESULT_WS_ONOPEN){
websocket->onOpen(ws);
	}else if(result_type == RESULT_WS_ONMESSAGE){
websocket->onMessage(ws, msg);
	}else if(result_type == RESULT_WS_ONCLOSE){
websocket->onClose(ws);
	}else if(result_type == RESULT_WS_ONERROR){
websocket->onError(ws, error);
	}

}

//读取2字节
static int readShort(char *data, int index) {
	return ((data[index] & 0xff) << 8) | (data[index + 1] & 0xff);
}
static int readInt(char *data, int index) {
	return ((data[index + 0] & 0xff) << 24) | ((data[index + 1] & 0xff) << 16) | ((data[index + 2] & 0xff) << 8) | (data[index + 3] & 0xff);
}
static long readLongLong(char *data, int index) {
	return ((data[index + 4] & 0xff) << 24) | ((data[index + 5] & 0xff) << 16) | ((data[index + 6] & 0xff) << 8) | (data[index + 7] & 0xff);
}

//读取指定长度byte 并在byte后添加\0 需要释放内存
char *readBytes(char *data, int index, int len) {
	char *readData = mrc_malloc(len + 2);
	readData[len] = 0;
	readData[len + 1] = 0;
	mrc_memcpy(readData, data + index, len);
	return readData;
}

//读取帧 需要释放内存
char *readFrame(HTTP_WEBSOCKET *websocket) {
	//1字节
	int total_len = 0;	//帧的总长度
	int ptr = 0;
	int FIN = 0;			   //1 bit
	int RSV1, RSV2, RSV3 = 0;  //共3bit
	int opcode = 0;			   //4 bit
	//2字节
	int mask = 0;		   //1 bit
	long payload_len = 0;  //7 bit | 7+16 bit | 7+64 bit
	int MaskingKey = 0;	   //0 | 4 bytes 掩码密钥，所有从客户端发送到服务端的帧都包含一个 32bits 的掩码（如果mask被设置成1），否则为0。一旦掩码被设置，所有接收到的 payload data 都必须与该值以一种算法做异或运算来获取真实值。
	char *payload_data;
	// char *extension_data;
	int extension_len = 0;
	char *data = websocket->buffer->data;
	if (websocket->buffer->len <= 2)
		return NULL;
	FIN = (data[0] & 0x80) >> 7;
	RSV1 = (data[0] & 0x40) >> 6;
	RSV2 = (data[0] & 0x20) >> 5;
	RSV3 = (data[0] & 0x10) >> 4;
	opcode = (data[0] & 0x8);
	mask = (data[1] & 0x80) >> 7;
	payload_len = (data[1] & 0x7f);
	ptr = 2;
	if (payload_len == 0x7e) {
		if (websocket->buffer->len <= ptr + 2)
			return NULL;
		//接下来的2字节
		payload_len = readShort(data, 2);
		ptr += 2;
	} else if (payload_len == 0x7f) {
		if (websocket->buffer->len <= ptr + 8)
			return NULL;
		//接下来的8字节
		payload_len = readLongLong(data, 2);
		ptr += 8;
	}
	if (mask == 1) {  //存在掩码
		total_len = (int)(ptr + 4 + payload_len + extension_len);
		if (websocket->buffer->len < total_len)
			return NULL;
		MaskingKey = readInt(data, ptr);
		ptr += 4;
	} else {
		total_len = (int)(ptr + payload_len + extension_len);
		if (websocket->buffer->len < total_len)
			return NULL;
	}
	//读取数据
	payload_data = readBytes(data, ptr, (int)payload_len);
	buffer_clear(websocket->buffer);  //读取一帧成功 丢弃帧

	return payload_data;
}




void print_ip(int32 ip) {
	unsigned char *data = (unsigned char *)&ip;
	mrc_printf("ip:%d.%d.%d.%d\n", data[3], data[2], data[1], data[0]);
}

//通过url获取host 需free
char *getUrlHost(char *url) {
	int len = mrc_strlen(url);
	char *host = mrc_malloc(len);
	int i = 0;
	int type = 0;
	int start = 0;
	int end = len;
	mrc_memset(host, 0, len);
	while (url[i]) {
		switch (type) {
		case 0:
			if (url[i] == ':') {
				type = 1;
			}
			break;
		case 1:
			if (url[i] == '/') {
				type = 2;
			} else {
				goto out_host;
			}
			break;
		case 2:
			if (url[i] == '/') {
				start = i + 1;
				type = 3;
			} else {
				goto out_host;
			}
			break;
		case 3:
			if (url[i] == '/' || url[i] == ':') {
				end = i;
				goto out_host;
			}
			break;
		default:
			break;
		}

		i++;
	}
out_host:
	if (start > 0 && end > 0) {
		mrc_memcpy(host, url + start, end - start);
		return host;
	}
	mrc_free(host);
	return NULL;
}

//通过url获取路由 需free
char *getUrlRoad(char *url) {
	int len = mrc_strlen(url);
	char *host = mrc_malloc(len);
	int i = 0;
	int type = 0;
	int start = 0;
	int end = len;
	memset(host, '\0', len);
	while (url[i]) {
		switch (type) {
		case 0:
			if (url[i] == ':') {
				type = 1;
			}
			break;
		case 1:
			if (url[i] == '/') {
				type = 2;
			} else {
				goto out_road;
			}
			break;
		case 2:
			if (url[i] == '/') {
				type = 3;
			} else {
				goto out_road;
			}
			break;
		case 3:
			if (url[i] == '/') {
				start = i;
				type = 4;
				goto out_road;
			}
			break;
		case 4:

			break;
		default:
			break;
		}
		if (i == len - 1) {
			start = -1;
			goto out_road;
		}
		i++;
	}
out_road:
	if (start > 0 && end > 0) {
		mrc_memcpy(host, url + start, len);
		return host;
	} else {
		mrc_memcpy(host, "/", 1);
		return host;
	}
	mrc_free(host);
	return NULL;
}

//通过url获取port 需free
int getUrlPort(char *url) {
	int len = mrc_strlen(url);

	int i = 0;
	int type = 0;
	int start = 0;
	// int end = len;
	int port = 80;

	while (url[i]) {
		switch (type) {
		case 0:
			if (url[i] == ':') {
				type = 1;
			}
			break;
		case 1:
			if (url[i] == '/') {
				type = 2;
			} else {
				goto out_road;
			}
			break;
		case 2:
			if (url[i] == '/') {
				type = 3;
			} else {
				goto out_road;
			}
			break;
		case 3:
			if (url[i] == ':') {
				start = i + 1;
				type = 4;
				// mrc_printf("atoi \n");
				port = mrc_atoi(url + start);
				goto out_road;
			} else if (url[i] == '/') {
				goto out_road;
			}
			break;
		case 4:

			break;
		default:
			break;
		}
		if (i == len - 1) {
			start = -1;
			goto out_road;
		}
		i++;
	}
out_road:

	return port;
}





int32 isNumber(char *host){
	int32 len = 0;
	int i;
	char c;
	len = mrc_strlen(host);
	for(i=0;i<len;i++){
		c = host[i];
		if((c>='0' && c<='9') || c=='.'){
			continue;
		}else{
			return FALSE;
		}
	}
	return TRUE;
}


//获取ip地址 并回调
int32 getHost(char *url, MR_GET_HOST_CB cb) {
	int32 re = 0;
	char *host = getUrlHost(url);
	char *road = getUrlRoad(url);
	websocket->socket_state = SOCKET_STATE_GETHOST;
	if (isNumber(host)) {
		websocket->socket_state = SOCKET_STATE_CONNECT;
		cb(str2ip(host));
	} else {
		re = mrc_getHostByName((const char *)host, cb);
		mrc_printf("getHost %s", url);
		// mrc_memset(websocket->send_buf, 0, websocket->recv_max);
		mrc_printf("host=%s road=%s", host, road);
		// mrc_sprintf(websocket->send_buf, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", road, host);

		mrc_printf("getHost 2");
		if (re == MR_FAILED) {
			//   drawInfo("getHostByName失败");
			// lis_onerror(HTTP_ERROR_HOST);
			websocket->onError((int32)websocket, HTTP_ERROR_HOST);
		} else {  //直接获取ip
			mrc_printf("getHost 3");
			cb(re);
		}
	}
  mrc_free(road);
  mrc_free(host);
  
  return re;
}

int32 http_ws_run(int32 ip) {
	
  

	// int timeout = 1000;
	// int i = 0;
    
	int32 temp_int = 0;
	int32 ret = 0;
	int32 state_=0;
	// char *temp_str;
	// int32 content_len = 0;
	// int32 temp_re = 0;
	// int isOpen = FALSE;
	// char *host = getUrlHost(websocket->url);
	// char *road = getUrlRoad(websocket->url);
	// int32 port = getUrlPort(websocket->url);

	// char *ipstr = getHostByName((const char *)host);
	// free(road);
	// free(host);
	int ii = 0;
	websocket->ip = ip;
	mrc_printf("http_ws_run %s\n", websocket->url);
	if (websocket->socket_state == SOCKET_STATE_GETHOST) {
		mrc_printf("mrc_gethost ....");
		websocket->socket = mrc_socket(MR_SOCK_STREAM, MR_IPPROTO_TCP);

		websocket->socket_state = SOCKET_STATE_CONNECT;
		 ret = mrc_connect(websocket->socket, ip, websocket->port, MR_SOCKET_BLOCK);
		if (ret == MR_WAITING) {
			mrc_printf("应用需要轮循");
		} else if (ret == MR_SUCCESS) {
			mrc_printf("连接成功");
			websocket->socket_state = SOCKET_STATE_CONNECT;
		} else {
			mrc_printf("连接失败");
			websocket->socket_state = SOCKET_STATE_ERROR;
		}
	}else if(websocket->socket_state == SOCKET_STATE_CONNECT){
		mrc_printf("connect....");
		 state_ = mrc_getSocketState(websocket->socket);
		if(state_ == MR_SUCCESS){
			websocket->socket_state = SOCKET_STATE_SEND;
		}else if(state_ == MR_FAILED){
			websocket->socket_state = SOCKET_STATE_ERROR;
		}
    
	}else if(websocket->socket_state == SOCKET_STATE_SEND){
		 ret = mrc_send(websocket->socket, websocket->send_buf, mrc_strlen(websocket->send_buf)-websocket->send_len);
		 mrc_printf("mrc_send.... %d", ret);
		if(ret == MR_FAILED){
			websocket->socket_state = SOCKET_STATE_ERROR;
		}else if(ret>0){
			websocket->send_len += ret;
		}
		if(websocket->send_len >= mrc_strlen(websocket->send_buf)){
			websocket->socket_state = SOCKET_STATE_SUCCESS;
			// send_result(RESULT_WS_ONOPEN, (int32)websocket, NULL, 0);
		}
	}else if(websocket->socket_state == SOCKET_STATE_SUCCESS){
		mrc_printf("mrc_recv ....");
		// char buf[4096] = {0};
		// mrc_printf("--while \r\n");
		
			 ret = mrc_recv(websocket->socket, websocket->recv_buf, websocket->recv_max);	//MSG_DONTWAIT MSG_WAITALL
			if(ret == MR_FAILED){
				websocket->socket_state = SOCKET_STATE_ERROR;
			}
			temp_int = ret;

		if (temp_int >= 0) {
			
			for ( ii = 0; ii < temp_int; ii++) {
				mrc_printf("读取数据 %d",temp_int);
				buffer_append(websocket->buffer, websocket->recv_buf[ii]);
				//判断header是否完成
				if (!websocket->is_open) {
					if (mrc_strstr(websocket->buffer->data, "\r\n\r\n")) {
						mrc_printf("header ... %s",websocket->buffer->data);
						mrc_clearScreen(240,240,240);
						mrc_drawText(websocket->buffer->data,0,0,20,20,20,0,1);
						mrc_refreshScreen(0,0,240,320);
						buffer_clear(websocket->buffer);
						websocket->is_open = TRUE;
						
						send_result(RESULT_WS_ONOPEN, (int32)websocket, NULL, 0);
					}
				} else {
					char *msgData = readFrame(websocket);
					if (msgData != NULL) {
						mrc_printf("--------- 读取帧成功 %s\n ", msgData);
						send_result(RESULT_WS_ONMESSAGE, (int32)websocket, msgData, 0);
						free(msgData);
					}else{
						mrc_printf("frame....");
					}
				}
			}

		} else {
			// mrc_printf("recv err\n");
			send_result(RESULT_WS_ONERROR, (int32)websocket, NULL, 0);
	
		}
	}

	 if(websocket->socket_state != SOCKET_STATE_ERROR){
		mrc_timerStart(websocket->timer, 200, ip, http_ws_timer, FALSE); 
	 }
	 

	



	
	
	


	return 0;
}

void http_ws_timer(int32 data){
	http_ws_run(data);
}

int32 http_ws(char *url, WS_ONOPEN onOpen, WS_ONMESSAGE onMessage, WS_ONCLOSE onClose, WS_ONERROR onError) {
	int len;
	char *road,*host;
	
	char *key = "puVOuWb7rel6z2AVZBKnfw==";
	HTTP_WEBSOCKET *ws = (HTTP_WEBSOCKET *)mrc_malloc(sizeof(HTTP_WEBSOCKET));
	websocket = ws;

	memset(ws, 0, sizeof(HTTP_WEBSOCKET));
	 len = mrc_strlen(url);
	mrc_printf("http_ws %d\n", 1);
	ws->url = mrc_malloc(len + 2);
	ws->recv_buf = mrc_malloc(1024*10);
	ws->recv_max = 1024*10;
	ws->send_buf = mrc_malloc(1024*10);
	
	mrc_strcpy(ws->url, url);
	mrc_printf("http_ws %d\n", 2);
	ws->buffer = buffer_create();
	mrc_printf("http_ws %d\n", 3);
	ws->port = getUrlPort(url);
	mrc_printf("http_ws %d\n", 4);
	host = getUrlHost(url);
	mrc_printf("http_ws %d\n", 5);
	road = getUrlRoad(url);
	mrc_printf("http_ws %d\n", 6);
	ws->socket_state = 1;
	ws->onOpen = onOpen;
	ws->onMessage = onMessage;
	ws->onClose = onClose;
	ws->onError = onError;
	
	ws->send_len = 0;
	mrc_printf("http_ws %d\n", 7);
	ws->key = mrc_malloc(strlen(key) + 2);
	mrc_strcpy(ws->key, key);
	mrc_printf("http_ws %d\n", 8);
	

	mrc_memset(ws->send_buf, '\0', ws->recv_max);

	mrc_sprintf(ws->send_buf, "GET %s HTTP/1.1\r\nConnection: Upgrade\r\nuser-agent: capp (mrcc:io)\r\nContent-Length: 0\r\nHost: %s:%d\r\nOrigin: null\r\nsec-websocket-extensions: permessage-deflate; client_max_window_bits\r\nSec-WebSocket-Key: %s\r\nSec-WebSocket-Version: 13\r\nUpgrade: websocket\r\n\r\n", road, host,ws->port, key);
	mrc_printf("send %s", ws->send_buf);
	mrc_free(road);
	mrc_free(host);
	ws->timer = mrc_timerCreate();
	getHost(url, http_ws_run);
	
	return (int32)ws;
}

void writeShort(char *data, int index, int num) {
	data[index] = (char)((num & 0xff00) >> 8);
	data[index + 1] = (char)(num & 0xff);
}

void http_ws_send(int32 ws, char *text) {
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	
	int isMask = 1;
	char maskKey[4] = {0x66, 0x66, 0x66, 0x66};
	char temp1, temp2;
	char *payloadData = text;
	char *sendData = NULL;
	int FIN = 1;  //1 bit
	int opencode = 1;
	int total_len = 0;
	int payload_len = 0;
	int ptr = 0;
	int i,count;
	int write_len;
	int mask;
	if (ws == 0)
		return;
	payload_len = mrc_strlen(payloadData);
	total_len = payload_len + 2;
	if (payload_len > 125) {
		total_len += 2;
	}
	if (isMask == 1) {
		total_len += 4;
	}
	sendData = mrc_malloc(total_len);
	sendData[ptr] = (char)((FIN << 7) | opencode);
	ptr += 1;
	 mask = 1;

	if (payload_len < 126) {
		sendData[ptr++] = (char)((isMask << 7) | payload_len);

	} else if (payload_len < 65536) {
		sendData[ptr++] = (char)((isMask << 7) | 126);
		writeShort(sendData, ptr, payload_len);
		ptr += 2;
	}
	if (isMask == 1) {
		sendData[ptr++] = maskKey[0];
		sendData[ptr++] = maskKey[1];
		sendData[ptr++] = maskKey[2];
		sendData[ptr++] = maskKey[3];
		for ( i = 0, count = 0; i < payload_len; i++) {
			temp1 = maskKey[count];
			temp2 = payloadData[i];
			sendData[ptr++] = (char)(((~temp1) & temp2) | (temp1 & (~temp2)));
			count++;
			if (count >= 4)
				count = 0;
		}

	} else {
		for ( i = 0; i < payload_len; i++) {
			sendData[ptr++] = payloadData[i];
		}
	}

	mrc_printf("----------- 发送 %s", text);
	// socket_w(sendData);
	//  write_len = writesocket(websocket->socket, sendData, total_len, 0);
	write_len = mrc_send(websocket->socket, sendData, total_len);
	if (write_len != total_len) {
		mrc_printf("write 未完成 %d\n", write_len);
	}else {
		mrc_printf("发送完成");
	}

	mrc_free(sendData);
}

//关闭websocket
void http_ws_exit(int32 ws) {
	
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	if (ws == 0)
		return;
	websocket->socket_state = 0;
	if (websocket->socket >= 0) {
		mrc_printf("关闭socket %d\n", websocket->socket);
		mrc_closeSocket(websocket->socket);
		websocket->socket = -1;
	}
	

	if (websocket->key) {
		free(websocket->key);
		websocket->key = NULL;
	}
	if (websocket->url) {
		free(websocket->url);
		websocket->url = NULL;
	}
	if (websocket->buffer) {
		buffer_free(websocket->buffer);
		websocket->buffer = NULL;
	}
	

	free(websocket);
	websocket = NULL;
	mrc_printf("ws exit ok\n");
}

