//#include "haning.h"
//#include "ext.h"
#include "../src/interpreter.h"
#include "m_net.h"
#include "picoc.h"
#include <mrc_base.h>
#include <mrc_network.h>

char getHostCB[32];
char initNetworkCB[32];
char Source[256];

int32 FuncRet_NET;

static int index_num = 0;
static void AddString(PFunction ex_function,  char *func_text){
	
	netFunctions[index_num].Func = ex_function;
	netFunctions[index_num].Prototype = func_text;
	netFunctions[index_num+1].Func = NULL;
	netFunctions[index_num+1].Prototype = NULL;
	index_num++;
}

int32 GET_HOST_CB(int32 ip)
{
	FuncRet_NET=ip;//FuncRet_NET是内部符号_ret
    if(CheckBaseCall(getHostCB,&IntType,1))//检查函数是否符合要求
    {
        ProgramFail(NULL, "无法使用%s",getHostCB);
    }
    mrc_sprintf(Source,"_ret=%s(_ret);",getHostCB);
    PicocParse(" ", Source, strlen(Source), TRUE, TRUE, FALSE);
	return FuncRet_NET;
}

void Lib_GetHostByName(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    mrc_strcpy(getHostCB,Param[1]->Val->Pointer);
    ReturnValue->Val->LongInteger = mrc_getHostByName(Param[0]->Val->Pointer, GET_HOST_CB);
}

int32 INIT_NETWORK_CB(int32 result)
{
	FuncRet_NET=result;//FuncRet_NET是内部符号_ret
    if(CheckBaseCall(initNetworkCB,&IntType,1))//检查函数是否符合要求
    {
        ProgramFail(NULL, "无法使用%s",initNetworkCB);
    }
    mrc_sprintf(Source,"_ret=%s(_ret);",initNetworkCB);
    PicocParse(" ", Source, strlen(Source), TRUE, TRUE, FALSE);
    return FuncRet_NET;
}
void Lib_InitNetwork(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_strcpy(initNetworkCB,Param[0]->Val->Pointer);
    ReturnValue->Val->LongInteger = mrc_initNetwork(INIT_NETWORK_CB, Param[1]->Val->Pointer);
}

void Lib_GetNetworkID(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_getNetworkID();
}

void Lib_GetNetworkType(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = 0; //mrc_getNetworkType();
}
		
void Lib_CloseNetwork(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger =mrc_closeNetwork();
}

void Lib_Socket(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_socket(Param[0]->Val->LongInteger, Param[1]->Val->LongInteger);
}
void Lib_Connect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_connect(Param[0]->Val->LongInteger, Param[1]->Val->LongInteger,
        Param[2]->Val->UnsignedShortInteger, Param[3]->Val->LongInteger);
}
void Lib_GetSocketState(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_getSocketState(Param[0]->Val->LongInteger);
}
void Lib_CloseSocket(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_closeSocket(Param[0]->Val->LongInteger);
}

void Lib_Recv(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_recv(Param[0]->Val->LongInteger, Param[1]->Val->Pointer, Param[2]->Val->Integer);
}
void Lib_Send(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_send(Param[0]->Val->LongInteger, Param[1]->Val->Pointer, Param[2]->Val->Integer);
}

void Lib_Recvfrom(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_recvfrom(Param[0]->Val->LongInteger, Param[1]->Val->Pointer, Param[2]->Val->Integer
        ,Param[3]->Val->Pointer, Param[4]->Val->Pointer);
}
void Lib_Sendto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger = mrc_sendto(Param[0]->Val->LongInteger, Param[1]->Val->Pointer, Param[2]->Val->Integer
        ,Param[3]->Val->LongInteger, Param[4]->Val->UnsignedShortInteger);
}

#define  MAX_NET_COUNT 13

const char net_Defs[] = "\
  \
";



struct LibraryFunction netFunctions[MAX_NET_COUNT+1];
/*=
{
	
  	{Lib_InitNetwork,  "int initnetwork(char*,char*);"},
    {Lib_Recv,         "int recv(int,char*,int);"},
    {Lib_Send,         "int send(int,char*,int);"},
  	{Lib_Sendto,      "int sendto(int,char*,int,int,uint16);"},
	  {Lib_Connect,     "int connect(int,int,int,int);"},
    {Lib_GetSocketState,  "int getsocketstate(int);"},
    {Lib_CloseSocket,     "int closesocket(int);"},
    {Lib_GetNetworkID,    "int getnetworkid();"},
    {Lib_GetNetworkType,  "int getnetworktype();"},
    {Lib_Recvfrom,        "int recvfrom(int,char*,int,int*,uint16*);"},
    {Lib_Socket,          "int socket(int,int);"},
    {Lib_CloseNetwork,    "int closenetwork();"},
    {Lib_GetHostByName,   "int gethostbyname(char*,char*);"},


	
	
	{NULL,      NULL}
};
*/
void netSetupFunc()
{
	
	// Haninit(NULL);
    index_num = 0;

	AddString(Lib_InitNetwork,"int initnetwork(char*,char*);");
    AddString(Lib_Recv,"int recv(int,char*,int);");
    AddString(Lib_Send,"int send(int,char*,int);");
	AddString(Lib_Sendto,"int sendto(int,char*,int,int,uint16);");
	AddString(Lib_Connect,"int connect(int,int,int,int);");
    AddString(Lib_GetSocketState,"int getsocketstate(int);");
    AddString(Lib_CloseSocket,"int closesocket(int);");
    AddString(Lib_GetNetworkID,"int getnetworkid();");
    AddString(Lib_GetNetworkType,  "int getnetworktype();");
    AddString(Lib_Recvfrom,"int recvfrom(int,char*,int,int*,uint16*);");
    AddString(Lib_Socket,"int socket(int,int);");
    AddString(Lib_CloseNetwork,"int closenetwork();");
    AddString(Lib_GetHostByName,"int gethostbyname(char*,char*);");


	return ;

}

