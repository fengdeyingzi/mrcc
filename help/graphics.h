/*
手机CAPP mrp版 头文件说明
graphics.h
注意：graphics.h只支持读取bmp图片格式，支持正常的bmp图片
目前仅支持16位与24位的bmp

风的影子 编写
*/

 //从内存卡读取bitmap 
 int readBitmap(char *filename);
 //裁剪绘制bitmap
 int32 drawBitmapFlip(int buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
 //绘制bitmap
 void drawBitmap(int b,int32 x,int32 y);
 //释放图片内存
 int32 bitmapFree(int b);

 //从工程目录assets文件夹读取图片
 int readBitmapFromAssets(char *filename);