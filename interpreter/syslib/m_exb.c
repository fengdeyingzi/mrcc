#include "../src/interpreter.h"

//#include <time.h>
#include <mrc_base.h>
#include "xl_coding.h"
#include "m_exb.h"


/*
union AnyValue
{
    unsigned char Character;
    short ShortInteger;
    int Integer;
    long LongInteger;
    unsigned short UnsignedShortInteger;
    unsigned int UnsignedInteger;
    unsigned long UnsignedLongInteger;
    char *Identifier;
    char ArrayMem[2];               // 数据开始的占位符，它不指向
    struct ValueType *Typ;
    struct FuncDef FuncDef;
    struct MacroDef MacroDef;
#ifndef NO_FP
    double FP;
#endif
    void *Pointer;                  //unsafe native pointers
};
*/

/*
static void Lib_d(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = mrc_memcpy(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer);
}

static void Lib_ungzip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ungzipdata(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->UnsignedInteger);
}

static void Lib_unzip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = mr_unzip(Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Pointer, Param[3]->Val->Pointer);
}


static void Lib_fv_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = fv_init( Param[0]->Val->Integer);
}

static void Lib_fv_setType(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = fv_setType(Param[0]->Val->Pointer,  Param[1]->Val->Integer);
}

static void Lib_fv_beginView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = fv_beginView(Param[0]->Val->Pointer);
}

static void Lib_fv_getPath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = fv_getPath();
}

static void Lib_fv_end(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = fv_end();
}

static void Lib_clock(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = clock();
}

static void Lib_getKeyPressed(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = getKeyPressed(Param[0]->Val->Integer);
}
*/

void Lib_setPadType(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//setPadType(Param[0]->Val->Integer);
}

void Lib_setTextSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//mrc_setTextSize(Param[0]->Val->Integer,Param[1]->Val->Integer);
}
/*
void Lib_unZip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
unZip(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}


void Lib_motionSensorPowerOn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->Integer = mrc_motionSensorPowerOn();
}




void Lib_motionSensorPowerOff(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
 ReturnValue->Val->Integer = mrc_motionSensorPowerOff();
}


void Lib_motionSensorStop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->Integer =    mrc_motionSensorStopListen();
}


void Lib_motionSensorStart(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->Integer =  mrc_motionSensorStart(Param[0]->Val->Integer);
}

void Lib_getBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->Integer =  ex_getBitmap(Param[0]->Val->Integer);
}

void Lib_touch_isDown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->Integer =  touch_isDown(Param[0]->Val->Integer);
}

void Lib_touch_getX(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Integer =  touch_getX(Param[0]->Val->Integer);
}

void Lib_touch_getY(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Integer =  touch_getY(Param[0]->Val->Integer);
}
*/
void Lib_ex_coding(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Pointer =  xl_ex_coding(Param[0]->Val->Pointer,Param[1]->Val->Integer,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
}

const char exb_Defs[] = "\
typedef struct \
{\
 int x;\
 int y;\
 int z;\
} MOTION_ACC;\
";



static int index_num = 0;
static void AddString(PFunction ex_function,  char *func_text){
	
	exbFunctions[index_num].Func = ex_function;
	exbFunctions[index_num].Prototype = func_text;
	exbFunctions[index_num+1].Func = NULL;
	exbFunctions[index_num+1].Prototype = NULL;
	index_num++;
}

struct LibraryFunction exbFunctions[EXB_FUNCTIONS_NUM]; /*=
{
    {Lib_ungzip,          "int ungzipdata(uint8*, uint32*, uint8*, uint32);"},
		{Lib_unzip,          "int unzip(uint8*, int32, uint8**, int*);"},
	  {Lib_fv_init,         "int fv_init(int);" },	
	  {Lib_fv_setType,       "int fv_settype(char*,int);" },	
		{Lib_fv_beginView,     "int fv_begin(char*);" },	
		{Lib_fv_getPath,       "char *fv_getpath();" },	
		{Lib_fv_end,           "int fv_end();" },	
		{ Lib_clock,           "int clock();" },	
		{ Lib_getKeyPressed,      "int getkeypressed(int);" },	
		{Lib_setPadType,        "void setpadtype(int);"},
			  { Lib_setTextSize,  "void setTextSize(int,int);" },	
		  { Lib_unZip,          "void unZip(char*,char*);" },	
			  { Lib_motionSensorPowerOn,          "int sensorOn();" },	
			  { Lib_motionSensorPowerOff,         "int sensorOff();" },	
			  { Lib_motionSensorStop,             "int sensorStop();" },	
			  { Lib_motionSensorStart,            "int sensorStart(int);" },	
			  { Lib_getBitmap,         "int ex_getBitmap(int);" },	
		    { Lib_ex_coding,         "char* ex_coding(char*,int,char*,char*);" },
	{ Lib_touch_isDown,              "int touch_isdown(int);"},
	{ Lib_touch_getX,                "int touch_getx(int);"},
	{ Lib_touch_getY,                "int touch_gety(int);"},
		//	  { MathAcos,         "" },	
		//	  { MathAcos,         "" },	
		//	  { MathAcos,         "" },	
		//	  { MathAcos,         "" },	
		//	  { MathAcos,         "" },	
		
    { NULL,             NULL }
};*/

/* creates various system-dependent definitions */
void exbSetupFunc(void)
{
	index_num = 0;
 AddString(Lib_setPadType,        "void setpadtype(int);");
 AddString(Lib_ex_coding,         "char* ex_coding(char*,int,char*,char*);");
 AddString(Lib_setTextSize,  "void setTextSize(int,int);");
 
}
