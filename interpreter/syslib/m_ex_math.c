#include "interpreter.h"
#include <math.h>
#include "ex_math.h"
#include "m_ex_math.h"
//#ifndef BUILTIN_MINI_STDLIB
//#ifndef NO_FP

	
	static	void Lib_isPointCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ex_isPointCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer);
}

static	void Lib_IsCircleCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ex_IsCircleCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer, Param[6]->Val->Integer);
}

static	void Lib_isCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_isCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer, Param[6]->Val->Integer,Param[7]->Val->Integer);
}
static	void Lib_toSpan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ex_toSpin(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer, Param[4]->Val->Integer,  Param[5]->Val->Pointer, Param[6]->Val->Pointer);
}


static	void Lib_getLineSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_getLineSize(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}
static	void Lib_getRadiam(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_getRadiam(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}


static int index_num = 0;
static void AddFunction(PFunction ex_function,  char *func_text){
	
	Ex_MathFunctions[index_num].Func = (PFunction)ex_function;
	Ex_MathFunctions[index_num].Prototype = func_text;
	Ex_MathFunctions[index_num+1].Func = NULL;
	Ex_MathFunctions[index_num+1].Prototype = NULL;
	index_num++;
}

	struct LibraryFunction Ex_MathFunctions[MAX_MATHFUNCTIONS]; /*=
{
	{Lib_isPointCollisionRect,    "int isPointCollRect(int,int,int,int,int,int);"},
	{Lib_IsCircleCollisionRect,   "int isCirCollRect(int,int,int,int,int,int,int);"},
    { Lib_isCollisionRect,           "int isCollRect(int,int,int,int,int,int,int,int);" },
    { Lib_toSpan,            "int toSpin(int,int,int,int,int,int*,int*);" },
	{ Lib_getLineSize,            "int getLineSize(int,int,int,int);" },
	{ Lib_getRadiam,         "int getRadiam(int,int,int,int);" },
    {NULL,NULL}
 };*/

 
 void Ex_MathSetupFunc(void)
 {
	 index_num = 0;
	 AddFunction(Lib_isPointCollisionRect, "int isPointCollRect(int,int,int,int,int,int);");
	 AddFunction(Lib_IsCircleCollisionRect, "int isCirCollRect(int,int,int,int,int,int,int);");
	 AddFunction(Lib_isCollisionRect, "int isCollRect(int,int,int,int,int,int,int,int);");
	 AddFunction(Lib_toSpan, "int toSpin(int,int,int,int,int,int*,int*);");
	 AddFunction(Lib_getLineSize, "int getLineSize(int,int,int,int);");
	 AddFunction(Lib_getRadiam, "int getRadiam(int,int,int,int);");
	 
 }
