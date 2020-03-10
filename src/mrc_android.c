#include <mrc_base.h>
#include "xl_bmp.h"
#include "xl_debug.h"

char *assets_dir;

//extern int32 mrc_getLen(const char* filename);

 char* getAssetsDir(void){
	return assets_dir;
}
 void setAssetsDir(char *dir){
	assets_dir = dir;
}


void *mrc_readFileFromAssets(char *filename, int32 *len){
 int32 f = 0;
 char path[300];
 void *buf = NULL;
 
 buf = (void*)mrc_malloc(*len);
 
 mrc_sprintf(path,"%s/%s",getAssetsDir(),filename);
 debug_printf("¶ÁÈ¡assets");
 debug_printf(path);
 *len = (int32)mrc_getLen((const char*)path);
 f = mrc_open(path, 1);
 if(f>0){
 mrc_read(f, buf, *len);
 mrc_close(f);
 return buf;
 }
 return NULL;
}