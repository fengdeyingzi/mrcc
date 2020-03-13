#ifndef _MRC_ANDROID_H_
#define _MRC_ANDROID_H_

//从aasts目录读取文件
extern void *mrc_readFileFromAssets(char *filename, int32 *len);

//释放assets目录读取的文件 （作废）
void mrc_freeFileFromAssets(void *data,int32 len);


extern char* getAssetsDir(void);
extern void setAssetsDir(char *dir);

#endif