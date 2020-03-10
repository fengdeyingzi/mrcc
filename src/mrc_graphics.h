#ifndef _MRC_GRAPHICS_H_
#define _MRC_GRAPHICS_H_


#include "xl_bmp.h"
extern BITMAP_565* readBitmap(char *filename);
extern int32 drawBitmapFlip(BITMAP_565 *buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
extern void drawBitmap(BITMAP_565 *b,int32 x,int32 y);
extern int32 bitmapFree(BITMAP_565 *b);
extern BITMAP_565 *readBitmapFromAssets(char *filename);

#endif