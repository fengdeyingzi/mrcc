#include <mpc.h>
#include "xl_coding.h"


//ex_coding����ʵ�� ���ܱ���ת������
char* xl_ex_coding(char* text,int len,char* coding,char* tocoding){
	char *temp_un = NULL;
	int32 len_un = 0;
	char *retext = NULL;
	int32 relen = len;
	//�ж��ı��Ƿ�Ϊun���� ������� ��ת����un���루��ˣ�
	if(strcmp(coding,"UTF16-BE") == 0 || strcmp(coding,"utf16-be") == 0 || strcmp(coding,"UNICODE") == 0|| strcmp(coding,"unicode") == 0){
		temp_un = text;
		len_un = len;
		relen = len*2;
	}
	else{
		if(strcmp(coding, "GBK")==0 || strcmp(coding,"gbk")==0 || strcmp(coding,"GB2312")==0 || strcmp(coding,"gb2312")==0){
			temp_un = gbToUn(text);
			len_un = wstrlen(temp_un);
			relen = len*2;
		}
		else if(strcmp(coding,"UTF-8")==0 || strcmp(coding,"utf-8")==0){
			len_un = len*2;
			temp_un = malloc(len_un);
			relen = len*2;
			UTF8ToUni(text, temp_un, len_un);
		}
		else if(strcmp(coding, "ANSI")==0 || strcmp(coding, "ansi")==0){
			relen = len*3;
			temp_un = gbToUn(text);
			len_un = wstrlen(temp_un);
		}
		else{
			return NULL;
		}
	}
	if(strcmp(tocoding, "unicode")==0 || strcmp(tocoding,"UNICODE")==0 || strcmp(tocoding,"UTF-16BE")==0 || strcmp(tocoding,"utf-16be")==0){
	return temp_un;
	}
    else if(strcmp(tocoding,"UTF-8")==0 || strcmp(tocoding,"utf-8")==0){
		retext = malloc(relen);
		UniToUTF8(temp_un, retext, relen);
		return retext;
	}
	else if(strcmp(tocoding,"gbk")==0 || strcmp(tocoding,"GBK")==0 || strcmp(tocoding,"gb2312")==0 || strcmp(tocoding,"GB2312")==0){
		return unToGb(temp_un);
	}
	
	return NULL;
}

//gb����תunicode ���ص��ַ�����Ҫ�ͷ��ڴ�
char *gbToUn(char *text)
{
 int len;
 return (char*)c2u(text, NULL, &len);
 
}

//unicode����תgb ���ص��ַ�����Ҫ�ͷ��ڴ�
char *unToGb(char *text)
{
 char *input= text;
  int output_len;
int input_len= wstrlen(input);
 char *output= malloc(input_len+2);
 printf("input_len %d\n",input_len);

 u2c( input, input_len, &output, &output_len);
 return output;
}


//�ж�utf���룬0Ϊ�ɹ���-1ʧ��
int IsUTF8( void* pBuffer, long size)
{
int IsUTF8 = 0;
unsigned char* start = (unsigned char*)pBuffer;
unsigned char* end = (unsigned char*)pBuffer + size;
while (start < end)
{
if (*start < 0x80) // (10000000): ֵС��0x80��ΪASCII�ַ�
{
start++;
}
else if (*start < (0xC0)) // (11000000): ֵ����0x80��0xC0֮���Ϊ��ЧUTF-8�ַ�
{
IsUTF8 = -1;
break;
}
else if (*start < (0xE0)) // (11100000): �˷�Χ��Ϊ2�ֽ�UTF-8�ַ�
{
if (start >= end - 1)
break;
if ((start[1] & (0xC0)) != 0x80)
{
IsUTF8 = -1;
break;
}
start += 2;
}
else if (*start < (0xF0)) // (11110000): �˷�Χ��Ϊ3�ֽ�UTF-8�ַ�
{
if (start >= end - 2)
break;
if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
{
IsUTF8 = -1;
break;
}
start += 3;
}
else
{
IsUTF8 = -1;
break;
}
}
return IsUTF8;
}




//����unicode�����ַ��������ص��ַ�����Ҫ�ֶ�free
char *un_copy(char *text)
{
 int len= wstrlen(text)+2;
 char *temp= malloc(len);
 memcpy(temp,text,len);
 return temp;
}

//un��������ת��Ϊint
int un_atoi(char *text)
{
 char *temp=unToGb(text);
 int num=atoi(temp);
 free(temp);
 return num;
}


// unicode�ַ����Ƚ�
/*
int wstrcmp(char *str1, char *str2)
{
    while ((str1[0] || str1[1]) && str1[0] == str2[0] && str1[1] == str2[1])
    {
        str1 += 2; 
        str2 += 2;
    }

    return str1[0] == str2[0] ? str1[1] - str2[1] : str1[0] - str2[0];
}
*/

// unicode�ַ�������
/*
char *wstrcpy(char *dst, char *src)
{
    int i = 0;

    while (src[i] || src[i + 1]) 
    {
        dst[i] = src[i];
        dst[i+1] = src[i + 1];
        i += 2;
    }

    dst[i] = dst[i + 1] = '\0';

    return dst;
}
*/

// unicode�ַ�������ָ������
/*
char *wstrncpy(char *dst, char *src, int32 size)
{
    int i = 0;

    size -= 2;

    while (src[i] || src[i + 1]) 
    {
        if (i >= size) break;

        dst[i] = src[i];
        dst[i + 1] = src[i + 1];
        i += 2;
    }

    dst[i] = dst[i + 1] = '\0';

    return dst;
}
*/

// unicode�ַ�������
/*
char *wstrcat(char *dst, char *src)
{
    int len = wstrlen(dst);
    return wstrcpy(dst + len, src);
}
*/
/*
// unicode�ַ�������
char *wstrdup( char *str)
{
    int len = 0;
    char *pDest = NULL;

    if (NULL == str)
        return NULL;

    len = wstrlen(str) + 2;
    pDest = (char*)malloc(len);
    if(NULL != pDest)
        memcpy(pDest, str, len);

    return pDest;
}
*/
/*---------------------------------------------------------------------------*/

//UTF8ת��ΪUnicode
//������UTF8�ַ�����Unicode����������������С
//���أ�������ʹ�ô�С
int UTF8ToUni( char *utf8str, char *unistr, int size)
{
    int32 i = 0, u = 0;
    uint8 *utf8, *unicode;

    utf8 = (unsigned char*)utf8str;
    unicode = (unsigned char*)unistr;

    while (utf8[i] && u < size - 2)
    {
        if((utf8[i] & 0x80) == 0)
        {
            // one byte 0...
            unicode[u] = 0;
            unicode[u + 1] = utf8[i++];
        }else if((utf8[i] & 0x20) == 0){
            // two bytes 110... 10...
            unicode[u] = (unsigned char)((utf8[i] & 0x1f) >> 2);
            unicode[u + 1] = (unsigned char)((utf8[i] << 6) & 0xff) | (utf8[i + 1] & 0x3f);
            i += 2;
        }else{
            // three bytes 1110... 10... 10...
            unicode[u] = (unsigned char)((utf8[i] << 4) & 0xff) | ((utf8[i + 1] & 0x3f) >> 2);
            unicode[u + 1] = (unsigned char)((utf8[i + 1] << 6) & 0xff) | (utf8[i + 2] & 0x3f);
            i += 3;
        }

        u += 2;
    }

    unicode[u] = '\0';
    unicode[u + 1] = '\0';

    return u;
}

//Unicodeת��ΪUTF8
//������Unicode�ַ�����UTF8����������������С
//���أ�������ʹ�ô�С
int UniToUTF8(char *unistr, char *utf8str, int size)
{
    int u = 0, i = 0;
    unsigned char *unicode, *utf8;

    unicode = (unsigned char*)unistr;
    utf8 = (unsigned char*)utf8str;

    while ((*(unicode+u) || *(unicode+u+1)) && i < size - 1)
    {
        if (*(unicode+u) == 0 && *(unicode+u + 1) < 128) {
            // 0 - 7 bits
            utf8[i++] = *(unicode+u + 1);
        } else if((*(unicode+u) & 0xf8) == 0) {
            // 8 - 11 bits
            utf8[i++] = 0xc0 | ((unicode[u] << 2) & 0xff) | (unicode[u + 1] >> 6);
            utf8[i++] = 0x80 | (unicode[u + 1] & 0x3f);
        } else {
            // 12 - 16 bits
            utf8[i++] = 0xe0 | (unicode[u] >> 4);
            utf8[i++] = 0x80 | ((unicode[u] << 2) & 0x3f) | (unicode[u + 1] >> 6);
            utf8[i++] = 0x80 | (unicode[u + 1] & 0x3f);
        }

        u += 2;
    }

    utf8[i] = '\0';

    return i;
}

// ת��ascii�ַ���Ϊunicode�ַ���
int Asc2Uni(char *input, char *output, int32 outlen)
{
    int i;

    if (NULL == input || NULL == output)
        return -1;

    for (i = 0; input[i] != '\0' && outlen >= 4; i++)
    {
        output[i * 2] = '\0';
        output[i * 2 + 1] = input[i];
        outlen -= 2;
    }

    output[i * 2] = '\0';
    output[i * 2 + 1] = '\0';

    return (i * 2);
}

// ת��unicode�ַ���Ϊascii�ַ���
int Uni2Asc(char *input, char *output,int outlen)
{
    int32 i;

    if (NULL == input || NULL == output)
        return -1;

    for (i = 0; input[i * 2 + 1] != '\0' && outlen >= 2; i++)
    {
        output[i] = input[i * 2 + 1];
        outlen--;
    }

    output[i] = '\0';

    return (i);
}


//��utf8����ת��Ϊgb����Ҫfree
char *utfToGb(char *text)
{
	char *gb_text;
 int len=strlen(text)*2+2;
 char *un_text=malloc(len);
 UTF8ToUni(text,un_text,len);
 gb_text=unToGb(un_text);
 free(un_text);
 return gb_text;
}


//��gbתutf����Ҫfree
char *gbToUtf(char *text)
{
 int len;
 char *un_text;
 char *utf_text;
 len=strlen(text)*2+2;
 utf_text=malloc(len);
 un_text=gbToUn(text);
 UniToUTF8(un_text,utf_text,len);
 free(un_text);
 return utf_text;
}
