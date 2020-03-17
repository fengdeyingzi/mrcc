
#ifndef _XL_SCREEN_H_
#define _XL_SCREEN_H_
/*
用于解决屏幕适配问题
*/


//设置屏幕虚拟分辨率
void scr_setScreenSize(int screen_w,int screen_h);

//获取屏幕虚拟宽度
int scr_getWidth();

//获取屏幕虚拟高度
int scr_getHeight();

//获取屏幕指定位置的虚拟坐标
int scr_getX(int x);

int scr_getY(int y);

//

#endif