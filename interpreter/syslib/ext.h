#ifndef __EXT_H__
#define __EXT_H__
#include <haning.H>

enum{
	EXT_FUNCRET,
	EXT_INTTYPE,
	EXT_FPTYPE,

	EXT_CHECKBASECALL,
	EXT_PROGRMFAIL,
	EXT_PICOCPARSE,
	EXT_VARIABLE,

	EXT_END
};
#ifndef __HELLOWORLD_H__
extern int32 ext_hanev(int32 code,int32 p0,int32 p1,int32 p2,int32 p3,int32 p4);

#define FuncRet  *((int*)ext_hanev(EXT_FUNCRET,0,0,0,0,0))
#define IntType  *((struct ValueType*)ext_hanev(EXT_INTTYPE,0,0,0,0,0))
#define FPType  *((struct ValueType*)ext_hanev(EXT_FPTYPE,0,0,0,0,0))

#define CheckBaseCall(e1,e2,e3)  (int)ext_hanev(EXT_CHECKBASECALL,(int32)e1,(int32)e2,(int32)e3,0,0)
#define ProgramFail(e1,e2,e3)  (int)ext_hanev(EXT_PROGRMFAIL,(int32)e1,(int32)e2,(int32)e3,0,0)
#define PicocParse(e1,e2,e3,e4,e5,e6)  (int)ext_hanev(EXT_PICOCPARSE,(int32)e1,(int32)e2,(int32)e3,(int32)e4,(int32)e5)
#define VariableDefinePlatformVar(e1,e2,e3,e4,e5) (int)ext_hanev(EXT_VARIABLE,(int32)e1,(int32)e2,(int32)e3,(int32)e4,(int32)e5)

#endif
#endif