#include <mrc_base.h>
#include "buffer.h"


//在字符串指定长度中搜索指定字符
char *strstr_x(char* text, int32 len, char *seText){
    char* ptr = text;
    int start = 0;
    int si = 0;
    int start_se = -1; //第一次搜到的结果
    int32 slen = strlen(seText);
    
    for(start = 0;start<len;start++){
        if(ptr[start] == seText[si]){
            for(si = 0;si<slen;si++){
                if(ptr[start+si] == seText[si]){
                    if(si == slen-1){
                        start_se = start;
                        return text+start_se;
                    }
                }
                else{
                    break;
                }
            }
        }
        else{
            si = 0;
        }
    }
    return NULL;
}

//http 获取当前行的值 并跳过空格 需要释放内存
char *getline_value(char *text){
    int start = 0;
    int end = 0;
    int i = 0;
    int32 len = strlen(text);
    int type = 0;
    char *temp = NULL;
    for(i = 0;i<len;i++){
        
        switch (type)
        {
        case 0:
            if(text[i] == ':'){
type = 1;
        }
            break;
        case 1:
        if(text[i] != ' '){
            start = i;
            type = 2;
        }
        break;
        case 2:
        if(text[i] == '\r' || text[i] == '\n'){
            end = i;
            goto line_out;
        }
        break;
        default:
            break;
        }
        
    }
    line_out:
    temp = malloc(end - start + 2);
    memset(temp,0,end - start + 2);
    memcpy(temp, text+start, end-start);
    return temp;
}

//判断Content-Length是否获取完成 
int32 isContentSuccess(char *text,int32 content_len){
    char *body = strstr(text,"\r\n\r\n");
    if(body){
        body += 4;
    }
    else{
        return FALSE;
    }
    if(strlen(body) >= content_len){
        mrc_printf("bodylen %d content_len %d\n",strlen(body),content_len);
        return TRUE;
    }
    return FALSE;
}

STRING_BUFFER* buffer_create(void){
    STRING_BUFFER *buffer = (STRING_BUFFER*) malloc(sizeof(STRING_BUFFER));
    memset(buffer,'\0',sizeof(STRING_BUFFER));
    buffer->data = (char*)malloc(MAX_BUFFER_LEN);
    memset(buffer->data,'\0', MAX_BUFFER_LEN);
    buffer->max = MAX_BUFFER_LEN;
    buffer->len = 0;
    buffer->header = buffer->data;
    return buffer;
}

int32 buffer_append(STRING_BUFFER* buffer, char c){
    if(buffer->len<buffer->max - 2){
        buffer->data[buffer->len] = c;
        buffer->len++;
        // printf("%s",buffer->data);
        return 0;
    }
    return -1;
}

int32 buffer_appendx(STRING_BUFFER* buffer, char *buf, int32 len){
    int i = 0;
    for(i=0;i<len;i++){
        buffer_append(buffer, buf[i]);
    }
    return -1;
}

int32 buffer_clear(STRING_BUFFER* buffer){
    buffer->len = 0;
    memset(buffer->data, 0, buffer->max);
    buffer->len = 0;
    buffer->body_len = 0;
    return 0;
}

int32 buffer_free(STRING_BUFFER* buffer){
    free(buffer->data);
    free(buffer);
    return 0;
}
