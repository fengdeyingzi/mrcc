#ifndef _MRC_ANDROID_H_
#define _MRC_ANDROID_H_

//��aastsĿ¼��ȡ�ļ�
extern void *mrc_readFileFromAssets(char *filename, int32 *len);

//�ͷ�assetsĿ¼��ȡ���ļ� �����ϣ�
void mrc_freeFileFromAssets(void *data,int32 len);


extern char* getAssetsDir(void);
extern void setAssetsDir(char *dir);

#endif