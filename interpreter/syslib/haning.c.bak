#include "haning.h"

hanint handata;
uint32 index = 0;
MR_HAN EXT_HAN,*EXT_HANEX;

extern uint16 * w_getScreenBuffer(void);
int hange;
HJGFuns hjglin;
HJGFunsp hjgopg;
void Haninit(const char *Defs)
{
	hjglin.Functions.Prototype=(char *)Defs;
	hjglin.next=NULL;
	hjgopg=&hjglin;
	index=0;
}
int yy=0;

void tishiss(char *text)
{
	int32 f;
	if(!text)
		return;
	f=mrc_open("print.txt",12);
	if(f>0)
	{
		mrc_seek(f,0,2);
		mrc_write(f,text,strlen(text));
		mrc_write(f,"\r\n",strlen("\r\n"));
		mrc_close(f);
	}
	yy=yy>320?0:yy;
	mrc_drawRect(0,yy*20,240,20,0,0,0);
	mrc_drawText(text,0,yy*20,255,255,255,0,1);
	yy++;
	mrc_refreshScreen(0,yy*20,240,20);

}
void AddString(CFuncType func, const char *proto_type)
{
	HJGFunsp now=mrc_malloc(sizeof(HJGFuns));
	now->Functions.Func=func;
	now->Functions.Prototype=(char *)proto_type;
	now->next=NULL;
	hjgopg->next=now;
	hjgopg=now;
	hange++;
}

int32 hanclose()
{
	int i=0;
	HJGFunsp temp,temp2;
	struct HJG *P=malloc(sizeof(struct HJG));
	P->Defs=hjglin.Functions.Prototype;
	P->Functions=mrc_malloc(sizeof(struct LibraryFunction)*(hange+1));

	temp2=temp=hjglin.next;
	while(temp)
	{
		P->Functions[i++]=temp->Functions;
		temp=temp->next;
		mrc_free(temp2);
		temp2=temp;
	}
	memset(&P->Functions[i],0,sizeof(struct LibraryFunction));
	EXT_HANEX=&EXT_HAN;
	P->zhuan=&EXT_HANEX;
	return (int32)P;
}

int32 ext_appEventinit(int32 code, int32 param0, int32 param1)
{
	//(*EXT_HAN)=(MR_HAN)param0;
	return MR_IGNORE;
}

int32 ext_hanev(int32 code,int32 p0,int32 p1,int32 p2,int32 p3,int32 p4)
{
	if(EXT_HAN)
		return EXT_HAN(code,p0,p1,p2,p3,p4);
	return 0;
}