#ifndef _FILERW_H_
#define _FILERW_H_
#include <mrc_base.h>

int32 ReadMrp(const char *mFile);
int32 SaveMrp(const char *mFile);
int32 mrpReplaceFile(const char *MrpFile, char *filename, char *conname);
int32 mrpSetDisplayName(const char *MrpFile,const char *displayname);
int32 mrpAddFile(const char *MrpFile, char *filename);
char *getParamPath(char *path);
int32 packProject(char *path);
#endif
