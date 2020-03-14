#ifndef _ACTION_H_
#define _ACTION_H_

#include "picture.h"

//动作 包含多帧画面
typedef struct
{
 PICTURE *picture[30]; //画面
 char *name; //动作名称
 int offset; //当前所处的帧
 int size;//帧数
 int id;//id
 int global; //引用数 除当前动作以为其余的引用数量，释放动作时，若引用数归0，那么释放本身
 int mode; //动画播放模式 0普通模式 1循环模式
// int w; //宽度
// int h; //高度(无太大意义)
// int rotate; //旋转
// int alpha; //透明度
} ACTION;

//创建一张空白动作
ACTION *ac_new()
{
 ACTION *ac=malloc(sizeof(ACTION));
 memset(ac,0,sizeof(ACTION));
 
 return ac;
}

/*
//创建一个动作 参数：id 所有帧 帧数 
ACTION *ac_create(int id, PICTURE *pic, int size)
{
 ACTION *ac=malloc(sizeof(ACTION));
 memset(ac,0,sizeof(ACTION));
 ac->picture=pic;
 ac->size=size;
 
 return ac;
};
*/



//给动作添加一帧画面
int ac_add(ACTION *action, PICTURE *picture)
{
 action->picture[action->size++]=picture;
 return 0;
}

//设置动作id
int ac_setId(ACTION *ac,int id)
{
 if(ac==NULL)return -1;
 ac->id=id;
 return 0;
}
//设置动作名称
int ac_setName(ACTION *ac,char *name)
{
 if(ac==NULL)return -1;
 ac->name=malloc(strlen(name)+1);
 strcpy(ac->name,name);
 
 return 0;
}

//设置播放模式
int ac_setPlayMode(ACTION *ac,int mode)
{
	if(ac==NULL)return -1;
	ac->mode=mode;
	return 0;
}

//绘制动作(自动跳转到下一帧)
void ac_draw(int bitmap,ACTION *ac,int x,int y)
{
 //printf("绘制动作\n");
 pic_draw(bitmap,ac->picture[ac->offset],x,y);

 // printf("绘制画面 %d/%d\n",ac->offset,ac->size) ;
}

void ac_run(ACTION *ac)
{
 ac->offset++;
 if(ac->offset>=ac->size)
  {
		switch(ac->mode)
		{
			case 0:
				ac->offset=ac->size-1;
				break;
			case 1:
			ac->offset=0;
			break;
		}

  }
}


ACTION *ac_copy(ACTION *ac)
{
	int i;
 ACTION *new_ac=malloc(sizeof(ACTION));
 memcpy(new_ac,ac,sizeof(ACTION));
 //复制画面
 
 for(i=0;i<ac->size;i++)
 {
  new_ac->picture[i]=pic_copy(ac->picture[i]);
 }
 return new_ac;
}

//销毁动作
int ac_free(ACTION *ac)
{
 int i;
 if(ac==NULL)return -1;
 if(ac->global>0) //如果存在其它引用，那么不销毁
 {
  ac->global--;
//  printf("action释放引用\n");
 }
 else
 {
 //先销毁画面
  for(i=0;i<ac->size;i++)
  {
  pic_free(ac->picture[i]);
  }
 //销毁字符串
 if(ac->name!=NULL)
 free(ac->name);
// printf("销毁action\n");
 free(ac);
 }
 return 0;
}




#endif



