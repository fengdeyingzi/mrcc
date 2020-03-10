#include <mrc_base.h>
//#include <mrc_base_i.h>
#include "xl_debug.h"
#include <debug.h>
/*

EBUG_FILE
风的影子 用于调试
*/
void debug_printf(char *text){
	int32 f = 0;
	int32 len = 0;
	len = mrc_getLen(DEBUG_CHECK_FILE);
	mrc_clearScreen(240,240,240);
	mrc_drawText(text, 0,0, 20,20,20, 0, 1);
	mrc_refreshScreen(0,0,240,320);
	mrc_sleep(200);
	if(len>=0){
		f = mrc_open(DEBUG_FILE, 2);
		mrc_seek(f,0,MR_SEEK_END);
		mrc_write(f, text, mrc_strlen(text));
		mrc_write(f, "\r\n", 2);
		mrc_close(f);
	}
}