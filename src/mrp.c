#include "mrc_base.h"
#include "mrc_exb.h"
#include "mrp.h"

int32 ToMrp(const char *InDir, const char *OutMrp, int32 RAM, TOMRPINFO *info, Ptr_TOMRP_progbar TOMRP_progbar)
{
#define BUFFERLEN 240
#define FILENAMELEN 255

	int32 search_handle=0;
	int32 MRPHandle=0;
	int32 fileHandle=0;

	uint8 error=0;

	char *buffer=NULL;
	char *filename=NULL;
	char *tempfile=NULL;
	char *xiegang = "/";

	int32 listLen=0;
	int32 str_len=0;
	int32 filepy=0;//�ļ�ƫ��
	int32 fileLen=0;//�ļ�����
	int32 space=0;//�հ��ֽ�


	//////////////////////////////////////////////////////////////////////////////

	filename = (char*)malloc(FILENAMELEN);
	buffer = (char*)malloc(BUFFERLEN);

	mrc_memset(buffer,0,BUFFERLEN);
	TOMRP_progbar(1,0);
	search_handle = mrc_findStart(InDir,buffer,BUFFERLEN);
	if(search_handle == MR_FAILED)
	{
		mrc_free((void*)filename);
		mrc_free((void*)buffer);
		return MRP_SEARCHFAILED;
	}
	TOMRP_progbar(2,0);
	//�����б���
	do
	{
		mrc_memset(filename,0,FILENAMELEN);
		mrc_strcpy(filename,InDir);
		mrc_strcat(filename,xiegang);
		mrc_strcat(filename,buffer);

		if(mrc_fileState(filename) == MR_IS_FILE && mrc_strlen(buffer)<BUFFERLEN)
		{
			listLen += (mrc_strlen(buffer) + 17);
		}
		else
		{
			error++;
		}
	}while(!mrc_findGetNext(search_handle,buffer,BUFFERLEN));
	mrc_findStop(search_handle);
	if(!listLen)//����б���ΪO����
	{
		mrc_free((void*)filename);
		mrc_free((void*)buffer);
		return MRP_LISTLENFAILED;
	}
	TOMRP_progbar(3,0);

	mrc_free((void*)buffer);
	buffer = (char*)mrc_readFileFromMrp("head",&str_len,0);

	mrc_remove(OutMrp);//ɾ�����ļ�
	MRPHandle = mrc_open(OutMrp,MR_FILE_RDWR | MR_FILE_CREATE);
	if(!MRPHandle)//�޷����ļ�
	{
		mrc_free((void*)filename);
		if(buffer != NULL)	mrc_freeFileData((void*)buffer,str_len);
		return MRP_OPENFAILED;
	}
	if(buffer != NULL)
	{
		mrc_write(MRPHandle,buffer,str_len);//240�ļ�ͷ
		mrc_freeFileData((void*)buffer,str_len);
	}
	buffer = (char*)malloc(BUFFERLEN);
	
	TOMRP_progbar(4,0);
	listLen += 232;//������λ��(�ļ�ͷ��Ϣ)
	mrc_seek(MRPHandle,4,MR_SEEK_SET);
	mrc_write(MRPHandle,&listLen,4);
	mrc_seek(MRPHandle,240,MR_SEEK_SET);
	listLen += 8;//��������ʼλ�ã������ļ�ƫ�ƵĻ���ֵ��
	filepy = listLen;//��һ���ļ�ƫ��
	search_handle = mrc_findStart(InDir,buffer,BUFFERLEN);
	if(search_handle == MR_FAILED)
	{
		mrc_close(MRPHandle);
		mrc_free((void*)filename);
		mrc_free((void*)buffer);
		return MRP_SEARCHFAILED;
	}
	//�����ļ��б�
	do
	{
		mrc_memset(filename,0,FILENAMELEN);
		mrc_strcpy(filename,InDir);
		mrc_strcat(filename,xiegang);
		mrc_strcat(filename,buffer);

		str_len = mrc_strlen(buffer);
		if(mrc_fileState(filename) == MR_IS_FILE && str_len<BUFFERLEN)
		{
			str_len++;//�ļ������ȼ�1
			mrc_write(MRPHandle,&str_len,4);//д�ļ�������
			mrc_write(MRPHandle,buffer,str_len);//д�ļ���
			filepy = filepy + fileLen + str_len + 8;//�����ļ�ƫ��
			fileLen = mrc_getLen(filename);
			mrc_write(MRPHandle,&filepy,4);//д�ļ�ƫ��
			mrc_write(MRPHandle,&fileLen,4);//д�ļ�����
			mrc_write(MRPHandle,&space,4);
		}
		else
		{
			error++;
		}
	}while(!mrc_findGetNext(search_handle,buffer,BUFFERLEN));
	mrc_findStop(search_handle);
	TOMRP_progbar(5,0);
	search_handle = mrc_findStart(InDir,buffer,BUFFERLEN);
	if(search_handle == MR_FAILED)
	{
		mrc_close(MRPHandle);
		mrc_free((void*)filename);
		mrc_free((void*)buffer);
		return MRP_SEARCHFAILED;
	}
	//����ļ�����
	tempfile = (char*)malloc(RAM);
	do
	{
		mrc_memset(filename,0,FILENAMELEN);
		mrc_strcpy(filename,InDir);
		mrc_strcat(filename,xiegang);
		mrc_strcat(filename,buffer);

		str_len = mrc_strlen(buffer);
		if(mrc_fileState(filename) == MR_IS_FILE && str_len<BUFFERLEN)
		{
			str_len++;//�ļ������ȼ�1
			mrc_write(MRPHandle,&str_len,4);//д�ļ�������
			mrc_write(MRPHandle,buffer,str_len);//д�ļ���
			fileLen = mrc_getLen(filename);
			mrc_write(MRPHandle,&fileLen,4);//д�ļ�����

			str_len = RAM;//�ڴ滺��������
			fileHandle = mrc_open(filename,MR_FILE_RDONLY);
			if(!fileHandle) error++;//�˴��������κζ��⴦��(û��̫��Ӱ��)
			while(fileLen)
			{
				if(fileLen>str_len)
				{
					fileLen -= str_len;
				}
				else
				{
					str_len = fileLen;
					fileLen = 0;
				}
				mrc_read(fileHandle,tempfile,str_len);
				mrc_write(MRPHandle,tempfile,str_len);
			}
			mrc_close(fileHandle);
		}
		else
		{
			error++;//ͳ�ƴ�����
		}
	}while(!mrc_findGetNext(search_handle,buffer,BUFFERLEN));
	mrc_findStop(search_handle);

	mrc_free((void*)tempfile);
	TOMRP_progbar(6,0);

	//�����ļ�ͷ
	mrc_close(MRPHandle);
	fileLen = mrc_getLen(OutMrp);
	MRPHandle = mrc_open(OutMrp,MR_FILE_RDWR);
	if(!MRPHandle)
	{
		mrc_free((void*)filename);
		mrc_free((void*)buffer);
		return MRP_OPENFAILED;
	}
	mrc_seek(MRPHandle,8,MR_SEEK_SET);
	mrc_write(MRPHandle,&fileLen,4);
	
	mrc_seek(MRPHandle,16,MR_SEEK_SET);
	mrc_memset(buffer,0,12);
	mrc_strcpy(buffer, info->filename);
	mrc_write(MRPHandle,buffer,12);//д�ڲ��ļ���

	mrc_memset(buffer,0,24);
	mrc_strcpy(buffer, info->appname);
	mrc_write(MRPHandle,buffer,24);//д��ʾ��

	mrc_seek(MRPHandle,68,MR_SEEK_SET);
	mrc_write(MRPHandle,&(info->appid), 4);//дAPPID
	mrc_write(MRPHandle,&(info->version), 4);//д�汾

	mrc_seek(MRPHandle,88,MR_SEEK_SET);
	mrc_memset(buffer,0,40);
	mrc_strcpy(buffer, info->vendor);
	mrc_write(MRPHandle,buffer, 40);//д����

	mrc_memset(buffer,0,64);
	mrc_strcpy(buffer, info->description);
	mrc_write(MRPHandle,buffer, 64);//д����

	mrc_seek(MRPHandle,192,MR_SEEK_SET);
	listLen = mrc_htonl(info->appid);
	mrc_write(MRPHandle,&listLen,4);//дAPPID
	listLen = mrc_htonl(info->version);
	mrc_write(MRPHandle,&listLen,4);//д�汾

	error -= 6;
	error = error/3 + error%3;
	TOMRP_progbar(7,error);

	mrc_close(MRPHandle);
	mrc_free((void*)buffer);
	mrc_free((void*)filename);
	return MRP_SUCCESS;
}

int32 UnMrp(char* MRPName, char* ToDir, int32 RAM, int32 isUN)
{
	int32 	MRPhandle = 0,//�ļ���� 
			FileHandle = 0;	
	uint32 	filenamelen = 0;

	char *filename;
	char *filename2;
	uint8 *filebuf;

	int32 unfilelen;
	int32 unfilewz;
	int32 RAMlen = 0;
	int32 sum = 0;//�ɹ���
	int32 fileStart = 0,
		  fileStop = 0;	

	//////////////////////////////////////////////////////////////	

	filename = (char*)mrc_malloc(50);
	filename2 = (char*)mrc_malloc(50);

	mrc_mkDir(ToDir);
	if(mrc_getLen(MRPName)<240)//���ж��Ƿ�Ϊ��ȷ��MRP��ʽ
	{
		goto aa;
	}
	MRPhandle = mrc_open(MRPName,MR_FILE_RDONLY);//���ļ�
	if(!MRPhandle) 
	{
		goto aa;
	}
	mrc_seek(MRPhandle,0,MR_SEEK_SET);
	mrc_read(MRPhandle,filename,4);
	if(mrc_strncmp(filename,"MRPG",4))//���ж��Ƿ�Ϊ��ȷ��MRP��ʽ
	{
		mrc_close(MRPhandle);
		goto aa;
	}
	mrc_read(MRPhandle, &fileStop,4);
	fileStop += 8;//�ļ��б���ֹ��λ��
	mrc_seek(MRPhandle,12,MR_SEEK_SET);
	mrc_read(MRPhandle, &fileStart,4);//�б�ʼλ��

	while(fileStart < fileStop)
	{
		filebuf = NULL;
		mrc_memset(filename2,0,50);

		mrc_seek(MRPhandle,fileStart,MR_SEEK_SET);//�Ƶ����б�
		mrc_read(MRPhandle, &filenamelen,4);//�ļ�������
		mrc_read(MRPhandle,filename,filenamelen);//�ļ���
		mrc_read(MRPhandle,&unfilewz,4);
		mrc_read(MRPhandle,&unfilelen,4);
		fileStart = fileStart + filenamelen + 16;//��λ���Ƶ��¸��б�

		mrc_strcpy(filename2,ToDir);
		mrc_strcat(filename2,"/");
		mrc_strcat(filename2,filename);
		mrc_remove(filename2);
		FileHandle = mrc_open(filename2, MR_FILE_RDWR | MR_FILE_CREATE);
		if(!FileHandle)	continue;
		if(isUN)//д����ѹ����
		{
		/*	if(unfilelen>600)
			{
				mrc_close(FileHandle);
				continue;
			}
		*/
			if(mrc_readFileFromMrpExA(MRPName,filename, &filebuf, &unfilelen,3))
			{
				mrc_close(FileHandle);
				continue;
			}

			mrc_write(FileHandle,filebuf,unfilelen);
			mrc_freeFileData((void*)filebuf,unfilelen);
		}
		else//д��ѹ������
		{
			filebuf = (uint8*)malloc(RAM);
			RAMlen = RAM;
			mrc_seek(MRPhandle,unfilewz,MR_SEEK_SET);
			while(unfilelen)
			{
				if(unfilelen>RAMlen)
				{
					unfilelen -= RAMlen;
				}
				else
				{
					RAMlen = unfilelen;
					unfilelen = 0;
				}
				mrc_read(MRPhandle,(void*)filebuf,RAMlen);
				mrc_write(FileHandle,filebuf,RAMlen);
			}
			mrc_free((void*)filebuf);
		}
		sum += 1;
		mrc_close(FileHandle);
	}

	mrc_free((void*)filename);
	mrc_free((void*)filename2);
	mrc_close(MRPhandle);

	return sum;

aa:	mrc_free((void*)filename);
	mrc_free((void*)filename2);
	return MR_FAILED;

}