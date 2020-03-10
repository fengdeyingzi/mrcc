#ifndef _BASE_H_I
#define _BASE_H_I
typedef struct
{
	uint8       IMEI[16];	      //IMEI 长度为15字节
	uint8       IMSI[16];	      //IMSI 长度为15字节
	char        manufactory[8];  //厂商名，最大7个字符，空字节填\0
	char        type[8];         //mobile type，最大7个字符，空字节填\0
	uint32      ver;            //移植软件版本
	uint8       spare[12];       //备用
}userinfo;

extern int32 sleep(uint32 ms);
extern int32 getSysInfo(mr_userinfo* info);
extern int32 sendSms(char* pNumber, char*pContent, int32 flags);
extern void call(char *number);
extern void connectWAP(char* wap);


extern int32 plat(int32 code, int32 param);
extern uint8* getFixMrp(int32 index);
extern uint8* getFixMrpByName(char* name);
extern int32 encode(uint8  *in, uint32 len,uint8 *out);
extern int32 setReloadFile(char* mrpname, char* filename);
extern int32 getReloadFile(char** mrpname, char** filename);


int32 loadSmsCfg(void);
int32 readSmsCfg(int32 pos, char* p, int32 len);
int32 setSmsCfg(int32 pos, char* p, int32 len);
int32 saveSmsCfg(void);

char* getMrParam(void);//1946
char* getMrEntry(void);//1952, V2000-V2002不支持；


extern void* malloc8(int size);
extern void free8(void *address);


/*
退出应用，应用调用该函数通知mythroad，应用将要退
出。
虚拟机在退出前将调用回调函数cb。
*/
extern void exitImmediately( timerCB cb, int32 data);




int32 isZip(uint8* inputbuf, int32 inputlen);

/*
解压缩。

输出:
outputbuf    解压后的数据，需要应用自己释放( free)；
outputlen    解压后的数据长度
      
返回:
      MR_SUCCESS     成功
      MR_FAILED         失败。
      MR_IGNORE        数据不是可识别的压缩格式。
*/
int32 unzip(uint8* inputbuf, int32 inputlen, uint8** outputbuf, int32* outputlen);
int32 unzipVM(uint8* inputbuf, int32 inputlen, uint8** outputbuf, int32* outputlen);

/*获取本ext模块全局变量使用的内存空间大小(字节)*/
int32 getExtGlobalMem(void);


int32 checkMrp(char* mrp_name);

int32 timerInit(void);

/*******************************C代码管理**********************************/

/*
该变量保存了该模块的C代码程序句柄。
*/
extern int32 extHandle;

/*
该函数需要在主ext模块中实现，当在子ext模块中调
用 extSendAppEvent函数时，主ext模块中的该函数被调
用。
输入:
app,code,param0,param1    均为模块间传递的参数;
返回值:
返回值将被作为子模块 extSendAppEvent函数的返回值
*/
extern int32 extRecvAppEvent(int32 app, int32 code, int32 param0, int32 param1);
extern int32 extRecvAppEventEx(int32 code, int32 p0, int32 p1, int32 p2, int32 p3, int32 p4,
								   int32 p5);


/*
函数 extLoad加载一个ext文件所包含的C代码程序。
输入:
buf     指向ext文件内容的指针
len     ext文件长度
返回值:
MR_FAILED      操作失败
其他           C代码程序句柄
*/
int32 extLoad(uint8* buf, int32 len);

/*
函数释放一个已经加载的C代码程序。

注意:
     如果需要在子模块发往主模块的事件处理函数中调用该
  函数释放子模块，需要注意的是，当调用完 extFree函数
  之后，实际上子模块所运行的代码空间在逻辑上已经被
  释放，注意不要在 extFree函数之后再进行与内存申请有
  关的操作。

输入:
ext     C代码程序句柄
返回值:
MR_FAILED      操作失败
MR_SUCCESS  操作成功
*/
int32 extFree(int32 ext);


/*
函数释放一个已经加载的C代码程序所对应的定时器。
除了定时器之外，函数不释放其他资源。


输入:
ext     C代码程序句柄
返回值:
MR_FAILED      操作失败
MR_SUCCESS  操作成功
*/
int32 extFreeTimer(int32 ext);

/*
函数设置一个已经加载的C代码程序的模式。
0:主模块
1:普通插件
2:应用插件
*/
void extSetMode(int32 ext, int32 mode);


/*
函数对一个已经加载的C代码程序进行初始化。
输入:
ext     C代码程序句柄
返回值:
MR_FAILED      操作失败
MR_SUCCESS  操作成功
*/
int32 extInit(int32 ext);

/*
函数将事件传入已经初始化的C代码程序中。
输入:
ext     C代码程序句柄
其他参数与 event相同
返回值:
C代码程序 event返回值
*/
int32 extEvent(int32 ext, int32 code, int32 param0, int32 param1);

/*
函数将暂停操作传入已经初始化的C代码程序中。
输入:
ext     C代码程序句柄
返回值:
C代码程序 pause返回值
*/
int32 extPause(int32 ext);

/*
函数将恢复操作传入已经初始化的C代码程序中。
输入:
ext     C代码程序句柄
返回值:
C代码程序 resume返回值
*/
int32 extResume(int32 ext);
/*
在子ext模块中调用该函数，主ext(管理)模块中的
 extRecvAppEvent函数将被调用。
输入:
app,code,param0,param1    均为模块间传递的参数;
返回值:
返回值为主ext模块 extRecvAppEvent函数的返回值
*/
int32 extSendAppEvent(int32 app, int32 code, int32 param0, int32 param1);
int32 extSendAppEventEx(int32 code, int32 p0, int32 p1, int32 p2, int32 p3,int32 p4, int32 p5);


int32 extMpsFpCall(int32 ext, mpsFpFuncType func, int32 p0, int32 p1, int32 p2, int32 p3, int32 p4, int32 p5);

int32 extInitMainModule(void);

#endif