
#ifndef _MAP_H_
#define _MAP_H_
/*
游戏地图
做游戏专用
风的影子 制作
*/
#include <mrc_base.h>
#include "mpc.h"

#include "camera.h"
#include "sprite.h"


typedef struct GAME_MAP
{
 int sprite[255];
 int *data; //数据
 
 int width; //横向图块数量
 int height; //纵向图块数量
 int item_w; //图块宽度
 int item_h; //图块高度
} GAME_MAP;


GAME_MAP *map_create(int w,int h,int item_w,int item_h)
{
 GAME_MAP *map=malloc(sizeof(GAME_MAP));
 memset(map,0,sizeof(GAME_MAP));
 map->data=malloc(w*h*4);
 memset(map->data,0,w*h*4);
 map->width=w;
 map->height=h;
 map->item_w=item_w;
 map->item_h=item_h;
 return map;
};


//为地图设置精灵
int map_setSprite(GAME_MAP *map, int id, int sprite)
{
 map->sprite[id]=(void*)sprite;
 return 0;
}

//设置data
int map_setData(GAME_MAP *map,int* data)
{
 memcpy(map->data, data, map->width*map->height*sizeof(int));
 return 0;
}

//设置地图上xy位置图块的属性
int map_setDataType(GAME_MAP *map, int x,int y,int type)
{
 map->data[map->width* y +x]=type;
 return 0;
}
//获取地图上xy位置图块的属性
int map_getDataType(GAME_MAP *map, int x,int y)
{
 
 
 return map->data[map->width*y +x];
}

//绘制地图
//参数：地图 照相机 

int map_draw(GAME_MAP *map,int ca)
{
 CAMERA *camera=(void*)ca;
 int i;
 int ix,iy;
 int width=map->width;
 int height=map->height;
 SPRITE *sprite=map->sprite;
 //计算x y方向需要绘制的区域以减少绘制量
 ix=camera->x/map->item_w;
 iy=camera->y/map->item_h;
 width=camera->w/map->item_w+1+ix;
 height=camera->h/map->item_h+1+iy;
 width= (width>map->width)?map->width:width;
 height= (height>map->height)?map->height:height;
// printf("%d %d %d %d\n", ix,iy,width,height);
 for(iy=0;iy<height;iy++)
  for(ix=0;ix<width;ix++)
  {
   int sp= (int)sprite[map->data[iy*map->width+ix]];
   if(sp!=NULL)
   {
   sp_setxy(sp,ix*map->item_w,iy*map->item_h);
   sp_draw(sp,ca);
   }
  }
 
 
 return 0;
}


//销毁地图
int map_free(GAME_MAP *map)
{
 free(map->data);
 free(map);
 return 0;
}



#endif
