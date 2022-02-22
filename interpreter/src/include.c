#include "picoc.h"
#include "interpreter.h"
#include "m_android.h"
#include "m_graphics.h"
#include "m_ex_game.h"
#include "m_ex_math.h"
#include "m_exb.h"
#include "m_net.h"


/* ���ǿ��԰���һ�����б� */
struct IncludeLibrary
{
    char *IncludeName;
    void (*SetupFunction)(void);
    struct LibraryFunction *FuncList;
    const char *SetupCSource;
    struct IncludeLibrary *NextLib;
};

struct IncludeLibrary *IncludeLibList = NULL;


/* ��ʼ�����õİ����� */
void IncludeInit(void)
{
/* ԭ��
#ifndef BUILTIN_MINI_STDLIB
    IncludeRegister("ctype.h", NULL, &StdCtypeFunctions[0], NULL);
    IncludeRegister("errno.h", &StdErrnoSetupFunc, NULL, NULL);
#ifndef NO_FP
    IncludeRegister("math.h", &MathSetupFunc, &MathFunctions[0], NULL);
#endif
    IncludeRegister("stdbool.h", &StdboolSetupFunc, NULL, StdboolDefs);
    IncludeRegister("stdio.h", &StdioSetupFunc, &StdioFunctions[0], StdioDefs);
    IncludeRegister("stdlib.h", &StdlibSetupFunc, &StdlibFunctions[0], NULL);
    IncludeRegister("string.h", &StringSetupFunc, &StringFunctions[0], NULL);
    IncludeRegister("time.h", &StdTimeSetupFunc, &StdTimeFunctions[0], StdTimeDefs);
    IncludeRegister("unistd.h", &UnistdSetupFunc, &UnistdFunctions[0], UnistdDefs);
#endif
*/
    //IncludeRegister("ctype.h", &Ctype_SetupFunc, &Ctype_Functions[0], NULL);
    IncludeRegister("sound.h", &Sound_SetupFunc, &Sound_Functions[0], NULL);
    IncludeRegister("base.h", &mrc_base_SetupFunc, &mrc_base_Functions[0], mrc_base_Defs);
    IncludeRegister("base_i.h", &base_i_init, &base_i_Functions[0], mrc_base_i_Defs);
	IncludeRegister("android.h", &androidSetupFunc, &androidFunctions[0], android_Defs);
	IncludeRegister("graphics.h", &bitmapSetupFunc, &bitmapFunctions[0], bitmap_Defs);
	IncludeRegister("ex_game.h", &Ex_GameSetupFunc, &Ex_GameFunctions[0], game_Defs);
	IncludeRegister("ex_math.h", &Ex_MathSetupFunc, &Ex_MathFunctions[0], NULL);
	IncludeRegister("exb.h", &exbSetupFunc, &exbFunctions[0], exb_Defs);
	IncludeRegister("net.h", &netSetupFunc, &netFunctions[0], net_Defs);
}

/* �������ϵͳͷ�ļ���ʹ�õĿռ� */
void IncludeCleanup(void)
{
    struct IncludeLibrary *ThisInclude = IncludeLibList;
    struct IncludeLibrary *NextInclude;
    
    while (ThisInclude != NULL)
    {
        NextInclude = ThisInclude->NextLib;
        HeapFreeMem(ThisInclude);
        ThisInclude = NextInclude;
    }

    IncludeLibList = NULL;
}

/* ע��һ���µ����ð����ļ� */
void IncludeRegister(const char *IncludeName, void (*SetupFunction)(void), struct LibraryFunction *FuncList, const char *SetupCSource)
{
    struct IncludeLibrary *NewLib = HeapAllocMem(sizeof(struct IncludeLibrary));
    NewLib->IncludeName = TableStrRegister(IncludeName);
    NewLib->SetupFunction = SetupFunction;
    NewLib->FuncList = FuncList;
    NewLib->SetupCSource = SetupCSource;
    NewLib->NextLib = IncludeLibList;
    IncludeLibList = NewLib;
}

/* �������е�ϵͳͷ�ļ� */
void PicocIncludeAllSystemHeaders(void)
{
    struct IncludeLibrary *ThisInclude = IncludeLibList;
    
    for (; ThisInclude != NULL; ThisInclude = ThisInclude->NextLib)
        IncludeFile(ThisInclude->IncludeName);
}

/* ����һЩԤ����Ŀ⣬����ʵ�ʵ��ļ� */
void IncludeFile(char *FileName)
{
    struct IncludeLibrary *LInclude;
    
    /* ɨ��������ļ����������Ƿ������ǵ�Ԥ����İ����б��� */
    for (LInclude = IncludeLibList; LInclude != NULL; LInclude = LInclude->NextLib)
    {
        if (strcmp(LInclude->IncludeName, FileName) == 0)
        {
            /* ���� - ��ֹ�ظ����� */
            if (!VariableDefined(FileName))
            {
                VariableDefine(NULL, FileName, NULL, &VoidType, FALSE);
                
                /* ���ж�������������������һ�� */
                if (LInclude->SetupFunction != NULL)
                    (*LInclude->SetupFunction)();
                
                /* �������õ�CԴ���� - ���Զ������͵�. */
                if (LInclude->SetupCSource != NULL)
                    PicocParse(FileName, LInclude->SetupCSource, strlen(LInclude->SetupCSource), TRUE, TRUE, FALSE);
                
                /* ���ú����� */
                if (LInclude->FuncList != NULL)
                    LibraryAdd(&GlobalTable, FileName, LInclude->FuncList);
            }
            
            return;
        }
    }
    
    /* ����Ԥ������ļ�����һ���������ļ� */
    PicocPlatformScanFile(FileName);
}

