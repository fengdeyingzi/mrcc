#include <mrc_base.h>
#include "xl_debug.h"
#include <debug.h>
/*

EBUG_FILE
风的影子 用于调试
*/


#ifndef va_start
typedef char * va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (va_list)(&(v)) + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )


#endif

void debug_printf(char *text,...){
	int32 f = 0;
	int32 len = 0;
	char temp[500];
	va_list args; 
	
	len = mrc_getLen(DEBUG_CHECK_FILE);
	//mrc_clearScreen(240,240,240);
	//mrc_drawText(text, 0,0, 20,20,20, 0, 1);
	//mrc_refreshScreen(0,0,240,320);
	//mrc_sleep(200);
	if(len>=0){
		va_start(args, text);  
		mrc_sprintf(temp,text,args);
		va_end(args); 
		f = mrc_open(DEBUG_FILE, 2);
		mrc_seek(f,0,MR_SEEK_END);
		mrc_write(f, temp, mrc_strlen(temp));
		mrc_write(f, "\r\n", 2);
		mrc_close(f);
	}
}