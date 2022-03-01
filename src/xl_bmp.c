
#include <mrc_base.h>
#include "xl_debug.h"
#include "xl_bmp.h"

//构建一个bmp 参数：内存数据，宽度，高度，透明色(0表示不透明)
BITMAP_565* bmp_create(uint16 *bitmap, int width, int height, int transcolor){
 BITMAP_565* bmp = mrc_malloc(sizeof(BITMAP_565));
 memset(bmp, 0, sizeof(BITMAP_565));
 bmp->bitmap = bitmap;
 bmp->width = width;
 bmp->height = height;
 bmp->color_bit = 16;
 bmp->mode = BM_COPY;
 if(transcolor!=0){
  bmp->mode = BM_TRANSPARENT;
  bmp->transcolor = transcolor;
 }
 return bmp;
}

//读取一个低位int类型数字
int get_int(char *buf,int ptr){
 int num = (buf[ptr]&0xff) | (buf[ptr+1]<<8) | (buf[ptr+2]<<16) | (buf[ptr+3]<<24);
 return num;
}

static int get_short(char *buf,int ptr){
 int num = (buf[ptr]&0xff) | (buf[ptr+1]<<8);
 return num;
}

//读取bmp
BITMAP_565* bmp_read(void *buf, int len){
 char *bufc = (char*)buf;
 int ptr=0;
 int w=0,h=0;
 int bit=16; //bmp位数
 int bmpstart=0; //bmp数据位置
 int iy=0;
 int i=0;
 uint16 *buf16 = NULL;
 char *buf24 = NULL;
 int tcolor = 0;
 int wsize;
 int iw;
 BITMAP_565* bmp = mrc_malloc(sizeof(BITMAP_565));
 memset(bmp,0,sizeof(BITMAP_565));
 bmp->color_bit = 16;
 bmp->mode = BM_COPY;
//  debug_log("检测文件头");
//  debug_log("检测文件头 %c %c",*(bufc+1),*(bufc+2));
 //检测文件头
 if(bufc[0]=='B' && bufc[1]=='M'){
  // debug_log("BM\n");
  ptr = 10;
  bmpstart = get_int(bufc,ptr);
  // debug_printf("bmpstart\n");
  ptr = 18;
  w = get_int(bufc,ptr);
  ptr = 22;
  h = get_int(bufc,ptr);
  ptr = 28;
  bit = get_short(bufc,ptr);
  if(bit == 16){
  //  debug_printf("16位图\n");
   ptr = bmpstart;
   bmp->width = w;
   bmp->height = h;
   bmp->bitmap = (uint16*)mrc_malloc(w*h*2);
   //复制位图数据
   
   for( iy=0;iy<bmp->height;iy++){
    mrc_memcpy(bmp->bitmap+iy*bmp->width, bufc+ptr+(bmp->height-1-iy)*bmp->width*2, w*2);
    // mrc_printf("复制位图数据%d %d\n",iy, bmp->height-1-iy);
   }
   
  }
  else if(bit == 24){
  //  debug_printf("当前位图是24位");
   ptr = bmpstart;
   bmp->width = w;
   bmp->height = h;
   //对齐字节
   wsize = w*3;
   if(wsize%4!=0) wsize = wsize - wsize%4 + 4;
  //  debug_printf("申请内存\n");
   bmp->bitmap = (uint16*)mrc_malloc(w*h*3);
   //32转16位
    buf16 = (unsigned short*)mrc_malloc(bmp->width*bmp->height*2);
    buf24 = (bufc+ptr);
   for(i=0;i<h;i++){
	   for(iw=0;iw<w;iw++){
		   
    //BGRA
     tcolor = (((buf24[i*wsize+iw*3]>>3)&0x1f) 
    | ((buf24[i*wsize+iw*3+1]<<3)&0x7e0) 
    | ((buf24[i*wsize+iw*3+2]<<8)&0xf800));
    buf16[i*w+iw] = (uint16)(tcolor&0xffff);
	
	   }
   }
   //复制位图数据
    for(iy=0;iy<bmp->height;iy++){
		
     //debug_printf("复制数据 %d %d\n",iy,bmp->height-1-iy);
	 
     mrc_memcpy (bmp->bitmap + iy*bmp->width, buf16+(bmp->height-1-iy)*bmp->width,w*2);
   }
   mrc_free(buf16);
  }
 }
 else
 {
	 debug_printf("不是bmp图片");
  return NULL;
 }
//  debug_printf("返回bmp\n");
 return bmp;
}

//设置透明色 argb
void bmp_settranscolor(BITMAP_565* bmp, int color){
 bmp->transcolor = ((color>>8)&0xf800) | ((color>>5)&0x07e0) | ((color>>3)&0x1f);
 bmp->mode = BM_TRANSPARENT;
}
//显示bmp
void bmp_draw(BITMAP_565* bmp, int x,int y){
//  mrc_printf("bmpdraw %d \n",bmp->width);
 mrc_bitmapShowExTrans(bmp->bitmap, (int16)x,(int16)y, (uint16)bmp->width, (uint16)bmp->width,(uint16)bmp->height, (uint16)bmp->mode, 0,0,(uint16)bmp->transcolor);
}
//区域显示bmp
void bmp_drawflip(BITMAP_565* bmp, int x,int y,int w,int h,int tx,int ty){
//  mrc_printf("bmpshowflip width=%d w=%d\n",bmp->width,w);
 mrc_bitmapShowExTrans(bmp->bitmap, (int16)x, (int16)y, (uint16)bmp->width, (uint16)w,(uint16)h, (uint16)bmp->mode, (int16)tx,(int16)ty,(uint16)bmp->transcolor);
}
//bmp释放
void bmp_free(BITMAP_565* bmp){
 mrc_free(bmp->bitmap);
 mrc_free(bmp);
}