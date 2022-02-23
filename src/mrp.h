#ifndef _MRP_H_
#define _MRP_H_

#include <mrc_base.h>
#include <mrc_exb.h>

enum{
	MRP_SUCCESS,			//打包成功
	MRP_SEARCHFAILED,		//无法搜索文件
	MRP_OPENFAILED,			//无法打开文件
	MRP_LISTLENFAILED,		//列表长度为0(文件夹中没有文件！)
	MRP_FILE
};

typedef struct 
{
	char *appname;			//显示名(最长24含结束符)
	char *filename;			//内部文件名(最长12含结束符)
	uint32 appid;			//APPID		
	uint32 version;			//版本
	char *vendor;			//开发商(最长40含结束符)
	char *description;		//介绍(最长64含结束符)

}TOMRPINFO;

//打包进度回调
typedef void (*Ptr_TOMRP_progbar)(uint8 value, uint8 error);

/*
打包MRP函数
输入：
	InDir			//打包目录(未尾不带"/")
	OutMrp			//打包后的MRP文件(可含路径)
	RAM				//打包所使用的内存大小(应注意剩余内存的大小来分配!)
	info			//打包MRP的信息
	TOMRP_progbar	//打包进度回调
返回：
	MRP_SUCCESS,			//打包成功
	MRP_SEARCHFAILED,		//无法搜索文件
	MRP_OPENFAILED,			//无法打开文件
	MRP_LISTLENFAILED,		//列表长度为0(文件夹中没有文件！)
*/
int32 ToMrp(const char *InDir, const char *OutMrp, int32 RAM, TOMRPINFO *info, Ptr_TOMRP_progbar TOMRP_progbar);

/*
解压(包)MRP函数
输入：
	MRPName		MRP文件名
	ToDir		文件存放目录(未尾不带"/"如果目录不存在则创建)
	RAM			使用的内存大小(只有在isUN为FALSE时有效)(应注意剩余内存的大小来分配!)
	isUN		是否解压文件
返回：
	成功数
	MR_FAILED	失败
*/
int32 UnMrp(char* MRPName, char* ToDir, int32 RAM, int32 isUN);

#endif