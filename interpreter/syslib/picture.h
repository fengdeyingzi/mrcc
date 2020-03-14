#ifndef _PICTURE_H_
#define _PICTURE_H_

#include "rectflip.h"


//画面 包含图片矩形区域(用于显示图片)和显示位置
typedef struct _PICTURE
{
 RECTFLIP *rect[30];//矩形区域
 int size; //矩形块数量
} PICTURE;

//新建一张空白画面
PICTURE *pic_new()
{
 PICTURE *pic=malloc(sizeof(PICTURE));
 memset(pic,0,sizeof(PICTURE));
 return pic;
}

//创建一张画面 参数：矩形区域，矩形块数量，
/*
PICTURE *pic_create(RECTFLIP *rects,int size)
{
 PICTURE *pic=malloc(sizeof(PICTURE));
// pic->rect=rects;
 pic->size=size;
 
 return pic;
};
*/

//给画面添加一个裁剪区域
int pic_add(PICTURE *picture, RECTFLIP *rect)
{
 picture->rect[picture->size++]= rect;
 return 0;
}

//显示一张画面，参数：bitmap，画面结构体，屏幕坐标
void pic_draw(int bitmap,PICTURE *pic,int x,int y)
{
 int i;
 
 for(i=0;i<pic->size;i++)
 {
 drawBitmapFlip(bitmap,x+pic->rect[i]->x, y+pic->rect[i]->y, pic->rect[i]->pw, pic->rect[i]->ph,  pic->rect[i]->px,pic->rect[i]->py );
  
 // printf("绘制画面%d %d %d %d \n",pic->rect[i]->px,pic->rect[i]->py,pic->rect[i]->pw,pic->rect[i]->ph);
  }
 //printf("画面绘制完成\n");
}

PICTURE *pic_copy(PICTURE *pic)
{
 int i;
 PICTURE *new_pic=malloc(sizeof(PICTURE));
 memcpy(new_pic,pic,sizeof(PICTURE));
 //复制rectflip
 
 for(i=0;i<pic->size;i++)
 {
  new_pic->rect[i]=rect_copy(pic->rect[i]);
  
 }
 return new_pic;
}


//销毁画面
int pic_free(PICTURE *pic)
{
	int i;
 if(pic==NULL)return -1;
 //首先销毁矩形区域
 
 for(i=0;i<pic->size;i++)
 {
  //释放结构体内存
  rect_free(pic->rect[i]);
  //跳转到下一个结构体指针
  
 }
 
 free(pic);
 return 0;
}

//释放画面



#endif
