#ifndef _HANING_H_
#define _HANING_H_

#include "..\src\picoc.h"

typedef int32 (*MR_HAN)(int32 code,int32 p0,int32 p1,int32 p2,int32 p3,int32 p4);
extern int hange;
#define  HANGE hange

struct HJG
{
	struct LibraryFunction *Functions;
	const char *Defs;
	MR_HAN **zhuan;
};
typedef struct HJGFunctions
{
	struct LibraryFunction Functions;
	struct HJGFunctions *next;
}HJGFuns,*HJGFunsp;
void Haninit(const char *Defs);
int32 hanclose();
void AddString(CFuncType func, const char *proto_type);
int32 ext_appEventinit(int32 code, int32 param0, int32 param1);
int32 ext_hanev(int32 code,int32 p0,int32 p1,int32 p2,int32 p3,int32 p4);

void tishiss(char *a);


#endif