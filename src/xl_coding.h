
#ifndef _CODING_H_
#define _CODING_H_

#include <mrc_base.h>

char* xl_ex_coding(char* text,int len,char* coding,char* tocoding);
char *gbToUn(char *text);
char *unToGb(char *text);
int IsUTF8( void* pBuffer, long size);
char *un_copy(char *text);
int un_atoi(char *text);
//int wstrcmp(char *str1, char *str2);
//char *wstrcpy(char *dst, char *src);
//char *wstrncpy(char *dst, char *src, int32 size);
//char *wstrcat(char *dst, char *src);
int UTF8ToUni( char *utf8str, char *unistr, int size);
int UniToUTF8(char *unistr, char *utf8str, int size);
int Asc2Uni(char *input, char *output, int32 outlen);
int Uni2Asc(char *input, char *output,int outlen);
char *utfToGb(char *text);
char *gbToUtf(char *text);
int32 isGBK(const char *buf, int size);
int32 isGB2312(const char *buf, int size);


#endif