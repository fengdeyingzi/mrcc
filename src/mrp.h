#ifndef _MRP_H_
#define _MRP_H_

#include <mrc_base.h>
#include <mrc_exb.h>

enum{
	MRP_SUCCESS,			//����ɹ�
	MRP_SEARCHFAILED,		//�޷������ļ�
	MRP_OPENFAILED,			//�޷����ļ�
	MRP_LISTLENFAILED,		//�б���Ϊ0(�ļ�����û���ļ���)
	MRP_FILE
};

typedef struct 
{
	char *appname;			//��ʾ��(�24��������)
	char *filename;			//�ڲ��ļ���(�12��������)
	uint32 appid;			//APPID		
	uint32 version;			//�汾
	char *vendor;			//������(�40��������)
	char *description;		//����(�64��������)

}TOMRPINFO;

//������Ȼص�
typedef void (*Ptr_TOMRP_progbar)(uint8 value, uint8 error);

/*
���MRP����
���룺
	InDir			//���Ŀ¼(δβ����"/")
	OutMrp			//������MRP�ļ�(�ɺ�·��)
	RAM				//�����ʹ�õ��ڴ��С(Ӧע��ʣ���ڴ�Ĵ�С������!)
	info			//���MRP����Ϣ
	TOMRP_progbar	//������Ȼص�
���أ�
	MRP_SUCCESS,			//����ɹ�
	MRP_SEARCHFAILED,		//�޷������ļ�
	MRP_OPENFAILED,			//�޷����ļ�
	MRP_LISTLENFAILED,		//�б���Ϊ0(�ļ�����û���ļ���)
*/
int32 ToMrp(const char *InDir, const char *OutMrp, int32 RAM, TOMRPINFO *info, Ptr_TOMRP_progbar TOMRP_progbar);

/*
��ѹ(��)MRP����
���룺
	MRPName		MRP�ļ���
	ToDir		�ļ����Ŀ¼(δβ����"/"���Ŀ¼�������򴴽�)
	RAM			ʹ�õ��ڴ��С(ֻ����isUNΪFALSEʱ��Ч)(Ӧע��ʣ���ڴ�Ĵ�С������!)
	isUN		�Ƿ��ѹ�ļ�
���أ�
	�ɹ���
	MR_FAILED	ʧ��
*/
int32 UnMrp(char* MRPName, char* ToDir, int32 RAM, int32 isUN);

#endif