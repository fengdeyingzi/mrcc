
#include "interpreter.h"
#include "readSprite.h"
#include "world.h"
#include "camera.h"
#include "m_ex_game.h"



static	void Lib_sp_read(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = sp_read(Param[0]->Val->Identifier,Param[1]->Val->Integer);
}


static	void Lib_sp_setDraw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_setDraw(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_sp_isDraw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_isDraw(Param[0]->Val->Integer);
}


static	void Lib_sp_getId(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getId(Param[0]->Val->Integer);
}

static	void Lib_sp_setId(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_setId(Param[0]->Val->Integer,Param[1]->Val->Integer);
}


static	void Lib_sp_copy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = sp_copy(Param[0]->Val->Integer);
}


static	void Lib_sp_getFrame(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getFrame(Param[0]->Val->Integer);
}

static	void Lib_sp_setAction(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_setAction(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_sp_getAction(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getAction(Param[0]->Val->Integer);
}

static	void Lib_sp_getx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getx(Param[0]->Val->Integer);
}

static	void Lib_sp_gety(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_gety(Param[0]->Val->Integer);
}

static	void Lib_sp_setxy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_setxy(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}


static	void Lib_sp_move(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_move(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}

static	void Lib_sp_getWidth(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getWidth(Param[0]->Val->Integer);
}

static	void Lib_sp_getHeight(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_getHeight(Param[0]->Val->Integer);
}

static	void Lib_sp_impact(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_impact(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}

static	void Lib_sp_crash(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_crash(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_sp_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_draw(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

static	void Lib_sp_run(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    sp_run(Param[0]->Val->Integer);
}

static	void Lib_sp_free(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)sp_free(Param[0]->Val->Integer);
}

static	void Lib_world_create(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_create();
}

static	void Lib_world_addSprite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_addSprite(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_world_removeSprite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_removeSprite(Param[0]->Val->Integer,Param[1]->Val->Integer);
}


static	void Lib_world_setCamera(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_setCamera(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_world_draw(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_draw(Param[0]->Val->Integer);
}


static	void Lib_world_run(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_run(Param[0]->Val->Integer);
}

static	void Lib_world_rank(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_rank(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static	void Lib_world_free(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)world_free(Param[0]->Val->Integer);
}


static	void Lib_ca_create(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_create(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

static	void Lib_ca_setxy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_setxy(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}

static	void Lib_ca_getx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_getx(Param[0]->Val->Integer);
}

static	void Lib_ca_gety(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_gety(Param[0]->Val->Integer);
}

static	void Lib_ca_move(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_move(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}



static	void Lib_ca_free(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ca_free(Param[0]->Val->Integer);
}







const char game_Defs[] = "\
  \
";



	struct LibraryFunction Ex_GameFunctions[EX_GAME_FUNSIZE]; /*=
{
	
		//	{ Lib_sp_getAction,         "int sp_getAction(int,int,int,int);" },
	{ Lib_ca_create,         "int ca_create(int,int,int,int);" },
	{ Lib_ca_setxy,         "int ca_setxy(int,int,int);" },
	{ Lib_ca_getx,         "int ca_getx(int);" },
	{ Lib_ca_gety,         "int ca_gety(int);" },
	{ Lib_ca_move,         "int ca_move(int,int,int);" },
	{ Lib_ca_free,         "int ca_free(int);" },
	
	{Lib_sp_read,        "int sp_read(char*,int);"},
		{Lib_sp_setDraw,   "int sp_setDraw(int,int);"},
	{Lib_sp_isDraw,      "int sp_isDraw(int);"},
    { Lib_sp_getId ,          "int sp_getId(int);" },
		    { Lib_sp_setId ,          "int sp_setId(int,int);" },
    { Lib_sp_copy,            "int sp_copy(int);" },
		{Lib_sp_getFrame,         "int sp_getFrame(int);"},
		{ Lib_sp_setAction,            "int sp_setAction(int,int);" },
		
		{ Lib_sp_getAction,         "int sp_getAction(int);" },
		{ Lib_sp_getx,             "int sp_getx(int);" },
		{ Lib_sp_gety,             "int sp_gety(int);" },
		{ Lib_sp_setxy,            "int sp_setxy(int,int,int);" },
		{ Lib_sp_move,             "int sp_move(int,int,int);" },
		
				{ Lib_sp_getWidth,         "int sp_getWidth(int);" },
				{ Lib_sp_getHeight,         "int sp_getHeight(int);" },
				{ Lib_sp_impact,           "int sp_impact(int,int,int);" },
				{ Lib_sp_crash,            "int sp_crash(int,int);" },
				{ Lib_sp_draw,             "int sp_draw(int,int);" },
				
				{ Lib_sp_run,              "void sp_run(int);" },
				{ Lib_sp_free,             "int sp_free(int);" },
				{ Lib_world_create,         "int world_create();" },
				{ Lib_world_addSprite,         "int world_addSprite(int,int);" },
				{ Lib_world_removeSprite,      "int world_removeSprite(int,int);"},
				{ Lib_world_setCamera,         "int world_setCamera(int,int);" },
				
				{ Lib_world_draw,             "int world_draw(int);" },
				{ Lib_world_run,             "int world_run(int);" },
				{Lib_world_rank,             "int world_rank(int,int);"},
						{ Lib_world_free,         "int world_free(int);" },
    {NULL,NULL}
 };
*/
static int index_num = 0;
static void AddFunction(PFunction ex_function,  char *func_text){
	
	Ex_GameFunctions[index_num].Func = (PFunction)ex_function;
	Ex_GameFunctions[index_num].Prototype = func_text;
	Ex_GameFunctions[index_num+1].Func = NULL;
	Ex_GameFunctions[index_num+1].Prototype = NULL;
	index_num++;
}
 
 void Ex_GameSetupFunc(void)
 {
	 index_num = 0;
	AddFunction( Lib_ca_create,         "int ca_create(int,int,int,int);" );
	AddFunction(Lib_ca_setxy,         "int ca_setxy(int,int,int);" );
	AddFunction(Lib_ca_getx,         "int ca_getx(int);" );
	AddFunction(Lib_ca_gety,         "int ca_gety(int);" );
    AddFunction(Lib_ca_move,         "int ca_move(int,int,int);" );
	AddFunction(Lib_ca_free,         "int ca_free(int);" );
	
	AddFunction(Lib_sp_read,        "int sp_read(char*,int);");
	AddFunction(Lib_sp_setDraw,   "int sp_setDraw(int,int);");
	AddFunction(Lib_sp_isDraw,      "int sp_isDraw(int);");
    AddFunction( Lib_sp_getId ,          "int sp_getId(int);" );
	AddFunction(Lib_sp_setId ,          "int sp_setId(int,int);" );
    AddFunction(Lib_sp_copy,            "int sp_copy(int);" );
	AddFunction(Lib_sp_getFrame,         "int sp_getFrame(int);");
	AddFunction( Lib_sp_setAction,            "int sp_setAction(int,int);" );
		
	AddFunction(Lib_sp_getAction,         "int sp_getAction(int);" );
	AddFunction( Lib_sp_getx,             "int sp_getx(int);" );
	AddFunction(Lib_sp_gety,             "int sp_gety(int);" );
	AddFunction(Lib_sp_setxy,            "int sp_setxy(int,int,int);" );
	AddFunction(Lib_sp_move,             "int sp_move(int,int,int);" );
		
	AddFunction(Lib_sp_getWidth,         "int sp_getWidth(int);" );
	AddFunction(Lib_sp_getHeight,         "int sp_getHeight(int);" );
	AddFunction(Lib_sp_impact,           "int sp_impact(int,int,int);" );
	AddFunction(Lib_sp_crash,            "int sp_crash(int,int);" );
	AddFunction(Lib_sp_draw,             "int sp_draw(int,int);" );
				
	AddFunction(Lib_sp_run,              "void sp_run(int);" );
	AddFunction(Lib_sp_free,             "int sp_free(int);" );
	AddFunction(Lib_world_create,         "int world_create();" );
	AddFunction(Lib_world_addSprite,         "int world_addSprite(int,int);" );
	AddFunction(Lib_world_removeSprite,      "int world_removeSprite(int,int);");
	AddFunction(Lib_world_setCamera,         "int world_setCamera(int,int);" );
				
	AddFunction(Lib_world_draw,             "int world_draw(int);" );
	AddFunction(Lib_world_run,             "int world_run(int);" );
	AddFunction(Lib_world_rank,             "int world_rank(int,int);");
	AddFunction(Lib_world_free,         "int world_free(int);" );

 }
 
 
 
