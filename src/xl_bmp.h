#ifndef _XL_BMP_H_
#define _XL_BMP_H_

/*
封装读取bmp图片
风的影子
由于mrp编译器会将bmp图片进行处理，所有mrp内部的bmp图片，采用非bmp后缀防止被编译，例如将bmp改成jpg
*/
#ifdef TCC
#include "base.h"
enum{
BM_OR,         //SRC .OR. DST*   半透明效果
   BM_XOR,        //SRC .XOR. DST*
   BM_COPY,       //DST = SRC*      覆盖
   BM_NOT,        //DST = (!SRC)*
   BM_MERGENOT,   //DST .OR. (!SRC)
   BM_ANDNOT,     //DST .AND. (!SRC)
   BM_TRANSPARENT,//透明色不显示，图片的第一个象素（左上角的象素）是透明色
   BM_AND,        //DST AND SRC
   BM_GRAY,        //灰度绘图， 相当于BM_TRANSPARENT＋灰度绘图 DST灰度 ＝ 30%R + 59%G + 11%B图片序号
   BM_REVERSE     //反向绘图，相当于BM_TRANSPARENT＋反向绘图（V1939）
   };
   #define mrc_bitmapShowFlip bmpshowflip
   #define mrc_bitmapShowExTrans bmpshowex
#else
#include <mrc_base.h>
#endif

typedef struct {
 uint16* bitmap;
 int width; //
 int height;
 int color_bit; //颜色位数 默认16
 int transcolor; //透明色 默认0xffff
 int mode; //绘制模式 默认BM_COPY
} BITMAP_565;


BITMAP_565* bmp_create(uint16 *bitmap, int width, int height, int transcolor);
int get_int(char *buf,int ptr);
BITMAP_565* bmp_read(void *buf, int len);
void bmp_settranscolor(BITMAP_565* bmp, int color);
void bmp_draw(BITMAP_565* bmp, int x,int y);
void bmp_drawflip(BITMAP_565* bmp, int x,int y,int w,int h,int tx,int ty);
void bmp_free(BITMAP_565* bmp);



#endif