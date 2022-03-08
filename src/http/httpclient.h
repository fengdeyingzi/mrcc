#ifndef __HTTPCLIENT_H__
#define __HTTPCLIENT_H__
#ifdef MTK_MOD
#include <mrc_base.h>
#include <mrc_network.h>
#elif defined(WIN32)
#define _WIN32_WINNT 0x0600
#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#endif
#include <mrc_base.h>
#include "buffer.h"
#include "array_state.h"

typedef void (*HTTP_ONPROGRESS)(int32 pos);
typedef void (*HTTP_ONSUCCESS)(char *ip, char *data, char *body);
typedef void (*HTTP_ONERROR)(int32 code);
typedef void (*test_test)(int32 data);

typedef void (*WS_ONOPEN)(int32 ws);
typedef void (*WS_ONMESSAGE)(int32 ws, char *msg);
typedef void (*WS_ONCLOSE)(int32 ws);
typedef void (*WS_ONERROR)(int32 ws, int err);

//数据缓冲区大小
#define BUFFER_MAX 1024 * 20

enum {
	SOCKET_STATE_NONE,
	SOCKET_STATE_GETHOST, //gethost
	SOCKET_STATE_CONNECT, //正在连接
	SOCKET_STATE_ERROR, //连接失败
	SOCKET_STATE_SEND, //发送头信息
	SOCKET_STATE_SUCCESS //socket通信中
};

enum {
	HTTP_ERROR_NETINIT,
	HTTP_ERROR_HOST,
	HTTP_ERROR_SOCKET,	//socket创建失败
	HTTP_ERROR_CONNECT,
	HTTP_ERROR_SEND,
	HTTP_ERROR_RECV
};

enum {
	HTTP_PROGRESS_CONNECT = -2,
	HTTP_PROGRESS_SEND = -1,
	HTTP_PROGRESS_HEAD = 0
};

enum {
	RESULT_WS_ONOPEN = 4,
	RESULT_WS_ONMESSAGE = 5,
	RESULT_WS_ONCLOSE = 6,
	RESULT_WS_ONERROR = 7
};

typedef struct HTTP_WEBSOCKET{
	char *url;
	int port;
	int socket;
	int socket_state; //socket状态
	int error; //错误状态码
	char *key;
	char *send_buf;
	char *recv_buf;
	int recv_max;
	int send_len;
	int32 timer;
	int32 is_open;
	// pthread_mutex_t lock;
	int32 ip;
    STRING_BUFFER *buffer;
	WS_ONOPEN onOpen;
	WS_ONMESSAGE onMessage;
	WS_ONCLOSE onClose;
	WS_ONERROR onError;
} HTTP_WEBSOCKET;

typedef struct {
	int result_type;
	int32 ws;
	char *msg;
	int error;
} RESULT_DATA;

void http_init(void);
void http_getData(char *url, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror);
void http_postData(char *url,char *data, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror);

//创建websocket客户端
int32 http_ws(char *url, WS_ONOPEN onOpen, WS_ONMESSAGE onMessage, WS_ONCLOSE onClose, WS_ONERROR onError);
void http_ws_send(int32 ws,char *text);
void http_ws_exit(int32 ws);
void http_exit(void);

#endif