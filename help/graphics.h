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
 
 /*
	将bitmap上(tx,ty,tw,th)区域缩放绘制到屏幕(x,y,w,h)区域上
	参数：
	x 绘制到屏幕上的x坐标
	y 绘制到屏幕上的y坐标
	w 绘制宽度
	h 绘制高度
	tx ty tw th 裁剪区域
*/
void drawBitmapEx(int32 b,int x,int y,int w,int h,int tx,int ty,int tw,int th);

 //绘制bitmap
 void drawBitmap(int b,int32 x,int32 y);
 //释放图片内存
 int32 bitmapFree(int b);

 //从工程目录assets文件夹读取图片
 int readBitmapFromAssets(char *filename);
 
 /*
 	绘制一个矩形
	参数：
	x,y 矩形坐标
	w,h, 矩形宽高
	color 矩形颜色(ARGB颜色值)
*/
	void drawRect(int x,int y,int w,int h,uint32 color);

/*
	
	绘制一个圆
	参数：
	x,y 圆的坐标
	r 圆的半径
	color 颜色值(ARGB格式)
*/
	void drawCir(int x,int y,int r,uint32 color);
 