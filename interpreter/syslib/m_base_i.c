#include "interpreter.h"
#include <mrc_base_i.h>
#include <mrc_exb.h>
//#include "haning.h"
//#include "ext.h"
//#include "mrc_base_i.h "

void Lib_getSysInfo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_getSysInfo((mr_userinfo*)Param[0]->Val->Pointer);
}

void Lib_sendSms(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_sendSms((char*)Param[0]->Val->Pointer,(char*)Param[1]->Val->Pointer,Param[2]->Val->UnsignedInteger);
}

void Lib_call(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_call((char*)Param[0]->Val->Pointer);
}

void Lib_connectWAP(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_connectWAP((char*)Param[0]->Val->Pointer);
}

void Lib_plat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_plat(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger);
}
char PLAT_EX_CBTEXT[32];
void Lib_PLAT_EX_CB(uint8* output, int32 output_len)
{

}
void Lib_platEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_strcmp(PLAT_EX_CBTEXT,(char *)Param[5]->Val->Pointer);
	ReturnValue->Val->UnsignedInteger = mrc_platEx(Param[0]->Val->UnsignedInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedInteger,Param[3]->Val->Pointer,Param[4]->Val->Pointer, (MR_PLAT_EX_CB* )Lib_PLAT_EX_CB);
}


void Lib_getFixMrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer = mrc_getFixMrp(Param[0]->Val->UnsignedInteger);
}

void Lib_getFixMrpByName(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer = mrc_getFixMrpByName(Param[0]->Val->Pointer);
}


void Lib_encode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_encode(Param[0]->Val->Pointer,Param[1]->Val->UnsignedLongInteger,Param[2]->Val->Pointer);
}

void Lib_setReloadFile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_setReloadFile(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}

void Lib_getReloadFile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_getReloadFile(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}

void Lib_loadSmsCfg(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_loadSmsCfg();
}

void Lib_readSmsCfg(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_readSmsCfg(Param[0]->Val->UnsignedLongInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_setSmsCfg(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_setSmsCfg(Param[0]->Val->UnsignedLongInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_saveSmsCfg(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_saveSmsCfg();
}

void Lib_getMrParam(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer = mrc_getMrParam();
}

void Lib_getMrEntry(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer = mrc_getMrEntry();
}

void Lib_malloc8(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer = mrc_malloc8(Param[0]->Val->UnsignedInteger);
}

void Lib_free8(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_free8(Param[0]->Val->Pointer);
}
char timerCBtext[32];
void Lib_timerCB(int32 data)
{

}

void Lib_exitImmediately(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	strcmp(timerCBtext,(char *)Param[0]->Val->Pointer);
	mrc_exitImmediately(Lib_timerCB,Param[1]->Val->UnsignedInteger);
}


void Lib_getUserID(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_getUserID(Param[0]->Val->Pointer);
}

//void Lib_payment(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_payment();
//}

//void Lib_getAppInfoEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_getAppInfoEx(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
//}

void Lib_isZip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_isZip(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger);
}

void Lib_unzip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_unzip(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
}

void Lib_unzipVM(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_unzipVM(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
}

//void Lib_unzipVMEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_unzipVMEx(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
//}


void Lib_getExtGlobalMem(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_getExtGlobalMem();
}

void Lib_checkMrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_checkMrp(Param[0]->Val->Pointer);
}

//void Lib_checkMrpB(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_checkMrpB(Param[0]->Val->Pointer);
//}

void Lib_timerInit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_timerInit();
}

void Lib_extRecvAppEvent(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extRecvAppEvent(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger);
}

void Lib_extRecvAppEventEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extRecvAppEventEx(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger,Param[5]->Val->UnsignedInteger,Param[6]->Val->UnsignedInteger);
}

void Lib_extLoad(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	//ReturnValue->Val->UnsignedInteger = mrc_extLoad(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger);
}

void Lib_extFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extFree(Param[0]->Val->UnsignedInteger);
}

//void Lib_mrc_extLoadA(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extLoadA(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger);
//}

//
//void Lib_extFreeA(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extFreeA(Param[0]->Val->UnsignedInteger);
//}

void Lib_extFreeTimer(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extFreeTimer(Param[0]->Val->UnsignedInteger);
}

void Lib_extSetMode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_extSetMode(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger);
}
//
//void Lib_extFreeLater(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extFreeLater(Param[0]->Val->UnsignedInteger);
//}

void Lib_extInit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extInit(Param[0]->Val->UnsignedInteger);
}

void Lib_extEvent(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extEvent(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger);
}

void Lib_extPause(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extPause(Param[0]->Val->UnsignedInteger);
}

void Lib_extResume(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extResume(Param[0]->Val->UnsignedInteger);
}
//
//void Lib_extBlock(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extBlock(Param[0]->Val->UnsignedInteger);
//}
//
//void Lib_extUnblock(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extUnblock(Param[0]->Val->UnsignedInteger);
//}
//
//void Lib_extIsBlocked(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extIsBlocked(Param[0]->Val->UnsignedInteger);
//}

void Lib_extSendAppEvent(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extSendAppEvent(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger);
}

void Lib_extSendAppEventEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extSendAppEventEx(Param[0]->Val->UnsignedInteger,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger,Param[5]->Val->UnsignedInteger,Param[6]->Val->UnsignedInteger);
}

char mpsFpFuncTypetext[32];
int32 Lib_mpsFpFuncType(int32 p0, int32 p1, int32 p2, int32 p3, int32 p4, int32 p5)
{
return 0;
}

void Lib_extMpsFpCall(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	strcmp(mpsFpFuncTypetext,(char *)Param[1]->Val->Pointer);
	mrc_extMpsFpCall(Param[0]->Val->UnsignedInteger,Lib_mpsFpFuncType,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger,Param[5]->Val->UnsignedInteger,Param[6]->Val->UnsignedInteger,Param[7]->Val->UnsignedInteger);
}

void Lib_extInitMainModule(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = mrc_extInitMainModule();
}

char refreshScreenHook_ttext[32];
void Lib_refreshScreenHook_t(void)
{
}
//
//void Lib_regRefreshScreenHook(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	strcmp(mpsFpFuncTypetext,(char *)Param[0]->Val->Pointer);
//	mrc_regRefreshScreenHook(Lib_refreshScreenHook_t);
//}
//
//void Lib_extRWCntxSwitch(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_extRWCntxSwitch();
//}
//
//void Lib_extRWCntxRestore(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	mrc_extRWCntxRestore(Param[0]->Val->UnsignedInteger);
//}
//
//void Lib_pluginapp_checkExtVersion(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_pluginapp_checkExtVersion(Param[0]->Val->UnsignedInteger,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
//}
//
//void Lib_setScrBuf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	mrc_setScrBuf(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger);
//}
//
//void Lib_saveVM(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_saveVM(Param[0]->Val->Pointer);
//}
//
//void Lib_loadVM(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_loadVM();
//}
//
//void Lib_bmpBufferDrawold(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	mrc_bmpBufferDrawold(Param[0]->Val->UnsignedShortInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger,Param[5]->Val->UnsignedInteger,Param[6]->Val->UnsignedInteger,Param[7]->Val->UnsignedInteger,Param[8]->Val->UnsignedInteger);
//}
//
//void Lib_bmpShowold(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	mrc_bmpShowold(Param[0]->Val->Pointer,Param[1]->Val->UnsignedInteger,Param[2]->Val->UnsignedInteger,Param[3]->Val->UnsignedInteger,Param[4]->Val->UnsignedInteger,Param[5]->Val->UnsignedInteger,Param[6]->Val->UnsignedInteger);
//}
//
//void Lib_getStackInfo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
//{
//	ReturnValue->Val->UnsignedInteger = mrc_getStackInfo(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
//}

typedef void (*CFuncType)(struct ParseState *Parser, struct Value *, struct Value **, int);
   
const  char mrc_base_i_Defs[]=\
"typedef struct\
{uint8 IMEI[16];uint8 IMSI[16];char manufactory[8];char type[8];uint32 ver;uint8 spare[12];}userinfo;";
struct LibraryFunction base_i_Functions[50];

static void AddString(CFuncType func,  char *proto_type)
{
    static uint32 index = 0;

    if (index < 50/*MAX_STRING_FUNC_COUNT*/)
    {
        base_i_Functions[index].Func = func;
        base_i_Functions[index].Prototype = proto_type;
        index++;
    }
}
void base_i_init(void)
{
	//Haninit(mrc_base_i_Defs);

	AddString(Lib_getSysInfo,"int32 getSysInfo(userinfo*);");

	AddString(Lib_sendSms,"int32 sendSms(char*,char*,int32);");

	AddString(Lib_call,"void call(char*);");

	AddString(Lib_connectWAP,"void connectWAP(char*);");

	AddString(Lib_plat,"int32 plat(int32,int32);");

	AddString(Lib_platEx,"int32 platEx(int32,uint8*,int32,uint8**,int32*,char*);");

	AddString(Lib_getFixMrp,"uint8* getFixMrp(int32);");

	AddString(Lib_getFixMrpByName,"uint8* getFixMrpByName(char*);");

	AddString(Lib_encode,"int32 encode(uint8*,uint32,uint8*);");

	AddString(Lib_setReloadFile,"int32 setReloadFile(char*,char*);");

	AddString(Lib_getReloadFile,"int32 getReloadFile(char**,char**);");

	AddString(Lib_loadSmsCfg,"int32 loadSmsCfg();");

	AddString(Lib_readSmsCfg,"int32 readSmsCfg(int32,char*,int32);");

	AddString(Lib_setSmsCfg,"int32 setSmsCfg(int32,char*,int32);");

	AddString(Lib_saveSmsCfg,"int32 saveSmsCfg();");

	AddString(Lib_getMrParam,"char* getMrParam();");

	AddString(Lib_getMrEntry,"char* getMrEntry();");

	AddString(Lib_malloc8,"void* malloc8(int);");

	AddString(Lib_free8,"void free8(void*);");

	AddString(Lib_exitImmediately,"void exitImmediately(char*,int32);");

	AddString(Lib_getUserID,"int32 getUserID(uint8**);");

	AddString(Lib_isZip,"int32 isZip(uint8*,int32);");

	AddString(Lib_unzip,"int32 unzip(uint8*,int32,uint8**,int32*);");

	AddString(Lib_unzipVM,"int32 unzipVM(uint8*,int32,uint8**,int32*);");

	AddString(Lib_getExtGlobalMem,"int32 getExtGlobalMem();");

	AddString(Lib_checkMrp,"int32 checkMrp(char*);");

	AddString(Lib_timerInit,"int32 timerInit();");

	AddString(Lib_extRecvAppEvent,"int32 extRecvAppEvent(int32,int32,int32,int32);");

	AddString(Lib_extRecvAppEventEx,"int32 extRecvAppEventEx(int32,int32,int32,int32,int32,int32,int32);");

	AddString(Lib_extLoad,"int32 extLoad(uint8*,int32);");

	AddString(Lib_extFree,"int32 extFree(int32);");

	AddString(Lib_extFreeTimer,"int32 extFreeTimer(int32);");

	AddString(Lib_extSetMode,"int32 extSetMode(int32,int32);");

//	AddString(Lib_extFreeLater,"int32 extFreeLater(int32);");

	AddString(Lib_extInit,"int32 extInit(int32);");

	AddString(Lib_extEvent,"int32 extEvent(int32,int32,int32,int32);");

	AddString(Lib_extPause,"int32 extPause(int32);");

	AddString(Lib_extResume,"int32 extResume(int32);");

	AddString(Lib_extSendAppEvent,"int32 extSendAppEvent(int32,int32,int32,int32);");

	AddString(Lib_extSendAppEventEx,"int32 extSendAppEventEx(int32,int32,int32,int32,int32,int32,int32);");

	AddString(Lib_extMpsFpCall,"int32 extMpsFpCall(int32,char*,int32,int32,int32,int32,int32,int32);");

	AddString(Lib_extInitMainModule,"int32 extInitMainModule();");

  AddString(NULL, NULL);


}