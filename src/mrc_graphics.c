
#include <mrc_base.h>
#include "mrc_android.h"
#include "mrc_graphics.h"
#include "xl_debug.h"
#include "mpc.h"
#include "platform.h"
/*
实现一些绘图函数
主要是实现bmp图片绘制

风的影子

*/
//将rgb888转rgb565
#define MAKECOLOR565(color) ((uint16)((color>>8)&0xf800) |  (uint16)((color>>5)&0x07e0) | (uint16)((color>>3)&0x1f))

BITMAP_565 *readBitmap565FromAssets(char *filename){
 int32 len =0;
 uint16 *buf;
 BITMAP_565* re = NULL;
 debug_printf("开始读取文件");
 
 buf = mrc_readFileFromAssets(filename, &len);
 if(len>0){
	 debug_printf("解析图片");
  re = bmp_read(buf,len);
  #ifdef C_RUN
  mrc_free(buf);
  #else
  //mrc_freeFileData(buf,len);
  mrc_free(buf);
  #endif
 }
 return re;
}

 BITMAP_565* readBitmap565(char *filename){
	 int32 f;
	 void *buf;
	 int32 len = 0;
	 BITMAP_565* re = NULL;
	 debug_printf("获取文件长度");
	 len = mrc_getLen(filename);
	 
	 if(len>0){
		 debug_printf("open");
		 f= mrc_open(filename,1);
		 debug_log("malloc %d", len);
		buf = mrc_malloc(len);
		if(buf==NULL){
			debug_log("申请内存失败");
		}
		if(f>0){
			debug_printf("read");
		 mrc_read(f, buf, len);
		 mrc_close(f);
		 debug_printf("bmp_read");
		 re = bmp_read(buf,len);
		}
		debug_printf("释放内存");
		mrc_free(buf);
	 }
	 
	 
	 
	 return re;
 }
 int32 drawBitmap565Flip(BITMAP_565 *buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy){
	  bmp_drawflip(buf, x,y,w,h, sx, sy);
	  return 0;
 }
 void drawBitmap565(BITMAP_565 *b,int32 x,int32 y){
	 bmp_draw(b, x,y);
 }
 
/*
将bitmap上(tx,ty,tw,th)区域缩放绘制到屏幕(x,y,w,h)区域上
参数：
x 绘制到屏幕上的x坐标
y 绘制到屏幕上的y坐标
w 绘制宽度 h 绘制高度 tx ty tw th 裁剪区域
*/
void drawBitmap565Ex(BITMAP_565* bmp,int32 x,int32 y,int32 w,int32 h,int32 tx,int32 ty,int32 tw,int32 th){
  int px,py; //屏幕区域坐标(相对)
  int32 pindex;
  //根据屏幕坐标计算出图片上的点
  for(px=0;px<w;px++){
   for(py=0;py<h;py++){
	pindex = bmp->width * (tx+py*th/h) + (ty+px*tw/w);
	if(pindex<bmp->width*bmp->height)
    mrc_drawPoint(px+x,py+y,*(bmp->bitmap + pindex));
    //*(getscrbuf() + (SCRW*(x+py)+(px+x))) = *(bmp->bitmap + bmp->width * (tx+py*th/h) + (ty+px*tw/w));
   }
  }
}
 
 int32 bitmap565Free(BITMAP_565 *b){
	 bmp_free(b);
	 return 0;
 }




//获取两点之间的长度 的平方
static int gl_getLineSize(int x,int y, int x2,int y2){
 return (x2-x)*(x2-x) + (y2-y)*(y2-y);
}

//混合两个颜色
int32 gl_getColor(int32 color1, uint32 color2){
 //printf("getColor %x %x\n",color1,color2);
  //int a1 = (color1>>24)&0xff;
  int r1 = (color1>>16)&0xff;
  int g1 = (color1>>8)&0xff;
  int b1 = color1&0xff;
  //printf("a1=%d r1=%d g1=%d b1=%d\n",a1,r1,g1,b1);
  //int a2 = (color2>>24)&0xff;
  int r2 = (color2>>16)&0xff;
  int g2 = (color2>>8)&0xff;
  int b2 = color2&0xff;
 // printf("a2=%d r2=%d g2=%d b2=%d\n",a2,r2,g2,b2);
  int draw_a = (color2>>24)&0xff;
  //int a = a1 * (255-draw_a)/255 + a2 * draw_a/255;
  int r = r1 * (255-draw_a)/255 + r2 * draw_a/255;
  //printf("drawa = %d\nr = %d + %d\n",draw_a, r1 * (255-draw_a)/255 , draw_a/255);
  int g = g1 * (255-draw_a)/255 + g2 * draw_a/255;
  int b = b1 * (255-draw_a)/255 + b2 * draw_a/255;
  //printf("a=%d,r=%d,g=%d,b=%d\n",a,r,g,b);
  return (0xff000000)|(r<<16) | (g<<8)|b;
}  

//画点 参数：x, y, argb
void gl_drawPoint(int x,int y,uint32 color){
 int32 scr_color=0;
 int32 o_color=0;
 uint16 scr_color16=0;
 //获取屏幕颜色
 if(x<0 || x>=SCRW)return;
 if(y<0 || y>=SCRH)return;
 scr_color16 = *(getscrbuf()+ (SCRW*y+x));
 scr_color = ((scr_color16<<8)&0xf80000) |  ((scr_color16<<5)&0xfc00) | (scr_color16<<3)&0xff;
 //混合
 o_color = gl_getColor(scr_color, color);
 //生成rgb565
 //*(getscrbuf()+ (SCRW*y+x)) = MAKECOLOR565(o_color);
 mrc_drawPoint(x,y, MAKECOLOR565(o_color));
 //*(((uint16*)getscrbuf())+ (SCRW*y+x)*2) = 0xffff;
 //printf("setzcolor %x\n",MAKECOLOR565(o_color));
}

//画矩形
void gl_drawRect(int32 x,int32 y,int32 w,int32 h,uint32 color){
 int ix,iy;
 for(ix=x;ix<x+w;ix++){
  for(iy=y;iy<y+h;iy++){
   gl_drawPoint(ix,iy,color);
  }
 }
}

//画圆
void gl_drawCir(int32 x,int32 y,int32 r,uint32 color){
 int ix,iy;
 
 
 for(ix=x-r;ix<x+r;ix++){
  for(iy=y-r;iy<y+r;iy++){
   if(gl_getLineSize(ix,iy, x,y)<= r*r){
    //考虑效率问题，不透明的圆单独处理
    
    if(color>>24==0xff){
     mrc_drawPoint(ix,iy, MAKECOLOR565(color));
    }
    else{
    gl_drawPoint(ix,iy, color);
    }
   }
  }
 }
 //printf("color>>24 = %d\n",color>>24);
}

int32 bitmap565getInfo(BITMAP_565* bmp, BITMAPINFO *info){
	mrc_memset(info,0, sizeof(BITMAPINFO));
	info->width = bmp->width;
	info->height = bmp->height;
	info->format = 16;
	info->ptr = bmp->bitmap;
	return 0;
}

