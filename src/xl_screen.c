#include <mrc_base.h>
#include "momo.h"
/*
���ڽ����Ļ��������
*/

static int screen_w,screen_h;

//������Ļ����ֱ���
void scr_setScreenSize(int w,int h){
	screen_w = w;
	screen_h = h;
}

//��ȡ��Ļ������
int scr_getWidth(){
	return screen_w;
}

//��ȡ��Ļ����߶�
int scr_getHeight(){
	return screen_h;
}

//��ȡ��Ļָ��λ�õ���������
int scr_getX(int x){
	return x*screen_w/SCREEN_WIDTH;
}

int scr_getY(int y){
	return y*screen_h/SCREEN_HEIGHT;
}