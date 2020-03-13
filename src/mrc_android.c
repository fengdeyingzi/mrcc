#include <mrc_base.h>
#include "xl_bmp.h"
#include "xl_debug.h"
#include "platform.h"

char *assets_dir;

//extern int32 mrc_getLen(const char* filename);

 char* getAssetsDir(void){
	return assets_dir;
}
 void setAssetsDir(char *dir){
	assets_dir = dir;
}

#ifdef C_RUN
void *mrc_readFileFromAssets(char *filename, int32 *len){
 int32 f = 0;
 char path[300];
 void *buf = NULL;
 mrc_sprintf(path,"%s/%s",getAssetsDir(),filename);
 debug_printf("¶ÁÈ¡assets");
 debug_printf(path);
 *len = (int32)mrc_getLen((const char*)path);
 buf = (void*)mrc_malloc(*len);
 f = mrc_open(path, 1);
 if(f>0){
 mrc_read(f, buf, *len);
 mrc_close(f);
 return buf;
 }
 return NULL;
}

void mrc_freeFileFromAssets(void *data,int32 len){
	mrc_free(data);
}

#else

void *mrc_readFileFromAssets(char *filename, int32 *len){
	uint8 *buf = NULL;
	int32 re = 0;
 re = mrc_readFileFromMrpEx(NULL,(const char*)filename,&buf,len,0);
 if(re == MR_SUCCESS){
	 return buf;
 }
 return NULL;
 //return mrc_readFileFromMrp((const char*)filename, len, 0);
}

void mrc_freeFileFromAssets(void *data,int32 len){
	//mrc_freeFileData(data,len);
	mrc_free(data);
}
#endif