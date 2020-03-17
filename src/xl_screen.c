#include <mrc_base.h>
#include "momo.h"
/*
用于解决屏幕适配问题
*/

static int screen_w,screen_h;

//设置屏幕虚拟分辨率
void scr_setScreenSize(int w,int h){
	screen_w = w;
	screen_h = h;
}

//获取屏幕虚拟宽度
int scr_getWidth(){
	return screen_w;
}

//获取屏幕虚拟高度
int scr_getHeight(){
	return screen_h;
}

//获取屏幕指定位置的虚拟坐标
int scr_getX(int x){
	return x*screen_w/SCREEN_WIDTH;
}

int scr_getY(int y){
	return y*screen_h/SCREEN_HEIGHT;
}