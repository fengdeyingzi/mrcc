#ifndef _MRC_ANDROID_H_
#define _MRC_ANDROID_H_


extern void *mrc_readFileFromAssets(char *filename, int *len);
extern char* getAssetsDir(void);
extern void setAssetsDir(char *dir);

#endif