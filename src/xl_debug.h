#ifndef _DEBUG_H_
#define _DEBUG_H_

//用于调试
#define DEBUG_FILE "debug.txt"
#define DEBUG_CHECK_FILE "风的影子"

extern void debug_printf(char *text,...);
#define debug_log(...) \
	do{\
		int32 h31415926len;\
		char msgBuffer[256] = {0};\
		int32 h31415926 = mrc_open("debug.txt", MR_FILE_CREATE|MR_FILE_WRONLY);\
		if (h31415926)\
		{\
			char *p = msgBuffer; \
			mr_datetime t; \
			mrc_getDatetime(&t); \
			h31415926len = sprintf(msgBuffer, "[%d/%02d/%02d %02d:%02d]\r\n", t.year, t.month, t.day, t.hour, t.minute); \
			mrc_seek(h31415926, 0, MR_SEEK_END);\
			p = msgBuffer + h31415926len; \
			h31415926len += sprintf(p, __VA_ARGS__);\
			mrc_write(h31415926, msgBuffer, h31415926len);\
			mrc_write(h31415926, "\r\n\r\n", 4);\
			mrc_close(h31415926);\
		}\
	}while(0)

#endif
