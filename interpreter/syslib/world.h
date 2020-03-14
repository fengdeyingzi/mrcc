#ifndef _STAGE_H_
#define _STAGE_H_

/*
世界  场景
做游戏专用
风的影子 制作
*/

typedef struct BODY
{
 int type; //类型 0图片 1精灵 2主角 3地图 4按钮 5文本 6菜单 7进度条  6窗口
 int sprite;
struct BODY *next;
int value;
} BODY;


typedef struct
{
 struct BODY *head; //世界中的物体
 struct BODY *end; //最后一个物体
 int camera;//照相机
 int value; //排序值
} WORLD;



		 /** @函数功能：单向链表排序
			   * @输入参数：指向链表头部的指针
			   *        注意：指向指针的指针可以修改指针的指向
			  * @输出参数：SORTSTATE 排序成功与否状态
			  */
		 static int sort(BODY ** chainhead)
		 {
			     BODY * head,                                    /* 当前比较接点的上一个接点 */
			          * first,                                    /* 当前比较接点 */
			          * second,                                    /* 当前参与比较的另一个接点 */
			          * end;                                        /* 当前比较接点的终点
				                                                      * 终点意味着从终点开始往后的
				                                                     * 链表排序已经确定，只需要将
				                                                    * 终点前的所有接点按照冒泡法
				                                                     * 排序，排序就将完成。
				                                                   */
			 BODY *temp;
			    if(*chainhead == NULL)                            /* 链表是否为空 */
			         return -1;
			     if((*chainhead)->next == NULL)                    /* 链表是否就只有一个接点 */
			          return 0;
			 
			     end = NULL;                                        /* 第一轮冒泡排序的终点接点值为NULL */
			     temp= *chainhead;
 
			     /* 冒泡法排序,可能有很多轮次 */
			     while(end != (*chainhead)->next){               
					 /* 如果排序的终点等于接点的第二个地址，
				    * 也就是说从第二个接点开始所有的接点
					  * 都已经按照从小到大的顺序确定了位置。
					  * 显然，剩下的唯一一个“第一接点”位置
					  * 也就确定了。所有排序全部完成。
					  */
				 
				         /* 首先比较位于头部的两个接点，由于位于头部，
					         * 与其他接点不一样,需要放在循环外边，单独处理。
					         */
				          first =   *chainhead;       /* 第一个比较接点是链表头部指向的接点 */
				         second = first->next;        /* 第二个比较接点是紧邻的第二个接点 */
				          
				        /* 是否需要更改链表的连接顺序 */
				         if(first->value > second->value){            
					              *chainhead = second;  /* 更改链表头部的指向 */    
					             /* 重新连接链表，就相当于对链表排序 */
					              first->next = second->next;            
					              second->next = first;            
					         }
				  
				         /* 移动比较接点到下两个接点 */
				          head = *chainhead;      /* 当前比较接点的上一个接点则是头部接点 */
				         first = head->next;    /* 当前比较接点 */
				          second = first->next;/* 当前参与比较的另一个接点 */
				          
				          while(second != end)    /* 此轮的比较是否结束 */
					          {
					              /* 是否需要更改链表的连接顺序 */
					              if(first->value > second->value){    
						                  /* 重新连接链表，就相当于对链表排序 */
						                  head->next = second;    
						                  first->next = second->next;
						                  second->next = first;
						                  
						              }
					              /* 移动比较接点到下两个接点 */
					              head = head->next;
					              first = head->next;
					              second = first->next;
					          }
				  
				          end = first;                                /* 一轮排序完成，结束接点位置上移一个 */
				      }
			  
			   return 0;                                   /* 排序成功 */
			}

//创建世界
int world_create()
{
 WORLD *world=malloc(sizeof(WORLD));
 memset(world,0,sizeof(WORLD));
 return (int)world;
}
/*
//为世界设置摄像机
int world_setCamera(int id,int camera)
{
 WORLD *world=(void*)id;
 world->camera=(void*)camera;
 
 return 0;
}
*/

//在世界里添加一个物体
int world_addBody(int id,int body)
{
 WORLD *world=(void*)id;
 BODY *bodynew=(void*)body;
// BODY *bodyhead=world->head;
 BODY *end=world->end;
 if(end==NULL)
 {
  end=bodynew;
  world->head=bodynew;
 }
 else
 {
 end->next=bodynew;
 world->end=bodynew;
 }
 
 
 
 return 0;
}

int world_addSprite(int id,int sprite)
{
 WORLD *world=(void*)id;
 BODY *body=malloc(sizeof(BODY));
 body->type=1;
 body->next=NULL;
 body->sprite=sprite;
 
 //printf("world_addSprite\n");
 
 if(world->end==NULL)
 {
  world->end=body;
  world->head=body;
 }
 else
 {
 world->end->next=body;
 world->end=body;
 }
 
 return 0;
}
//刷新世界end参数
static int world_ref(WORLD *world)
{
	BODY *temp=world->head;
	if(world->head==NULL)world->end=NULL;
while(temp!=NULL)
 {
	 if(temp->next==NULL)
	 {
   world->end=temp;break;
	 }
	 else
		 temp=temp->next;
 }
 return 0;
}
//删除一个精灵
int world_removeSprite(int id,int sprite)
{
 WORLD *world=(void*)id;
 BODY *body=world->head;
 BODY *temp;
 if(body==NULL)return -1;
 temp=body;
 //判断头部
 if(world->head==NULL) return -1;
 if(world->head->sprite==sprite)
 {
	 temp=world->head;
	 //判断删除的是否为end
	 if(temp==world->end)
	 {
		 world->end=NULL;
	 }
	 world->head=temp->next;
 }
 else
 {
   while(body->next)
   {
  	 //找到精灵
     if(body->next->sprite==sprite)
     {
	   temp=body->next;
	   body->next=body->next->next;
	   free(temp);
     }
     else
	   body=body->next;
   }
 //printf("world_addSprite\n");
 
 }
 world_ref(world);
 
 return 0;
}

int world_setCamera(int id,int camera)
{
 WORLD *world=(void*)id;
 world->camera=camera;
 return 0;
}

//显示世界
int world_draw(int id)
{
 WORLD *world=(void*)id;
 BODY *temp=world->head;
 while(temp!=NULL)
 {
 // printf("显示%d\n下一帧%d",(int)temp,(int)temp->next);
 sp_draw(temp->sprite,world->camera);
 temp=temp->next;
 
 }
 
 return 0;
}

//设置世界显示方式

int world_rank(int id,int type)
{
	WORLD *world=(void*)id;
 BODY *temp=world->head;
 while(temp!=NULL)
 {
 // printf("显示%d\n下一帧%d",(int)temp,(int)temp->next);
 SPRITE *sprite=(void*)temp->sprite;
 switch(type)
 {
	 case 0:
		 break;
	 case 1: //左上角
	  temp->value= (40000-sprite->y)*40000+(40000-sprite->x);
		 break;
		case 2: //左下角
		 temp->value= sprite->y*40000+(40000-sprite->x);
			break;
		case 3: //右上角
		 temp->value= (40000-sprite->y)*40000+sprite->x;
			break;
		case 4: //右下角
		 temp->value= sprite->y*40000+sprite->x;
			break;
	 
	 
 }

 temp=temp->next;
 
 }
 temp=world->head;
 sort(&temp);
 world->head=temp;
 while(temp!=NULL)
 {
	 if(temp->next==NULL)
	 {
   world->end=temp;break;
	 }
	 else
		 temp=temp->next;
 }
 return 0;
}

//世界逻辑
int world_run(int id)
{
 WORLD *world=(void*)id;
 BODY *temp=world->head;
 while(temp!=NULL)
 {
 // printf("显示%d\n下一帧%d",(int)temp,(int)temp->next);
 sp_run(temp->sprite);
 temp=temp->next;
 
 }
 
 return 0;
 
}


//检测x y 坐标是否点中世界里的物体，如果点中，返回被点中的物体

//检测世界内精灵是否与指定精灵发生碰撞，如果发生碰撞，返回碰撞的物体

//销毁世界
//销毁世界并不会销毁摄像机，精灵，它们需要单独销毁
int world_free(int id)
{
 WORLD *world=(void*)id;
 BODY *item=world->head;
 BODY *temp;
 while(item!=NULL)
 {
  temp=item->next;
  free(item);
  item=temp;
 }
 free(world);
 return 0;
}







#endif
