


#include "../src/interpreter.h"
#include <mrc_base.h>
#include "mrc_android.h"
//#include "../../mpc_malloc.h"




static void Lib_readFileFromAssets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ReturnValue->Val->Pointer =mrc_readFileFromAssets(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}




const char android_Defs[] = "\
  enum{LENGTH_SHORT,LENGTH_LONG};\
	enum{VIEW_DOWN=20,VIEW_UP=21};\
	enum{VISIBLE=0,INVISIBLE=4,GONE=8};\
	enum{INPUT_MASK_STATE = 15,\
  INPUT_STATE_UNSPECIFIED = 0,\
  INPUT_STATE_UNCHANGED = 1,\
  INPUT_STATE_HIDDEN = 2,\
  INPUT_STATE_ALWAYS_HIDDEN = 3,\
  INPUT_STATE_VISIBLE = 4,\
  INPUT_STATE_ALWAYS_VISIBLE = 5,\
  INPUT_MASK_ADJUST = 240,\
  INPUT_ADJUST_UNSPECIFIED = 0,\
  INPUT_ADJUST_RESIZE = 16,\
  INPUT_ADJUST_PAN = 32,\
  INPUT_ADJUST_NOTHING = 48,\
  INPUT_IS_FORWARD_NAVIGATION = 256};\
";




struct LibraryFunction androidFunctions[10];

/* creates various system-dependent definitions */
void androidSetupFunc(void)
{
	androidFunctions[0].Func = Lib_readFileFromAssets;
	androidFunctions[0].Prototype = "void* readFileFromAssets(char*,int);";
	
	androidFunctions[1].Func = NULL;
	androidFunctions[1].Prototype = NULL;
 /*
    VariableDefinePlatformVar(NULL, "M_E", &FPType, (union AnyValue *)&M_EValue, FALSE);
    VariableDefinePlatformVar(NULL, "M_LOG2E", &FPType, (union AnyValue *)&M_LOG2EValue, FALSE);
	*/
}
