#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "platform.h"


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif

#define MEM_ALIGN(x) (((x) + sizeof(ALIGN_TYPE) - 1) & ~(sizeof(ALIGN_TYPE)-1))

#define GETS_BUF_MAX 256

/* ǿ�ƶ���������ֵ������ */
#ifndef NO_FP
#define IS_FP(v) ((v)->Typ->Base == TypeFP)
#define FP_VAL(v) ((v)->Val->FP)
#else
#define IS_FP(v) 0
#define FP_VAL(v) 0
#endif

#define isalpha(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
#define isdigit(c) ((c) >= '0' && (c) <= '9')
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n')

#define IS_POINTER_COERCIBLE(v, ap) ((ap) ? ((v)->Typ->Base == TypePointer) : 0)
#define POINTER_COERCE(v) ((int)(v)->Val->Pointer)

#define IS_INTEGER_NUMERIC_TYPE(t) ((t)->Base >= TypeInt && (t)->Base <= TypeUnsignedLong)
#define IS_INTEGER_NUMERIC(v) IS_INTEGER_NUMERIC_TYPE((v)->Typ)
#define IS_NUMERIC_COERCIBLE(v) (IS_INTEGER_NUMERIC(v) || IS_FP(v))
#define IS_NUMERIC_COERCIBLE_PLUS_POINTERS(v,ap) (IS_NUMERIC_COERCIBLE(v) || IS_POINTER_COERCIBLE(v,ap))

extern uint16 SCREEN_WIDTH;
extern uint16 SCREEN_HEIGHT;

struct Table;

/* �ʷ���� */
enum LexToken
{
    /* 0x00 */ TokenNone, 
    /* 0x01 */ TokenComma,
    /* 0x02 */ TokenAssign, TokenAddAssign, TokenSubtractAssign, TokenMultiplyAssign, TokenDivideAssign, TokenModulusAssign,
    /* 0x08 */ TokenShiftLeftAssign, TokenShiftRightAssign, TokenArithmeticAndAssign, TokenArithmeticOrAssign, TokenArithmeticExorAssign,
    /* 0x0d */ TokenQuestionMark, TokenColon, 
    /* 0x0f */ TokenLogicalOr, 
    /* 0x10 */ TokenLogicalAnd, 
    /* 0x11 */ TokenArithmeticOr, 
    /* 0x12 */ TokenArithmeticExor, 
    /* 0x13 */ TokenAmpersand, 
    /* 0x14 */ TokenEqual, TokenNotEqual, 
    /* 0x16 */ TokenLessThan, TokenGreaterThan, TokenLessEqual, TokenGreaterEqual,
    /* 0x1a */ TokenShiftLeft, TokenShiftRight, 
    /* 0x1c */ TokenPlus, TokenMinus, 
    /* 0x1e */ TokenAsterisk, TokenSlash, TokenModulus,
    /* 0x21 */ TokenIncrement, TokenDecrement, TokenUnaryNot, TokenUnaryExor, TokenSizeof, TokenCast,
    /* 0x27 */ TokenLeftSquareBracket, TokenRightSquareBracket, TokenDot, TokenArrow, 
    /* 0x2b */ TokenOpenBracket, TokenCloseBracket,
    /* 0x2d */ TokenIdentifier, TokenIntegerConstant, TokenFPConstant, TokenStringConstant, TokenCharacterConstant,
    /* 0x32 */ TokenSemicolon, TokenEllipsis,
    /* 0x34 */ TokenLeftBrace, TokenRightBrace,
    /* 0x36 */ TokenIntType, TokenCharType, TokenFloatType, TokenDoubleType, TokenVoidType, TokenEnumType,
    /* 0x3c */ TokenLongType, TokenSignedType, TokenShortType, TokenStaticType, TokenAutoType, TokenRegisterType, TokenExternType, TokenStructType, TokenUnionType, TokenUnsignedType, TokenTypedef,
    /* 0x46 */ TokenContinue, TokenDo, TokenElse, TokenFor, TokenGoto, TokenIf, TokenWhile, TokenBreak, TokenSwitch, TokenCase, TokenDefault, TokenReturn,
    /* 0x52 */ TokenHashDefine, TokenHashInclude, TokenHashIf, TokenHashIfdef, TokenHashIfndef, TokenHashElse, TokenHashEndif,
    /* 0x59 */ TokenNew, TokenDelete,
    /* 0x5b */ TokenOpenMacroBracket,
    /* 0x5c */ TokenEOF, TokenEndOfLine, TokenEndOfFunction
};

/* ���ڶ�̬�ڴ���� */
struct AllocNode
{
    unsigned int Size;
    struct AllocNode *NextFree;
};

/* �Ƿ��������л��������� */
enum RunMode
{
    RunModeRun,                 /* ���������������еĴ��� */
    RunModeSkip,                /* �������룬û������ */
    RunModeReturn,              /* �Ӻ������� */
    RunModeCaseSearch,          /* Ѱ��һ��case��ǩ */
    RunModeBreak,               /* ���� switch/while/do */
    RunModeContinue,            /* �ظ�ѭ�� */
    RunModeGoto                 /* Ѱ��һ��goto��ǩ */
};

/* ��������״̬ - ������һϸ�ڣ��������ǾͿ���Ƕ�׽����ļ� */
struct ParseState
{
    const unsigned char *Pos;
    const char *FileName;
    short int Line;
    short int CharacterPos;
    enum RunMode Mode;          /* �Ƿ����������д��� */
    int SearchLabel;            /* ��������Ѱ��ʲô����±�ǩ */
    const char *SearchGotoLabel;/* ��������Ѱ��ʲôGOTO��ǩ */
    short int HashIfLevel;
    short int HashIfEvaluateToLevel;
    const char *SourceText;
};

/* ���� */
enum BaseType
{
    TypeVoid,                   /* void */
    TypeInt,                    /* integer */
    TypeShort,                  /* short integer */
    TypeChar,                   /* char (unsigned) */
    TypeLong,                   /* long integer */
    TypeUnsignedInt,            /* unsigned integer */
    TypeUnsignedShort,          /* unsigned short integer */
    TypeUnsignedLong,           /* unsigned long integer */
#ifndef NO_FP
    TypeFP,                     /* ����ָ�� */
#endif
    TypeFunction,               /* ���� */
    TypeMacro,                  /* �� */
    TypePointer,                /* ָ�� */
    TypeArray,                  /* �������� */
    TypeStruct,                 /* �ṹ */
    TypeUnion,                  /* �������� */
    TypeEnum,                   /* ö������ */
    TypeGotoLabel,              /* goto���ı�ǩ */
    Type_Type                   /* �洢���͵����� */
};

/* �������� */
struct ValueType
{
    enum BaseType Base;             /* ����ʲô�������� */
    int ArraySize;                  /* �������͵Ĵ�С */
    int Sizeof;                     /* �洢Ҫ�� */
    int AlignBytes;                 /* �������͵Ķ���߽� */
    const char *Identifier;         /* �ṹ�����ϵ����� */
    struct ValueType *FromType;     /* ��ʼ���� (�� NULL) */
    struct ValueType *DerivedTypeList;  /* ����ʼ�����б�ĵ�һ�� */
    struct ValueType *Next;         /* ����ʼ�����б����һ�� */
    struct Table *Members;          /* �ṹ�����ϵĳ�Ա */
    int OnHeap;                     /* true������ڶ��Ϸ��� */
    int StaticQualifier;            /* true���������һ����̬���� */
};

/* �������Ͷ���*/
struct FuncDef
{
    struct ValueType *ReturnType;   /* ����ֵ���� */
    int NumParams;                  /* ���������� */
    int VarArgs;                    /* ��ȷָ��һ���ɱ���Ŀ�Ĳ��� */
    struct ValueType **ParamType;   /* �������͵����� */
    char **ParamName;               /* �������Ƶ����� */
    void (*Intrinsic)();            /* �ڲ����õ�ַ��NULL */
    struct ParseState Body;         /* �ʷ���ǵĺ����壬���û�в����� */
};

/* �����Ͷ��� */
struct MacroDef
{
    int NumParams;                  /* ���������� */
    char **ParamName;               /* �������Ƶ����� */
    struct ParseState Body;         /* �ʷ���ǵĺ����壬���û�в����� */
};

/* values */
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
    char ArrayMem[2];               /* ���ݿ�ʼ��ռλ��������ָ�� */
    struct ValueType *Typ;
    struct FuncDef FuncDef;
    struct MacroDef MacroDef;
#ifndef NO_FP
    double FP;
#endif
    void *Pointer;                  /* unsafe native pointers */
};

struct Value
{
    struct ValueType *Typ;          /* ������������� */
    union AnyValue *Val;            /* ����ʵ�����ݵ�AnyValueָ�� */
    struct Value *LValueFrom;       /* �����һ����ֵ������һ����ֵ�ı�������NULL�� */
    char ValOnHeap;                 /* the AnyValue is on the heap (but this Value is on the stack) */
    char ValOnStack;                /* the AnyValue is on the stack along with this Value */
    char IsLValue;                  /* �Ƿ���޸ĺͷ����ĳ���ط������ǿ�����Ч���޸��� */
};

/* hash table data structure */
struct TableEntry
{
    struct TableEntry *Next;        /* next item in this hash chain */
    const char *DeclFileName;       /* where the variable was declared */
    unsigned short DeclLine;
    unsigned short DeclColumn;

    union TableEntryPayload
    {
        struct ValueEntry
        {
            char *Key;              /* points to the shared string table */
            struct Value *Val;      /* the value we're storing */
        } v;                        /* used for tables of values */
        
        char Key[1];                /* dummy size - used for the shared string table */
    } p;
};
    
struct Table
{
    short Size;
    short OnHeap;
    struct TableEntry **HashTable;
};

/* stack frame for function calls */
struct StackFrame
{
    struct ParseState ReturnParser;         /* how we got here */
    const char *FuncName;                   /* the name of the function we're in */
    struct Value *ReturnValue;              /* copy the return value here */
    struct Value **Parameter;               /* array of parameter values */
    int NumParams;                          /* the number of parameters */
    struct Table LocalTable;                /* the local variables and parameters */
    struct TableEntry *LocalHashTable[LOCAL_TABLE_SIZE];
    struct StackFrame *PreviousStackFrame;  /* the next lower stack frame */
};

/* lexer state */
enum LexMode
{
    LexModeNormal,
    LexModeHashInclude,
    LexModeHashDefine,
    LexModeHashDefineSpace,
    LexModeHashDefineSpaceIdent
};

struct LexState
{
    const char *Pos;
    const char *End;
    const char *FileName;
    int Line;
    int CharacterPos;
    const char *SourceText;
    enum LexMode Mode;
    int EmitExtraNewlines;
};

typedef void (*PFunction)(struct ParseState *Parser, struct Value *, struct Value **, int);

/* �⺯������ */
struct LibraryFunction
{
	PFunction Func;
 //   void (*Func)(struct ParseState *Parser, struct Value *, struct Value **, int);
    char *Prototype;
};

/* ��������͵��ض�״̬��Ϣ */
union OutputStreamInfo
{
    struct StringOutputStream
    {
        struct ParseState *Parser;
        char *WritePos;
    } Str;
};
typedef void CharWriter(unsigned char, union OutputStreamInfo *);
/* ��ӡ����ַ���ʱʹ�� - printf() */
struct OutputStream
{
    CharWriter *PutchFunc;
    union OutputStreamInfo i;
};
/* ����һ�������п��ܵĽ�� */
enum ParseResult { ParseResultEOF, ParseResultError, ParseResultOk };

/* ȫ�ֱ��� */
extern void *HeapStackTop;
extern struct Table GlobalTable;
extern struct StackFrame *TopStackFrame;
extern struct ValueType UberType;
extern struct ValueType IntType;
extern struct ValueType CharType;
extern struct ValueType UnsignedShortType;

#ifndef NO_FP
extern struct ValueType FPType;
#endif
extern struct ValueType VoidType;
extern struct ValueType TypeType;
extern struct ValueType FunctionType;
extern struct ValueType MacroType;
extern struct ValueType GotoLabelType;
extern struct ValueType *CharPtrType;
extern struct ValueType *CharPtrPtrType;
extern struct ValueType *CharArrayType;
extern struct ValueType *VoidPtrType;
extern char *StrEmpty;
extern struct PointerValue NULLPointer;//
extern struct OutputStream *CStdOut;
int32 mr_platEx (int32 code, 
uint8* input, 
int32 input_len, 
uint8** output, 
int32* output_len, 
MR_PLAT_EX_CB* cb
);
 

/* table.c */
void TableInit(void);
char *TableStrRegister(const char *Str);
char *TableStrRegister2(const char *Str, int Len);
void TableInitTable(struct Table *Tbl, struct TableEntry **HashTable, int Size, int OnHeap);
int TableSet(struct Table *Tbl, char *Key, struct Value *Val, const char *DeclFileName, int DeclLine, int DeclColumn);
int TableGet(struct Table *Tbl, const char *Key, struct Value **Val, const char **DeclFileName, int *DeclLine, int *DeclColumn);
struct Value *TableDelete(struct Table *Tbl, const char *Key);
char *TableSetIdentifier(struct Table *Tbl, const char *Ident, int IdentLen);
void TableStrFree(void);

/* lex.c */
void LexInit(void);
void LexCleanup(void);
void *LexAnalyse(const char *FileName, const char *Source, int SourceLen, int *TokenLen);
void LexInitParser(struct ParseState *Parser, const char *SourceText, void *TokenSource, const char *FileName, int RunIt);
enum LexToken LexGetToken(struct ParseState *Parser, struct Value **Value, int IncPos);
enum LexToken LexRawPeekToken(struct ParseState *Parser);
void LexToEndOfLine(struct ParseState *Parser);
void *LexCopyTokens(struct ParseState *StartParser, struct ParseState *EndParser);
void LexInteractiveClear(struct ParseState *Parser);
void LexInteractiveCompleted(struct ParseState *Parser);
void LexInteractiveStatementPrompt(void);

/* parse.c */
/* �����Ƕ����� picoc.h:
 * void PicocParse(const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource);
 */
enum ParseResult ParseStatement(struct ParseState *Parser, int CheckTrailingSemicolon);
struct Value *ParseFunctionDefinition(struct ParseState *Parser, struct ValueType *ReturnType, char *Identifier);
void ParseCleanup(void);
void ParserCopyPos(struct ParseState *To, struct ParseState *From);
void ParserCopy(struct ParseState *To, struct ParseState *From);

/* expression.c */
int ExpressionParse(struct ParseState *Parser, struct Value **Result);
long ExpressionParseInt(struct ParseState *Parser);
void ExpressionAssign(struct ParseState *Parser, struct Value *DestValue, struct Value *SourceValue, int Force, const char *FuncName, int ParamNo, int AllowPointerCoercion);
long ExpressionCoerceInteger(struct Value *Val);
unsigned long ExpressionCoerceUnsignedInteger(struct Value *Val);
#ifndef NO_FP
double ExpressionCoerceFP(struct Value *Val);
#endif

/* type.c */
void TypeInit(void);
void TypeCleanup(void);
int TypeSize(struct ValueType *Typ, int ArraySize, int Compact);
int TypeSizeValue(struct Value *Val, int Compact);
int TypeStackSizeValue(struct Value *Val);
int TypeLastAccessibleOffset(struct Value *Val);
int TypeParseFront(struct ParseState *Parser, struct ValueType **Typ, int *IsStatic);
void TypeParseIdentPart(struct ParseState *Parser, struct ValueType *BasicTyp, struct ValueType **Typ, char **Identifier);
void TypeParse(struct ParseState *Parser, struct ValueType **Typ, char **Identifier, int *IsStatic);
struct ValueType *TypeGetMatching(struct ParseState *Parser, struct ValueType *ParentType, enum BaseType Base, int ArraySize, const char *Identifier, int AllowDuplicates);
struct ValueType *TypeCreateOpaqueStruct(struct ParseState *Parser, const char *StructName, int Size);

/* heap.c */
void HeapInit(int StackSize);
void HeapCleanup(void);
void *HeapAllocStack(int Size);
int HeapPopStack(void *Addr, int Size);
void HeapUnpopStack(int Size);
void HeapPushStackFrame(void);
int HeapPopStackFrame(void);
void *HeapAllocMem(int Size);
void HeapFreeMem(void *Mem);

/* variable.c */
void VariableInit(void);
void VariableCleanup(void);
void VariableFree(struct Value *Val);
void VariableTableCleanup(struct Table *HashTable);
void *VariableAlloc(struct ParseState *Parser, int Size, int OnHeap);
void VariableStackPop(struct ParseState *Parser, struct Value *Var);
struct Value *VariableAllocValueAndData(struct ParseState *Parser, int DataSize, int IsLValue, struct Value *LValueFrom, int OnHeap);
struct Value *VariableAllocValueAndCopy(struct ParseState *Parser, struct Value *FromValue, int OnHeap);
struct Value *VariableAllocValueFromType(struct ParseState *Parser, struct ValueType *Typ, int IsLValue, struct Value *LValueFrom, int OnHeap);
struct Value *VariableAllocValueFromExistingData(struct ParseState *Parser, struct ValueType *Typ, union AnyValue *FromValue, int IsLValue, struct Value *LValueFrom);
struct Value *VariableAllocValueShared(struct ParseState *Parser, struct Value *FromValue);
struct Value *VariableDefine(struct ParseState *Parser, char *Ident, struct Value *InitValue, struct ValueType *Typ, int MakeWritable);
struct Value *VariableDefineButIgnoreIdentical(struct ParseState *Parser, char *Ident, struct ValueType *Typ, int IsStatic, int *FirstVisit);
int VariableDefined(const char *Ident);
void VariableGet(struct ParseState *Parser, const char *Ident, struct Value **LVal);
void VariableDefinePlatformVar(struct ParseState *Parser, char *Ident, struct ValueType *Typ, union AnyValue *FromValue, int IsWritable);
void VariableStackFrameAdd(struct ParseState *Parser, const char *FuncName, int NumParams);
void VariableStackFramePop(struct ParseState *Parser);
struct Value *VariableStringLiteralGet(char *Ident);
void VariableStringLiteralDefine(char *Ident, struct Value *Val);
void *VariableDereferencePointer(struct ParseState *Parser, struct Value *PointerValue, struct Value **DerefVal, int *DerefOffset, struct ValueType **DerefType, int *DerefIsLValue);

/* clibrary.c */
void BasicIOInit(void);
void LibraryInit(void);
void LibraryAdd(struct Table *GlobalTable, const char *LibraryName, struct LibraryFunction *FuncList);
void PrintCh(char OutCh, struct OutputStream *Stream);
void PrintSimpleInt(long Num, struct OutputStream *Stream);
void PrintInt(long Num, int FieldWidth, int ZeroPad, int LeftJustify, struct OutputStream *Stream);
void PrintStr(const char *Str, struct OutputStream *Stream);
void PrintFP(double Num, struct OutputStream *Stream);
void PrintType(struct ValueType *Typ, struct OutputStream *Stream);
void LibPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);
void LibSPrintf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

/* platform.c */
/* �����Ƕ����� picoc.h:
 * int PicocPlatformSetExitPoint();
 * void PicocInitialise(int StackSize);
 * void PicocCleanup();
 * void PicocPlatformScanFile(const char *FileName);
 * extern int FuncRet; */
void ProgramFail(struct ParseState *Parser, const char *Message, ...);
void AssignFail(struct ParseState *Parser, const char *Format, struct ValueType *Type1, struct ValueType *Type2, int Num1, int Num2, const char *FuncName, int ParamNo);
void LexFail(struct LexState *Lexer, const char *Message, ...);
void PlatformCleanup(void);
void PlatformInit(void);
int PlatformGetCharacter(void);
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *);
void PlatformErrorPrefix(struct ParseState *Parser);
void PlatformPrintf(const char *Format, ...);
void PlatformVPrintf(const char *Format, va_list Args);
void PlatformExit(int ExitVal);
char *PlatformMakeTempName(char *TempNameBuffer);
void fileFree(void);

/* include.c */
void IncludeInit(void);
void IncludeCleanup(void);
void IncludeRegister(const char *IncludeName, void (*SetupFunction)(void), struct LibraryFunction *FuncList, const char *SetupCSource);
void IncludeFile(char *Filename);
/* �����Ƕ����� picoc.h:
 * void PicocIncludeAllSystemHeaders(); */

/* m_ctype.c */
extern struct LibraryFunction Ctype_Functions[];
void Ctype_SetupFunc(void);

//m_base.c
extern const char mrc_base_Defs[];
extern struct LibraryFunction mrc_base_Functions[];
void mrc_base_SetupFunc(void);

//m_sound.c
extern struct LibraryFunction Sound_Functions[];
void Sound_SetupFunc(void);

//m_base_i.c
void base_i_init(void);
extern struct LibraryFunction base_i_Functions[];
extern const  char mrc_base_i_Defs[];

#endif /* INTERPRETER_H */
