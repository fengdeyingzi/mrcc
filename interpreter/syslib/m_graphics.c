//#include "haning.h"
//#include "mrc_bmp.h"
//#include "mrc_graphics.h "

#include "../src/interpreter.h"
#include <mrc_base.h>
#include "mrc_graphics.h"
/*
void Lib_RectRe(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	RectRe(Param[0]->Val->Pointer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer);
}
void Lib_Rectlinepd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	Rectlinepd(Param[0]->Val->Pointer);
}

void Lib_Intersect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Integer = Intersect(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}
void Lib_pointpd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Integer = pointpd(Param[0]->Val->Integer,Param[1]->Val->Integer);
}
void Lib_sectRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	sectRect(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
}

void Lib_gr_cls(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_cls(*(mr_colourSt*)Param[0]->Val->Pointer);
}

void Lib_gr_point(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_point(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->UnsignedShortInteger);
}
void Lib_gr_pointex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_pointex(Param[0]->Val->Integer,Param[1]->Val->Integer,*(mr_colourSt*)Param[2]->Val->Pointer);
}

void Lib_gr_line(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_line(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,*(mr_colourSt*)Param[4]->Val->Pointer);
}

void Lib_gr_rect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_rect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,*(mr_colourSt*)Param[4]->Val->Pointer);
}

void Lib_gr_fill_area(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_fill_area(Param[0]->Val->Pointer,Param[1]->Val->Integer,*(mr_colourSt*)Param[2]->Val->Pointer);
}


void Lib_gr_bigger(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_bigger(Param[0]->Val->Pointer,Param[1]->Val->Integer,*(mr_colourSt*)Param[2]->Val->Pointer);
}

void Lib_gr_Circle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_Circle(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,*(mr_colourSt*)Param[3]->Val->Pointer);
}

void Lib_gr_Ellipse(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_Ellipse(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,*(mr_colourSt*)Param[4]->Val->Pointer);
}

void Lib_getpixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->UnsignedInteger = getpixel(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

void Lib_gr_Flood_Fill_4(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_Flood_Fill_4(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->UnsignedShortInteger,Param[3]->Val->UnsignedShortInteger);
}

void Lib_gr_set_clip_rect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_set_clip_rect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

void Lib_gr_graph(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_graph();
}

void Lib_gr_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_init();
}

void Lib_gr_close(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	gr_close();
}

////////////////////////////
const  char mrc_graphics_Defs[] = "\
typedef struct{int left;int top;int width;int height;}RECT;\n\
typedef struct{int x;int y;}EACH_POINT;\
";

int32 graphics_init()
{
	Haninit(&mrc_graphics_Defs[0]);

	AddString(Lib_RectRe,"void RectRe(RECT*,int,int,int,int);");
	AddString(Lib_Rectlinepd,"void Rectlinepd(RECT*);");
	AddString(Lib_Intersect,"int Intersect(RECT*,RECT*);");
	AddString(Lib_pointpd,"int pointpd(int,int);");
	AddString(Lib_sectRect,"void sectRect(RECT*,RECT*,RECT*);");
	AddString(Lib_gr_cls,"void gr_cls(mr_colourSt*);");
	AddString(Lib_gr_point,"void gr_point(int,int,uint16);");
	AddString(Lib_gr_pointex,"void gr_pointex(int,int,mr_colourSt*);");
	AddString(Lib_gr_line,"void gr_line(int,int,int,int,mr_colourSt*);");
	AddString(Lib_gr_rect,"void gr_rect(int,int,int,int,mr_colourSt*);");
	AddString(Lib_gr_fill_area,"void gr_fill_area(EACH_POINT*,int,mr_colourSt*);");
	AddString(Lib_gr_bigger,"void gr_bigger(EACH_POINT*,int,mr_colourSt*) ;");
	AddString(Lib_gr_Circle,"void gr_Circle(int,int,int,mr_colourSt*);");
	AddString(Lib_gr_Ellipse,"void gr_Ellipse(int,int,int,int,mr_colourSt*);");
	AddString(Lib_getpixel,"uint16 getpixel(int,int);");
	AddString(Lib_gr_Flood_Fill_4,"int32 gr_flood_fill_4(int,int,uint16,uint16);");
	AddString(Lib_gr_set_clip_rect,"void gr_set_clip_rect(int,int,int,int);");
	AddString(Lib_gr_graph,"void gr_graph();");
	AddString(Lib_gr_init,"void gr_init();");
	AddString(Lib_gr_close,"void gr_close();");





	return hanclose();

}
*/






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
    void *Pointer;                  // unsafe native pointers
};

*/

void Lib_readBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer = (int)readBitmap565( Param[0]->Val->Pointer);
}

void Lib_readBitmapFromAssets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer = (int)readBitmap565FromAssets( Param[0]->Val->Pointer);
}

void Lib_drawBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawBitmap565((BITMAP_565*)Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Integer);
}

void Lib_bitmapFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =bitmap565Free((BITMAP_565*)Param[0]->Val->Integer);
}
void Lib_drawBitmapFlip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ReturnValue->Val->Integer = drawBitmap565Flip((BITMAP_565*)Param[0]->Val->Integer, Param[1]->Val->Integer,  Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer, Param[6]->Val->Integer);
}


/*
void Lib_createBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =
	 createBitmap(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

void Lib_clipBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =clipBitmap(Param[0]->Val->Integer,  Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer);
}



void Lib_drawBitmapEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawBitmapEx(Param[0]->Val->Integer, 
	 Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	 Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer);
}

void Lib_drawBitmapExb(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   drawBitmapExb(Param[0]->Val->Integer,
	 Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	 Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer);
}

void Lib_drawBitmapExc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   drawBitmapExc(Param[0]->Val->Integer,
	 Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	 Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer,
	 Param[9]->Val->Integer,Param[10]->Val->Integer, Param[11]->Val->Integer, Param[12]->Val->Integer);
}



void Lib_whiteBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs){
    whiteBitmap(Param[0]->Val->Integer, Param[1]->Val->Integer);
}



void Lib_saveBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =saveBitmap(Param[0]->Val->Integer, Param[1]->Val->Pointer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

void Lib_drawBitmapOld(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ReturnValue->Val->Integer = drawBitmapOld(Param[0]->Val->Integer, Param[1]->Val->Integer,  Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer, Param[6]->Val->Integer, Param[7]->Val->Integer);
}


void Lib_drawBitmapAlpha(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
 ReturnValue->Val->Integer = drawBitmapAlpha(Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

void Lib_drawBitmapRotate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param,int NumArgs)
{
 ReturnValue->Val->Integer = drawBitmapRotate(Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer,Param[6]->Val->Integer);
}

void Lib_bitmapGetInfo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =bitmapGetInfo( Param[0]->Val->Integer,Param[1]->Val->Pointer);
}

void Lib_bitmapGetPixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =bitmapGetPixel( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer);
}

void Lib_bitmapSetPixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   bitmapSetPixel( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}

static void Lib_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawRect( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer);
}

static void Lib_drawCir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawCir( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}


static void Lib_clipRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
 ReturnValue->Val->Integer=  clipRect( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}
*/
const char bitmap_Defs[] = "\
enum\
{\
 _JPG=0,\
 _PNG=1,\
 _BMP16=2\
};\
typedef struct \
{\
unsigned int width; \
unsigned int height; \
unsigned int stride;\
int format; \
unsigned int flags;\
void *ptr; \
} BITMAPINFO;\
";



struct LibraryFunction bitmapFunctions[6];
/*
 =
{
   // { MathAcos,         "float acos(float);" },
   // {Lib_createBitmap ,               "int createBitmap(int,int);" },
		{Lib_readBitmap ,               "int readBitmap(char*);" },
	 // {Lib_clipBitmap ,               "int clipBitmap(int,int,int,int,int);" },
		{Lib_drawBitmap ,               "void drawBitmap(int,int,int);" },
	//	{Lib_drawBitmapEx ,               "void drawBitmapEx(int,int,int,int,int,int,int,int,int);" },
		//{Lib_drawBitmapExb ,               "void drawBitmapExb(int,int,int,int,int,int,int,int,int);" },
	//	{Lib_drawBitmapExc ,               "void drawBitmapExc(int,int,int,int,int,int,int,int,int,int,int,int,int);" },
	//  {Lib_whiteBitmap,                      "void whiteBitmap(int,int);"},
	  {Lib_bitmapFree ,               "int bitmapFree(int);" },
	//  {Lib_saveBitmap ,               "int saveBitmap(int,char*,int,int);" },
	//	{Lib_drawBitmapOld,             "int drawBitmapOld(int,int,int,int,int,int,int,int);"},
		{Lib_drawBitmapFlip,           "int drawBitmapFlip(int,int,int,int,int,int,int);"},
	//	{Lib_drawBitmapAlpha,          "int drawBitmapAlpha(int,int,int,int);"},
	//	{Lib_drawBitmapRotate,         "int drawBitmapRotate(int,int,int,int,int,int,int);"},
		
		 
		{Lib_readBitmapFromAssets,      "int readBitmapFromAssets(char*);"},
	//	{Lib_bitmapGetInfo,             "int bitmapGetInfo(int,BITMAPINFO*);"},
	//	{Lib_bitmapGetPixel,           "int bitmapGetPixel(int,int,int);"},
	//	{Lib_bitmapSetPixel,           "void bitmapSetPixel(int,int,int,int);"},

	//	{Lib_drawRect,                "void drawRect(int,int,int,int,int);"},
	//	{Lib_drawCir,                 "void drawCir(int,int,int,int);"},
	//	{Lib_clipRect,                "int clipRect(int,int,int,int);"},
    { NULL,             NULL }
};
*/

/* creates various system-dependent definitions */
void bitmapSetupFunc(void)
{
	bitmapFunctions[0].Func = Lib_readBitmap;
	bitmapFunctions[0].Prototype = "int readBitmap(char*);";
	
	bitmapFunctions[1].Func = Lib_drawBitmap;
	bitmapFunctions[1].Prototype = "void drawBitmap(int,int,int);";
	
	bitmapFunctions[2].Func = Lib_drawBitmapFlip;
	bitmapFunctions[2].Prototype = "int drawBitmapFlip(int,int,int,int,int,int,int);";
	
	bitmapFunctions[3].Func = Lib_readBitmapFromAssets;
	bitmapFunctions[3].Prototype = "int readBitmapFromAssets(char*);";
	
	bitmapFunctions[4].Func = Lib_bitmapFree;
	bitmapFunctions[4].Prototype = "int bitmapFree(int);";
	
	bitmapFunctions[5].Func = NULL;
	bitmapFunctions[5].Prototype = NULL;
 /*
    VariableDefinePlatformVar(NULL, "M_E", &FPType, (union AnyValue *)&M_EValue, FALSE);
    VariableDefinePlatformVar(NULL, "M_LOG2E", &FPType, (union AnyValue *)&M_LOG2EValue, FALSE);
	*/
}


