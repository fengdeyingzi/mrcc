#ifndef _READSPRITE_H_
#define _READSPRITE_H_
#include "mpc.h"
#include "sprite.h"



//读取底层嵌套(只做解析，无意义)
char *readflip(char *text)
{
 int type=0;
 char c;
 while(*text)
 {
  c=*text;
 switch(type)
  {
   case 0: //读取左括号
   if(c=='<')
   type=1;
   
   
   case 1:
   
   
   case 2:
   
   
   case 3:
   
   
   case 4:
   case 8: //读取/
   if(c=='/')
   {
    type=10;
   }
   break;
   case 10: //读取最后>
   if(c=='>')
   {
    return text;
   }
   
  }
 
 text++;
 }
 return text;
}
//跳过头信息
static char *breakHead(char *text)
 {
  int type=0;
  int ptr=0;
  while(text[ptr])
  {
   switch(type)
   {
    case 0:
     if(text[ptr]=='<')
     {
      type=1;
     }
     break;
    case 1:
     if(text[ptr]=='>')
     {
      return text+ptr;
     }
     break;
    case 2:
     break;
    
   }
   ptr++;
  }
  return text+ptr;
 }

//读取rectflip层，返回读取后指针
char *readRectFlip(PICTURE *pic,char *text)
{
 int type=0;
 char c=0;
 char *head=NULL;
 char *item=NULL;
 char *word=NULL;
 char *start=NULL,*end=NULL;
 RECTFLIP *rect=NULL;
 while(*text)
 {
  c=*text;//printf("%c%d ",c,type);
  switch(type)
  {
   case 0://读取左括号
   if(c=='<')
   {
    type=-1;
    start=text+1;
    head=text+1;
   }
   break;
   case -1:
     if(c=='/')
     {
      //  if(Str.strcmp(text,i,"</"+head))


     return text-1; 
      type=10;
      text++;
      start=text;



     }
     else if(c=='!')
     {
      text=breakHead(text);
      type=0;
     }
     else if(c=='?')
     {
      text=breakHead(text);
      type=0;
     }
     else
     {
     type=1;
      }
break;
   
   case 1://读取头信息
   if(c>='0' && c<='z')
   {
    
   }
   else if(c=='>')//信息结束
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')//如果是上一个的括号。。。
   {
    
   }
   else
   {
    end=text;
    head=malloc((int)end-(int)start+1);
    strncpy(head, start,(int)end-(int)start);
    if(memcmp(head,"rectflip",8)==0)
    {
    rect=new_rect();
    pic_add(pic,rect);
    // printf("添加rect\n");
    type=3;
    }
    else
    {
   //  printf("读取rectflip失败\n");
     return text;
    }
   }
   break;
   case 2://读取空格或回车
   if(c==' ' || c=='\n' || c=='\t')
   {
    type=3;
   }
   else if(c=='>')
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')
   {
    type=10;
   }
   break;
   case 3://读取参数
   if(c>='a' && c<='z')
   {
    start=text;
    type=4;
   }
   else if(c=='>') //若遇到反括号，就跳转到下一层
   {
    
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')
   {
   type=10;
   }
   break;
   case 4://读取= 或空格
   if(c==' '|| c=='=')
   {
    end=text;
    item=start;
    type=5;
   }
   break;
   case 5://读取值
   if(c=='\"')
   {
    start=text+1;
    type=6;
   }
   break;
   case 6:
   if(c=='\"')
   {
    end=text;
    word=start;
    type=2;
    if(memcmp(item,"x",1)==0)
    {
     rect->x=atoi(word);
     //printf("rectflip x=%d\n",rect->x);
    }
    else if(memcmp(item,"y",1)==0)
    {
     rect->y=atoi(word);
    }
    else if(memcmp(item,"px",2)==0)
    {
     rect->px=atoi(word);
    }
    else if(memcmp(item,"py",2)==0)
    {
     rect->py=atoi(word);
    }
    else if(memcmp(item,"width",5)==0)
    {
     rect->pw=atoi(word);
    }
    else if(memcmp(item,"height",6)==0)
    {
     rect->ph=atoi(word);
    }
   }
   break;
   case 7://读取末尾括号
   if(c=='<')
   {
    type=8;
   }
   break;
   case 8: //读取/
   if(c=='/')
   {
    type=10;
   }
   else if(c>='a' && c<='z')
   {
   type=1;
   start=text;
   }
   break;
   case 10: //读取最后>
   if(c=='>')
   {
   type=0;
   // return text+1;
   }
  }
  text++;
 }
 return text;
}

//读取picture层
char *readPicture(ACTION *ac,char *text)
{
 
 int type=0;
 char c=0;
 char *head=NULL;
 char *item=NULL;
 char *word=NULL;
 char *start=NULL,*end=NULL;
 PICTURE *pic=NULL;
 
 while(*text)
 {
  c=*text;// printf("%c ",c);
  switch(type)
  {
   case 0://读取左括号
   if(c=='<')
   {
    type=-1;
    start=text+1;
    head=text+1;
   }
   break;
   case -1:
     if(c=='/')
     {
      //  if(Str.strcmp(text,i,"</"+head))

return text-1;
      
      type=10;
      text++;
      start=text;



     }
     else if(c=='!')
     {
      text=breakHead(text);
      type=0;
     }
     else if(c=='?')
     {
      text=breakHead(text);
      type=0;
     }
     else
     {
     type=1;
      }
break;
   
   case 1://读取头信息
  
    if(c=='>')//信息结束
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')//如果是上一个的括号。。。
   {
    
   }
   if(c<'a' || c>'z')
   {
    end=text;
    head=start;//malloc((int)end-(int)start+1);
    //strncpy(head, start,(int)end-(int)start);
    if(memcmp(head,"picture",7)==0)
       {
    pic=pic_new();
    ac_add(ac,pic);
    //printf("添加picture\n");
    type=3;
    }
    else
    {
//     printf("读取picture失败\n");
     return NULL;
    }
   }
   break;
   case 2://读取空格或回车
   if(c==' ' || c=='\n' || c=='\t')
   {
    type=3;
   }
   else if(c=='>')
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')
   {
    type=10;
   }
   break;
   case 3://读取参数
   if(c>='a' && c<='z')
   {
    start=text;
    type=4;
   }
   else if(c=='>') //若遇到反括号，就跳转到下一层
   {
 // RECTFLIP *rect=new_rect();
    text=readRectFlip(pic,text+1);
  //  pic_add(pic,rect);
    type=7;
    text--;
   }
   break;
   case 4://读取= 或空格
   if(c==' '|| c=='=')
   {
    end=text;
    item=start;
    type=5;
   }
   break;
   case 5://读取值
   if(c=='\"')
   {
    start=text+1;
    type=6;
   }
   break;
   case 6:
   if(c=='\"')
   {
    end=text;
    word=start;
    type=2;
    
   }
   break;
   case 7://读取末尾括号
   if(c=='<')
   {
    type=8;
   }
   break;
   case 8: //读取/
   if(c=='/')
   {
    type=10;
   }
   break;
   case 10: //读取最后>
   if(c=='>')
   {
   type=0;
    //return text+1;
   }
  }
  text++;
 }
 
 return text;
}

//读取action层
char *readAction(int sp,char *text)
{
 int type=0;
 char c=0;
 char *head=NULL;
 char *item=NULL;
 char *word=NULL;
 char *start=NULL,*end=NULL;
 ACTION *ac=NULL;
 //printf("读取Action\n");
 while(*text)
 {
  c=*text;
  switch(type)
  {
   case 0://读取左括号
   if(c=='<')
   {
    type=-1;
    start=text+1;
    head=text+1;
   }
   break;
   case -1:
     if(c=='/')
     {
      //  if(Str.strcmp(text,i,"</"+head))

return text-1;
      
      type=10;
      text++;
      start=text;



     }
     else if(c=='!')
     {
      text=breakHead(text);
      type=0;
     }
     else if(c=='?')
     {
      text=breakHead(text);
      type=0;
     }
     else
     {
     type=1;
      }
break;
   
   case 1://读取头信息
  
    if(c=='>')//信息结束
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')//如果是上一个的括号。。。
   {
    
   }
   if(c<'a' || c>'z')
   {
    end=text;
    head=start;//malloc((int)end-(int)start+1);
    //strncpy(head, start,(int)end-(int)start);
    if(memcmp(head,"action",6)==0)
    {
    ac=ac_new();
    sp_add(sp,ac);
    type=3;
    }
    else
    {
//     printf("读取action失败\n");
     return NULL;
    }
   }
   break;
   case 2://读取空格或回车
   if(c==' ' || c=='\n' || c=='\t')
   {
    type=3;
   }
   else if(c=='>')
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')
   {
    type=10;
   }
   break;
   case 3://读取参数
   if(c>='a' && c<='z')
   {
    start=text;
    type=4;
   }
   else if(c=='>') //若遇到反括号，就跳转到下一层
   {
   //printf("读取picture\n");
    //PICTURE *pic=pic_new();
    text=readPicture(ac,text+1);
    //ac_add(ac,pic);

    type=7;
    text--;
   }
   break;
   case 4://读取= 或空格
   if(c==' '|| c=='=')
   {
    end=text;
    item=start;
    type=5;
   }
   break;
   case 5://读取值
   if(c=='\"')
   {
    start=text+1;
    type=6;
   }
   break;
   case 6:
   if(c=='\"')
   {
    end=text;
    word=start;
    type=2;
    if(memcmp(item,"mode",4)==0)
    {
     ac->mode=atoi(word);
     //printf("rectflip x=%d\n",rect->x);
    }
   }
   break;
   case 7://读取末尾括号
   if(c=='<')
   {
    type=8;
   }
   break;
   case 8: //读取/
   if(c=='/')
   {
    type=10;
   }
   break;
   case 10: //读取最后>
   if(c=='>')
   {
   type=0;
    //return text+1;
   }
  }
  text++;
 }
 
 return text;

}


//读取Sprite层
int readSprite(char *filename,int bitmap)

{
 int32 len=0;
 char *buf= NULL;
 char *temp=NULL;
 char *text=NULL;
 SPRITE *sprite=NULL;
 int sp=0;
  int type=0;
 char c=0;
 char *head=NULL;
 char *item=NULL;
 char *word=NULL;
 char *start=NULL,*end=NULL;
 buf = readFileFromAssets(filename,&len);
 if(len>0)
 {
  
 text=malloc(len+1);
 temp=text;
 memcpy(text,buf,len);
 *(text+len)=0;
 free(buf);
// printf("读取成功\n");
 }
 /*
 int len=getlen(filename);
 char *buf=malloc(len+1);
 *(buf+len)=0
 int f=open(filename,1);
 read(f,buf,len);
 close(f);
 */
  sp=sp_new();
 sprite= (void*)sp;
 //printf("创建精灵\n");
 sp_setBitmap(sp,bitmap);
 
 sp_setDraw(sp,TRUE);

// printf("开始循环\n");
 while(*text)
 {
  c=*text;//printf(" %c%d",c,type);
  switch(type)
  {
   case 0://读取左括号
   if(c=='<')
   {
    type=-1;
    start=text+1;
    head=text+1;
   }
   break;
   case -1:
     if(c=='/')
     {
      //  if(Str.strcmp(text,i,"</"+head))


      
      type=10;
      text++;
      start=text;



     }
     else if(c=='!')
     {
      text=breakHead(text);
      type=0;
     }
     else if(c=='?')
     {
      text=breakHead(text);
      type=0;
     }
     else
     {
     type=1;
      }
break;
   
   case 1://读取头信息
  
    if(c=='>')//信息结束
   {
    text=readflip(text+1);
    type=7;
   }
   else if(c=='/')//如果是上一个的括号。。。
   {
    
   }
   if(c<'a' || c>'z')
   {
    end=text;
    head=start;//malloc((int)end-(int)start+1);
    //strncpy(head, start,(int)end-(int)start);
    if(memcmp(head,"sprite",6)==0)
    type=3;
    else
    {
 //    printf("读取action失败\n");
     return 0;//
    }
   }
   break;
   case 2://读取空格或回车
   if(c==' ' || c=='\n' || c=='\t')
   {
    type=3;
   }
   else if(c=='>')
   {
    text=readAction(sp,text+1);
    type=7;
   }
   else if(c=='/')
   {
    type=10;
   }
   break;
   case 3://读取参数
   if(c>='a' && c<='z')
   {
    start=text;
    type=4;
   }
   else if(c=='>') //若遇到反括号，就跳转到下一层
   {
   // ACTION *ac=ac_new();
    text=readAction(sp,text+1);
   // sp_add(sp,ac);
    type=7;
   }
   break;
   case 4://读取= 或空格
   if(c==' '|| c=='=')
   {
    end=text;
    item=start;
    type=5;
   }
   break;
   case 5://读取值
   if(c=='\"')
   {
    start=text+1;
    type=6;
   }
   break;
   case 6:
   if(c=='\"')
   {
    end=text;
    word=start;
    type=2;
    
    if(memcmp(item,"width",5)==0)
    {
     sprite->w=atoi(word);
     //printf("rectflip x=%d\n",rect->x);
    }
    else if(memcmp(item,"height",6)==0)
    {
     sprite->h=atoi(word);
    }
   }
   break;
   case 7://读取末尾括号
   if(c=='<')
   {
    type=8;
   }
   break;
   case 8: //读取/
   if(c=='/')
   {
    type=10;
   }
   break;
   case 10: //读取最后>
   if(c=='>')
   {
    //printf("返回\n");
    type=0;
    goto END;
   }
   break;
  }
  text++;
  //printf("自增\n");
 }
 
 END:
 free(temp);
 return sp;
}

int sp_read(char *filename,int bitmap)
{
 return (int)readSprite(filename,bitmap);
}













#endif
