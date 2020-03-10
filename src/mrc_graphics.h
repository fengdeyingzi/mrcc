#ifndef _MRC_GRAPHICS_H_
#define _MRC_GRAPHICS_H_


#include "xl_bmp.h"
extern BITMAP_565* readBitmap565(char *filename);
extern int32 drawBitmap565Flip(BITMAP_565 *buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
extern void drawBitmap565(BITMAP_565 *b,int32 x,int32 y);
extern int32 bitmap565Free(BITMAP_565 *b);
extern BITMAP_565 *readBitmap565FromAssets(char *filename);

#endif