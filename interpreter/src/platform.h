/* �����ض�ƽ̨�İ����Ͷ��嶼������ļ��� */
#ifndef PLATFORM_H
#define PLATFORM_H

/*


*/
//�Ƿ�ʹ��������ģʽ ������true/�����false
//#define C_RUN 1


//#define MRPOID 1
 

#define INTERACTIVE_PROMPT_START "starting picoc " _VERSION "\n"
#define INTERACTIVE_PROMPT_STATEMENT "picoc> "
#define INTERACTIVE_PROMPT_LINE "     > "

#ifndef MRPOID 

#define ALIGN_TYPE void*                    // Ĭ�ϵ��������ͣ�����ʹ�� 
#define GLOBAL_TABLE_SIZE 150                // ȫ�ֱ����� 
#define STRING_TABLE_SIZE 150                // �����ַ�����Ĵ�С 
#define STRING_LITERAL_TABLE_SIZE 150        // �ַ������ֱ�Ĵ�С 
#define PARAMETER_MAX 16                    // ����������������� 
#define LINEBUFFER_MAX 256                  // �е�����ַ��� 
#define LOCAL_TABLE_SIZE 40                 // �ֲ�������Ĵ�С������չ�� 
#define STRUCT_TABLE_SIZE 40               // �ṹ/���ϳ�Ա��Ĵ�С������չ��

#define HEAP_SIZE (256*1024)               // �ѺͶ�ջ�ռ� XL���Ӱ���޸�

#else

#define ALIGN_TYPE void*                    // Ĭ�ϵ��������ͣ�����ʹ�� 
#define GLOBAL_TABLE_SIZE 97                // ȫ�ֱ����� 
#define STRING_TABLE_SIZE 97                // �����ַ�����Ĵ�С 
#define STRING_LITERAL_TABLE_SIZE 97        // �ַ������ֱ�Ĵ�С 
#define PARAMETER_MAX 16                    // ����������������� 
#define LINEBUFFER_MAX 256                  // �е�����ַ��� 
#define LOCAL_TABLE_SIZE 11                 // �ֲ�������Ĵ�С������չ�� 
#define STRUCT_TABLE_SIZE 11                // �ṹ/���ϳ�Ա��Ĵ�С������չ��

#define HEAP_SIZE (200*1024)               // �ѺͶ�ջ�ռ�

#endif
// #define USE_MALLOC_STACK
// #define USE_MALLOC_HEAP
#define NO_FP

#include <setjmp.h>
#include "mrc_base.h"
#include "mrc_base_i.h"

typedef char * va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (va_list)(&(v)) + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
#define assert(x)       //MRC_ASSERT(x)


#endif /* PLATFORM_H */
