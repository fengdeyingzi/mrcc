
#ifndef _SPRITE_H_
#define _SPRITE_H_


//#include "graphics.h"
//#include "ex_math.h"
#include "camera.h"
#include "action.h"

/*
精灵
做游戏专用
风的影子 编写
*/


typedef struct {
    int x;
    int y;
    int w;
    int h;
} _RECT;


//精灵 包含多个动作
typedef struct {
    int x; //屏幕坐标
    int y;
    int w; //精灵宽度
    int h;
    int bitmap;//图片资源
    ACTION *action[60];//动作数组
    int cx;  //显示中心点
    int cy;
    int id; //精灵id
    int offset;//当前所处的动作
    int size; //动作的数量
    int gravity; //显示方式
    int isdraw; //显示/隐藏

} SPRITE;
enum GRAVITY {
    _center,
    _left,
    _right,
    _top,
    _bottom
};

extern int sp_new(void);

/*
//加载精灵文件，参数：Sprite文件，bitmap
SPRITE *sp_read(char *filename, int bitmap)
{
 SPRITE *sp=sp_new();
 
 
 return sp;
};

*/




//给精灵添加动作
int sp_add(int id, ACTION *action) {
    SPRITE *sprite = (void *) id;

    sprite->action[sprite->size++] = action;

    return 0;
}

//通过图片创建精灵
SPRITE *sp_bitmapcreate(int bitmap, int width, int height) {
    // int bitmap=readBitmapFromAssets(filename);
	SPRITE *sprite = NULL;
	ACTION *action = NULL;
	int x, y;
    BITMAPINFO picinfo;
    bitmapGetInfo(bitmap, &picinfo);
    //创建精灵
    sprite = (SPRITE *) sp_new();
    sprite->bitmap = bitmap;
    // printf("\n");
    //创建动作
    action = ac_new();
    //printf("\n");
    
    for (y = 0; y < picinfo.height; y += height)
        for (x = 0; x < picinfo.width; x += width) {

            //创建rect
            RECTFLIP *rect = rect_create(0, 0, x, y, width, height);
            // printf("创建rect\n");
            //创建画面
            PICTURE *picture = pic_new();
            // printf("创建picture\n");
            //将rect添加到画面
            pic_add(picture, rect);
            //printf("将rect添加\n");
            //将画面添加到动作
            ac_add(action, picture);
            //printf("将picture添加\n");
        }
    //将动作添加到精灵
    sp_add((int) sprite, action);
    // printf("精灵完成\n");





    return sprite;
}

//新建一个精灵
int sp_new(void) {
    SPRITE *sprite = malloc(sizeof(SPRITE));
    memset(sprite, 0, sizeof(SPRITE));
    // printf("offset=%d\n",sprite->offset);
    return (int) sprite;
}

//创建精灵
SPRITE *sp_create(ACTION *action, int size) {
    SPRITE *sprite = malloc(sizeof(SPRITE));
    int i;
    for (i = 0; i < 10; i++)
        sprite->action[i] = action;
    sprite->id = -1;
    sprite->x = 0;
    sprite->y = 0;
    sprite->offset = 0;
    sprite->size = size;


    return sprite;
}

//通过加载一张图片完成精灵创建
//参数：精灵id，精灵宽度 高度
/*
int sp_createsprite(char *filename,int width,int height)
{
 int bitmap=readBitmapFromAssets(filename);
 int temp;
 int x,y;
 
 
 SPRITE *sprite=sp_new();
 sprite->bitmap=bitmap;
 ACTION *action = malloc(sizeof(ACTION));
 sprite->action[0]=action;
// action->rotate=0;
// action->alpha=255;
// action->type=0;
// action->w=width;
// action->h=height;
 sprite->offset=0;
 sprite->size=1;
 
 BITMAPINFO picinfo;
bitmapGetInfo(bitmap,&picinfo);
int size=0;
//如果裁剪图片和当前图片尺寸相等，就返回原图片

if(width==picinfo.width && height==picinfo.height)
{
 action->size=1;
 action->bitmap[size]=bitmap;
 return (int)sprite;
}
 for(y=0;y<picinfo.height;y+=height)
 for( x=0;x<picinfo.width;x+=width)
 {
  temp=clipBitmap(bitmap, x,y,width,height);
 // printf(" 裁剪图片 %d %d %d %d \n",x,y,width,height);
  action->bitmap[size]=temp;
  size++;
 }
 
// action->size=1;
// action->bitmap[size]=bitmap;
 bitmapFree(bitmap);
 return (int)sprite;
}
*/

//输出rectflip(纵向计算rectflip坐标)
/*
void printf_rectf(int x,int y,int width,int height,int movex,int movey)
{
 int i;
 int ix=0,iy=0;
 while(ix<width)
 {
 while(iy<height)
 {
 printf("
   <picture
   >
      <rectflip
      x=\"%d\"
      y=\"%d\"
      width=\"%d\"
      height=\"%d\"
      px=\"%d\"
      py=\"%d\"
      />
   </picture>\n
      ",0,0,movex,movey,x+ix,y+iy);
 iy+=movey;
 }
 ix+=movex;
 }
}
*/

//设置精灵的图片
void sp_setBitmap(int id, int bitmap) {
    SPRITE *sprite = (void *) id;
    sprite->bitmap = bitmap;

}

//设置精灵显示/隐藏
int sp_setDraw(int id, int isdraw) {
    SPRITE *sprite = (void *) id;

    sprite->isdraw = isdraw;
    return 0;
}

int sp_isDraw(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->isdraw;
}


//获取精灵id
int sp_getId(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->id;
}


int sp_setId(int sprite, int id) {
    SPRITE *sp = (void *) sprite;
    sp->id = id;
    return 0;
}

int sp_getFrame(int id)//得到当前图像的帧序号
{
    SPRITE *sp = (void *) id;
    return sp->action[sp->offset]->offset;
}

//复制一个精灵
int sp_copy(int id) {
    int i = 0;
    SPRITE *sprite = (void *) id;

// if(sprite==NULL)return NULL;

    //复制精灵
    SPRITE *new_sprite = malloc(sizeof(SPRITE));
    memcpy(new_sprite, sprite, sizeof(SPRITE));
    //复制动作
    for (i = 0; i < sprite->size; i++) {

        new_sprite->action[i] = ac_copy(sprite->action[i]);

    }
    return (int) new_sprite;

}

//添加精灵的动作
//参数：精灵句柄，动作句柄
int sp_addAction(int sprite_ptr, int action_ptr) {
    SPRITE *sprite = (void *) sprite_ptr;
    sprite->action[sprite->size] = (void *) action_ptr;
    sprite->size++;
    return 0;
}

//设置精灵的动作
//参数：精灵句柄，动作id
int sp_setAction(int id, int ac_id) {

    SPRITE *sprite = (void *) id;

    if (sprite->size > ac_id) {
        sprite->offset = ac_id;
        sprite->action[ac_id]->offset = 0;
    }
    return 0;
}

//获取精灵的动作
int sp_getAction(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->offset;
}

//精灵移动
int sp_move(int id, int x, int y) {
    SPRITE *sprite = (void *) id;

    sprite->x += x;
    sprite->y += y;
    return 0;
}


int sp_setxy(int id, int x, int y) {
    SPRITE *sprite = (void *) id;

    sprite->x = x;
    sprite->y = y;
    return 0;
}

int sp_getx(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->x;
}

int sp_gety(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->y;
}

int sp_getWidth(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->w;

}

int sp_getHeight(int id) {
    SPRITE *sprite = (void *) id;

    return sprite->h;
}

//精灵是否被x y点中
int sp_impact(int id, int x, int y) {
    SPRITE *sprite = (void *) id;

    //ACTION *action = sprite->action[sprite->offset];
    if (x >= sprite->x && x < sprite->x + sprite->w && y >= sprite->y && y < sprite->y + sprite->h)
        return TRUE;
    return FALSE;
}

int isCollisionRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    //Logcat.e(""+x1 + " " + y1 + " " + w1+ " "  + h1+ " "  + x2+ " "  + y2+ " "  + w2+ " "  + h2);

    //当矩形1 位于矩形2 的左侧
    if (x1 > x2 && x1 >= x2 + w2) {
        return FALSE;
        //当矩形1 位于矩形2 的右侧
    } else if (x1 < x2 && x1 + w1 <= x2) {
        return FALSE;
        //当矩形1 位于矩形2 的上方
    } else if (y1 > y2 && y1 >= y2 + h2) {
        return FALSE;
        //当矩形1 位于矩形2 的下方
    } else if (y1 < y2 && y1 + h1 <= y2) {
        return FALSE;
    }

    //所有不会发生碰撞都不满足时，肯定就是碰撞了
    return TRUE;
}

//精灵碰撞事件
//参数：精灵1 精灵2
//返回值：TRUE碰撞 FALSE不碰撞
int sp_crash(int id1, int id2) {
    _RECT *sprite1 = (void *) id1;
    _RECT *sprite2 = (void *) id2;


    return isCollisionRect(sprite1->x, sprite1->y, sprite1->w, sprite1->h, sprite2->x, sprite2->y,
                           sprite2->w, sprite2->h);
}

//显示精灵
int sp_draw(int id, int ca) {
    SPRITE *sp = (void *) id;
    CAMERA *camera = (void *) ca;
    if (sp == NULL)return -1;
    if (sp->isdraw == FALSE)return 0;
// printf("绘制精灵\n");
// printf("%d \n",sp->bitmap);
// printf("%d \n", (int) sp->action[0]);
// printf("精灵x %d \n",sp->x);
// printf("照相机 x%d ",camera->x);
    if (camera == NULL)
        ac_draw(sp->bitmap, sp->action[sp->offset], sp->x, sp->y);
    else
        ac_draw(sp->bitmap, sp->action[sp->offset], sp->x - camera->x, (sp->y) - (camera->y));
    //if(sp->offset>=sp->size)sp->offset=0;
    return 0;
}

void sp_run(int id) {
    SPRITE *sp = (void *) id;

    if (sp == NULL)return;
    ac_run(sp->action[sp->offset]);
}


//销毁精灵
int sp_free(int id) {
    SPRITE *sprite = (void *) id;

    //printf(" 开始释放精灵 \n");
    //销毁动作
    int i;

    for (i = 0; i < sprite->size; i++) {
        //bitmapFree(sprite->action[i]->bitmap[0]);
        ac_free(sprite->action[i]);
    }
    free(sprite);
    //printf(" 精灵释放成功 \n");

    return 0;
}


#endif
