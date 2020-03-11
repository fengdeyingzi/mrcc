
#include <mrc_base.h>
#include "mrc_android.h"
#include "mrc_graphics.h"
#include "xl_debug.h"

BITMAP_565 *readBitmap565FromAssets(char *filename){
 int32 len =0;
 uint16 *buf;
 debug_printf("开始读取文件");
 buf = mrc_readFileFromAssets(filename, &len);
 if(len>0){
	 debug_printf("解析图片");
  return bmp_read(buf,len);
 }
 return 0;
}

 BITMAP_565* readBitmap565(char *filename){
	 int32 len = mrc_getLen(filename);
	 if(len>0){
		int32 f= mrc_open(filename,1);
		char *buf = mrc_malloc(len);
		if(f>0){
		 mrc_read(f, &buf, len);
		 mrc_close(f);
		 return bmp_read(buf,len);
		}
		
		mrc_free(buf);
	 }
	 
	 
	 
	 return NULL;
 }
 int32 drawBitmap565Flip(BITMAP_565 *buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy){
	  bmp_drawflip(buf, x,y,w,h, sx, sy);
	  return 0;
 }
 void drawBitmap565(BITMAP_565 *b,int32 x,int32 y){
	 bmp_draw(b, x,y);
 }
 int32 bitmap565Free(BITMAP_565 *b){
	 bmp_free(b);
	 return 0;
 }



