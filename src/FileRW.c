#include "FileRW.h"

#include <mrc_base.h>

#include "momo.h"
#include "mrp.h"

/*---------------------------------------------------------------------------------------------*/
//��Mrp��ȡrc�ļ���������Mrp�ļ���
// int32 ReadMrp(const char *MrpFile)
// {
// 	int32 RcSize=0, rValue=0, fHwnd=0;
// 	uint8 *RcData=NULL;
//     const char *tempFile = "temp.rc";
// mrc_printf("��mrp����ļ� %d",0);
// 	rValue = mrc_readFileFromMrpEx((char*)MrpFile, "res_lang0.rc", &RcData, &RcSize, 0);
// 	if (MR_SUCCESS == rValue)
// 	{
// 		mrc_printf ("�ж�mrp�ļ��ɹ� %d",0);
//         mrc_remove(tempFile);
//         fHwnd = mrc_open(tempFile, MR_FILE_RDWR | MR_FILE_CREATE);
//         mrc_seek(fHwnd, 0, MR_SEEK_SET);
//         mrc_write(fHwnd, RcData, RcSize);
//         mrc_close(fHwnd);
//         mrc_free(RcData);
// 		ReadRc(tempFile);
//         mrc_remove(tempFile);

// 		return MR_SUCCESS;
// 	}
// 	else
// 	{
// 		return MR_FAILED;
// 	}
// }

//����rc��Mrp�ļ���������Mrp�ļ���
// int32 SaveMrp(const char *MrpFile)
// {
// 	int32 fHwnd;
// 	int32 MrpSize, NameLen, NewOffset;
// 	uint32 HeadSize,NewRcSize;
// 	char *HeadData, *RcData, *pPos, *RcName, *tempFile;

// 	RcName = "res_lang0.rc";
// 	NameLen = 13;

// 	//����res_lang0.rc�����¶�ȡ
// 	tempFile = "temp.rc";
// 	NewRcSize = SaveRc(tempFile);
// 	RcData = (char*)mrc_readAll(tempFile, &NewRcSize);
// 	mrc_remove(tempFile);
// 	if (NULL == RcData) return 0;

// 	fHwnd = mrc_open(MrpFile, MR_FILE_RDWR);
// 	if (0 == fHwnd) return 0;

// 	//ȡ��Mrp�ܴ�С
// 	mrc_seek(fHwnd, 8, MR_SEEK_SET);
// 	mrc_read(fHwnd, &MrpSize, 4);

// 	//ȡ����Ϣ���б��С
// 	mrc_seek(fHwnd, 4, MR_SEEK_SET);
// 	mrc_read(fHwnd, &HeadSize, 4);
// 	HeadSize += 8;

// 	//ȡ����Ϣ���б�����
// 	HeadData = (char*)mrc_malloc(HeadSize);
// 	mrc_seek(fHwnd, 0, MR_SEEK_SET);
// 	mrc_read(fHwnd, HeadData, HeadSize);

// 	//����res_lang0.rc
// 	pPos = FindPos(HeadData, RcName, HeadSize, NameLen);
// 	if (pPos)
// 	{
// 		//�޸���res_lang0.rcƫ��
// 		NewOffset = MrpSize+NameLen + 8;
// 		mrc_memcpy(pPos+strlen(RcName)+1, &NewOffset, 4);

// 		//�޸���res_lang0.rc��С
// 		mrc_memcpy(pPos+strlen(RcName)+1+4, &NewRcSize, 4);

// 		//�޸�Mrp�ܴ�С
// 		MrpSize = MrpSize + NewRcSize + NameLen + 8;
// 		mrc_memcpy(HeadData+8, &MrpSize, 4);

// 		//д��Mrp�ļ�
// 		mrc_seek(fHwnd, 0, MR_SEEK_SET);
// 		mrc_write(fHwnd, HeadData, HeadSize);

// 		//д��res_lang0.rc��Ϣ��ĩβ
// 		mrc_seek(fHwnd, 0, MR_SEEK_END);
// 		mrc_write(fHwnd, &NameLen, 4);
// 		mrc_seek(fHwnd, 0, MR_SEEK_END);
// 		mrc_write(fHwnd, RcName, NameLen);
// 		mrc_seek(fHwnd, 0, MR_SEEK_END);
// 		mrc_write(fHwnd, &NewRcSize, 4);

// 		//д��res_lang0.rc���ݵ�ĩβ
// 		mrc_seek(fHwnd, 0, MR_SEEK_END);
// 		mrc_write(fHwnd, RcData, NewRcSize);
// 	}

// 	mrc_free(RcData);
// 	mrc_free(HeadData);
// 	mrc_close(fHwnd);

// 	return MrpSize;
// }

// ��ȡ�ϼ�Ŀ¼��������/ ��Ҫfree
char *getParamPath(char *path) {
	char *temp = malloc(mrc_strlen(path) + 1);
	int i = 0;
	mrc_strcpy(temp, path);

	for (i = mrc_strlen(temp) - 1; i >= 0; i--) {
		if (temp[i] == '/' || temp[i] == '\\') {
			temp[i] = '\0';
			break;
		}
	}
	return temp;
}

// ��ȡ�ļ���
static char *getName(char *path) {
	int i = 0;
	for (i = mrc_strlen(path) - 1; i >= 0; i--) {
		if (path[i] == '/' || path[i] == '\\') {
			return path + i + 1;
		}
	}
	return path;
}

//��Ҫfree
static char *getDirName(char *path) {
	int i = 0;
	int end = mrc_strlen(path);
	char *dirname = mrc_malloc(128);
	int start = 0;
	mrc_memset(dirname, 0, 128);
	mrc_strcpy(dirname, path);
	for (i = mrc_strlen(path) - 1; i >= 0; i--) {
		if (path[i] == '/' || path[i] == '\\') {
			end = i;
			break;
		}
	}
	for (i = end-1; i >= 0; i--) {
		if (path[i] == '/' || path[i] == '\\') {
			start = i + 1;
			mrc_memcpy(dirname, path + start, end - start);
			*(dirname+(end-start)) = '\0';
			break;
		}
	}
	return dirname;
}
/*----------------------------------------------------------------------------------------*/
//����λ��
//������Դ���ݣ��������ݣ�Դ��С��������С
//���أ���Դ�����ҵ�λ�õ�ָ��
char *FindPos(char *StrS, char *StrF, int32 SLen, int32 FLen) {
	char *Str1, *Str2;
	int32 Found, i, j;

	for (i = 0; i < SLen; i++) {
		Found = 1;
		for (j = 0; j < FLen; j++) {
			Str1 = StrS + i + j;
			Str2 = StrF + j;
			if (*Str1 != *Str2) {
				Found = 0;
				break;
			}
		}
		if (1 == Found)
			return StrS + i;
	}
	return NULL;
}

//�滻mrp��ָ���ļ�
int32 mrpReplaceFile(const char *MrpFile, char *filename, char *conname) {
	int32 fHwnd;
	int32 MrpSize, NameLen, NewOffset;
	int32 MRPHeaderSize = 0; //[12:16] �ļ�ͷ�ĳ��ȣ�ͨ����240������ж�����������Ҫ���϶������ݵĳ���
	uint32 FileHeadLen, NewRcSize;
	char *HeadData, *RcData, *RcName, *pPos;

	RcName = conname;
	NameLen = mrc_strlen(conname);

	//����res_lang0.rc�����¶�ȡ
	NewRcSize = mrc_getLen(filename);
	RcData = (char *)mrc_readAll(filename, &NewRcSize);
	if (NULL == RcData)
		return 0;

	fHwnd = mrc_open(MrpFile, MR_FILE_RDWR);
	if (0 == fHwnd)
		return 0;

	//ȡ��Mrp�ܴ�С
	mrc_seek(fHwnd, 8, MR_SEEK_SET);
	mrc_read(fHwnd, &MrpSize, 4);

	mrc_seek(fHwnd, 12, MR_SEEK_SET);
	mrc_read(fHwnd, &MRPHeaderSize, 4);

	//ȡ����Ϣ���б��С
	mrc_seek(fHwnd, 4, MR_SEEK_SET);
	mrc_read(fHwnd, &FileHeadLen, 4);
	FileHeadLen += 8;

	//ȡ����Ϣ���б�����
	HeadData = (char *)mrc_malloc(FileHeadLen-MRPHeaderSize);
	mrc_seek(fHwnd, MRPHeaderSize, MR_SEEK_SET);
	mrc_read(fHwnd, HeadData, FileHeadLen-MRPHeaderSize);

	//����res_lang0.rc
	pPos = FindPos(HeadData, RcName, FileHeadLen, NameLen+1);
	if (pPos) {
		//�޸���res_lang0.rcƫ��
		NewOffset = MrpSize + NameLen + 8;
		mrc_memcpy(pPos + NameLen + 1, &NewOffset, 4);

		//�޸���res_lang0.rc��С
		mrc_memcpy(pPos + NameLen + 1 + 4, &NewRcSize, 4);

		//�޸�Mrp�ܴ�С
		MrpSize = MrpSize + NewRcSize + NameLen + 8;
		mrc_memcpy(HeadData + 8, &MrpSize, 4);

		//д��Mrp�ļ�
		mrc_seek(fHwnd, MRPHeaderSize, MR_SEEK_SET);
		mrc_write(fHwnd, HeadData, FileHeadLen-MRPHeaderSize);

		//д��res_lang0.rc��Ϣ��ĩβ
		mrc_seek(fHwnd, 0, MR_SEEK_END);
		mrc_write(fHwnd, &NameLen, 4);
		mrc_seek(fHwnd, 0, MR_SEEK_END);
		mrc_write(fHwnd, RcName, NameLen);
		mrc_seek(fHwnd, 0, MR_SEEK_END);
		mrc_write(fHwnd, &NewRcSize, 4);

		//д��res_lang0.rc���ݵ�ĩβ
		mrc_seek(fHwnd, 0, MR_SEEK_END);
		mrc_write(fHwnd, RcData, NewRcSize);
		mrc_printf("�滻�ļ��ɹ�");
	}else{
		mrc_printf("�滻�ļ�ʧ��");
	}

	mrc_free(RcData);
	mrc_free(HeadData);
	mrc_close(fHwnd);

	return MrpSize;
}

// int32 removeDir(const char* dirName)
// {
//     char fullName[128];
//     char fileName[64];
//     int32 ret = -1;
//     int32 dirNameLen;

//     if(!dirName)
//         return MR_FAILED;
//     memset(fullName, 0, sizeof(fullName));
//     memset(fileName, 0, sizeof(fileName));

//     dirNameLen = strlen(dirName);
//     memcpy(fullName, dirName, dirNameLen);
//     if(fullName[dirNameLen-1] != '/')//׼��ƴ��Ŀ¼�µ����ļ�����Ŀ¼
//     {
//         fullName[dirNameLen] = '/';
//         dirNameLen++;
//     }

//     if(mrc_fileState(dirName) == MR_IS_DIR)
//     {
//         int32 fd;
//         int32 result = MR_FAILED;

//         fd = mrc_findStart(dirName, fileName, sizeof(fileName));
//         if(fd > 0)//���������Ч
//         {
//             result = MR_SUCCESS;
//             while(result == MR_SUCCESS)
//             {
//                 //���fileNameȡֵΪ��.����ʶ������ֵ��Ч����������δ���
//                 if(fileName[0] && fileName[0] != '.')
//                 {
//                     int32 length = strlen(fileName);
//                     memcpy(&fullName[dirNameLen], fileName, length);
//                     fullName[dirNameLen+length] = 0;

//                     length = mrc_fileState(fullName);
//                     if(length == MR_IS_FILE)//�ļ����ͣ�ɾ���ļ�
//                         mrc_remove(fullName);
//                     else if(length == MR_IS_DIR)//�ļ������ͣ��ݹ�ɾ�����ļ���
//                         removeDir(fullName);
//                 }
//                 memset(fileName, 0, sizeof(fileName));
//                 result = mrc_findGetNext(fd, fileName, sizeof(fileName));
//             }
//             mrc_findStop(fd);
//         }
//         //����һ�μ�����,�������ɾ���ļ��е�����
//         fd = mrc_findStart("",fileName,sizeof(fileName));
//         mrc_findStop(fd);
//         ret = mrc_rmDir(dirName);
//     }
//     return ret;
// }

//����mrp����ʾ����
int32 mrpSetDisplayName(const char *MrpFile, const char *displayname) {
	int32 f = mrc_open(MrpFile, 4);
	char *temp = mrc_malloc(22);
	mrc_memset(temp, 0, 22);
	strcpy(temp, displayname);
	if (f != 0) {
		mrc_seek(f, 28, MR_SEEK_SET);
		mrc_write(f, temp, 22);
		mrc_close(f);
		mrc_free(temp);
	}
	return MR_SUCCESS;
}
void tomrppro(uint8 value, uint8 error){

}
void ShowLineText(int8 line, char *text, uint8 r, uint8 g, uint8 b)
{
	static int8 sum;
	if(!line)
	{
		mrc_clearScreen(0,0,0);
		sum=0;
	}
	if(sum >= (SCREEN_HEIGHT / 24 - 1))
	{
		mrc_clearScreen(0,0,0);
		sum=0;
	}
	else
	{
		sum++;
	}
	mrc_drawText(text, 0, 24 * (sum-1), r, g, b, 0,1);
	mrc_refreshScreen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//��mrp������ļ�
int32 mrpAddFile(const char *MrpFile, char *filename) {
	char *cacheDir = "mrpbuilder";
	// char *MrpFile_new = mrc_malloc(512);
	char *displayname = NULL;
	char *tempname = mrc_malloc(128);
	char *temp = mrc_malloc(128);
	int32 ret = 0;
	TOMRPINFO mrpinfo;
	// mrc_sprintf(MrpFile_new, "%s%s", MrpFile,".mrp");
	mrc_printf("mrpAddFile: %s %s %s", MrpFile, filename,"MrpFile_new");
	
	//�������Ŀ¼������
	removeDir(cacheDir);
	mrc_mkDir(cacheDir);
	//���
	mrc_printf("��ʼ���");
	UnMrp((char*)MrpFile, cacheDir, 50*1024, FALSE);
	
	//���
	// PackageMrp(mrpinfo, MrpFile, cacheDir, MrpFile_new);
	displayname = "�ҵ�Mrp";
	mrc_sprintf(tempname, "%s - capp", displayname);
	mrpinfo.appid = 1000;	 //APPID
	mrpinfo.version = 1001;	 //�汾ID
	mrpinfo.appname = tempname;
	mrpinfo.description = "�ֻ�CAPP����������ȡmpc.c�ļ���������";
	mrpinfo.filename = "capprun.mrp";
	mrpinfo.vendor = "���Ӱ��";
	mrc_printf("��ʼ���");
	
	mrc_sprintf(temp, "%s/%s", cacheDir, getName(filename));
	CopyFile(temp, filename);
	ret = ToMrp(cacheDir, MrpFile, 20480, &mrpinfo, tomrppro);
	switch(ret)
	{
	case MRP_SUCCESS:
		ShowLineText(1,"��������ɹ���",255,255,255);
		return;
	case MRP_SEARCHFAILED:
		ShowLineText(1,"�޷������ļ���",255,255,255);
		break;
	case MRP_OPENFAILED:
		ShowLineText(1,"�޷����ļ���",255,255,255);
		break;
	case MRP_LISTLENFAILED:
		ShowLineText(1,"û���ҵ��ļ���",255,255,255);
		break;
	default:
		break;
	}
	// mrpSetDisplayName(MrpFile,displayname);
	// mrc_free(MrpFile_new);
	mrc_remove(MrpFile);
	mrc_printf("������");
	// mrc_rename(MrpFile_new, MrpFile);
	mrc_free(tempname);
	mrc_free(temp);
	return MR_SUCCESS;
}

int32 unpackFile(char* name,char*out)
{
    char *buf=NULL;
	int32 f = 0;
	int32 len = 0;
	mrc_printf("unpackFile %s -> %s",name,out);
	buf = mrc_readFileFromMrp(name,&len,0);
	f=mrc_open(out,12);
	if(f!=0){
		mrc_write(f,buf,len);
		mrc_close(f);
		mrc_freeFileData(buf, len);
		return MR_SUCCESS;
	}
	return MR_FAILED;
}

//�������
int32 packProject(char *path) {
	int32 f;
	char *endfile;
	// int32 i;
	int32 ret = 0;
	char *temp = mrc_malloc(255);
	char *temppath = mrc_malloc(255);
	int list_n = 0;
	
	char *proDir = getParamPath(path);
	char *assetsDir = mrc_malloc(128);
	char *displayname = getDirName(path);
	char *mrpPath = mrc_malloc(255);
	char *tempfile = mrc_malloc(255);
	char *cacheDir = "mrpbuilder";
	
	TOMRPINFO mrpinfo;
	mrc_sprintf(assetsDir, "%s/assets", proDir);
	mrpinfo.appid = 1000;	 //APPID
	mrpinfo.version = 1001;	 //�汾ID
	mrpinfo.appname = "�ҵ�mrp - capp";
	mrpinfo.description = "�ֻ�CAPP����������ȡmpc.c�ļ���������";
	mrpinfo.filename = "capprun.mrp";
	mrpinfo.vendor = "���Ӱ��";
	mrc_printf("����Ŀ¼��%s", proDir);
	mrc_sprintf(mrpPath, "%s/%s", proDir, "run.mrp");
	//��ѹmrp�ļ�
	unpackFile("run.mrp", mrpPath);
	//�������Ŀ¼������
	removeDir(cacheDir);
	mrc_mkDir(cacheDir);
	UnMrp((char*)mrpPath, cacheDir, 50*1024, FALSE);
	mrc_sprintf(tempfile, "%s/%s", cacheDir, "mpc.c");
	CopyFile(tempfile, path);
	// mrpReplaceFile(mrpPath, path, "mpc.c");
	
    //����pathĿ¼
	f = mrc_findStart(proDir, temp, 72);
	if (f == MR_FAILED) {
		return MR_FAILED;
	}
	mrc_printf("findstart %s", temp);
	if (temp[0] != '\0' && *temp != '.') {
		list_n++;
		if (checkEndName(temp, ".c") || checkEndName(temp, ".C") || checkEndName(temp, ".h") || checkEndName(temp, ".H")) {
			mrc_sprintf(temppath,"%s/%s",proDir, temp);
			mrc_sprintf(tempfile, "%s/%s", cacheDir, temp);
	        CopyFile(tempfile, temppath);
		    // mrpAddFile(mrpPath, temppath);
		    // list_add(view, temp);
		}
	}

	while (ret == 0) {
		ret = mrc_findGetNext(f, temp, 72);
		mrc_printf("findnext %s", temp);
		if (ret == MR_FAILED)
			break;
		if (temp[0] == '\0')
			break;
		if (*temp != '.') {
			if (checkEndName(temp, ".c") || checkEndName(temp, ".C") || checkEndName(temp, ".h") || checkEndName(temp, ".H")) {
				list_n++;
				mrc_sprintf(temppath,"%s/%s",proDir, temp);
				mrc_sprintf(tempfile, "%s/%s", cacheDir, temp);
	            CopyFile(tempfile, temppath);
				// mrpAddFile(mrpPath, temppath);
			}
		}
	}

	//����assetsĿ¼
	ret = 0;
	f = mrc_findStart(assetsDir, temp, 72);
	if (f == MR_FAILED) {
		return MR_FAILED;
	}
	mrc_printf("findstart %s", temp);
	if (temp[0] != '\0' && *temp != '.') {
		list_n++;
		
			mrc_sprintf(temppath,"%s/%s",assetsDir, temp);
			mrc_sprintf(tempfile, "%s/%s", cacheDir, temp);
			mrc_printf("CopyFile %s %s", tempfile, temppath);
	        CopyFile(tempfile, temppath);
		    // mrpAddFile(mrpPath, temppath);
		    // list_add(view, temp);
		
	}
	
	while (ret == 0) {
		ret = mrc_findGetNext(f, temp, 72);
		mrc_printf("findnext %s", temp);
		if (ret == MR_FAILED)
			break;
		if (temp[0] == '\0')
			break;
		if (*temp != '.') {
			
				list_n++;
				mrc_sprintf(temppath,"%s/%s",assetsDir, temp);
				mrc_sprintf(tempfile, "%s/%s", cacheDir, temp);
				mrc_printf("CopyFile %s %s", tempfile, temppath);
	            CopyFile(tempfile, temppath);
				// mrpAddFile(mrpPath, temppath);
			
		}
	}
	ret = ToMrp(cacheDir, mrpPath, 20480, &mrpinfo, tomrppro);
	switch(ret)
	{
	case MRP_SUCCESS:
		ShowLineText(1,"��������ɹ���",255,255,255);
		return;
	case MRP_SEARCHFAILED:
		ShowLineText(1,"�޷������ļ���",255,255,255);
		break;
	case MRP_OPENFAILED:
		ShowLineText(1,"�޷����ļ���",255,255,255);
		break;
	case MRP_LISTLENFAILED:
		ShowLineText(1,"û���ҵ��ļ���",255,255,255);
		break;
	default:
		break;
	}
	mrpSetDisplayName(mrpPath, displayname);
	mrc_findStop(f);
	mrc_free(temp); //
	mrc_free(proDir); //
	mrc_free(temppath); //
	mrc_free(mrpPath); //
	mrc_free(tempfile); //
	mrc_free(assetsDir);
}