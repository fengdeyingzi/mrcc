
#ifndef _RECTFLIP_H_
#define _RECTFLIP_H_


typedef struct
{
 int x;//显示在画面上的相对位置
 int y;
 int px;//bitmap裁剪区域
 int py;
 int pw;
 int ph;
 
 
} RECTFLIP;

RECTFLIP *new_rect()
{
 RECTFLIP *rect=mrc_malloc(sizeof(RECTFLIP));
 
 return rect;
}

//创建一个矩形裁剪块
RECTFLIP *rect_create(int x,int y,int px,int py,int pw,int ph)
{
 RECTFLIP *rect=malloc(sizeof(RECTFLIP));
 rect->x=x;
 rect->y=y;
 rect->px=px;
 rect->py=py;
 rect->pw=pw;
 rect->ph=ph;
 
 return rect;
}

RECTFLIP *rect_copy(RECTFLIP *rect)
{
 RECTFLIP *new_rect=malloc(sizeof(RECTFLIP));
 memcpy(new_rect,rect,sizeof(RECTFLIP));
 return new_rect;
}


//销毁矩形裁剪块
int rect_free(RECTFLIP *rect)
{
 if(rect==NULL)return -1;
 free(rect);
 return 0;
}







#endif
