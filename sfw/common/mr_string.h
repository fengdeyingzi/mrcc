#ifndef _STRING_H
#define _STRING_H

#include "types.h"


/* ת��unicode�Ľṹ
   ʹ�ú��� mrc_freeOrigin �ͷ��ڴ�
 */
typedef struct {
	PWSTR pText;    //unicode�ַ���ָ��
	int32 len;      //�ַ������峤��
}UnicodeSt;


VOID CharToUnicode(char* in, PWSTR* out, int32* outlen);

PSTR UnicodeToChar(PCWSTR unicode);

#if 0
/**
 * \ת��ΪСд���ַ�����
 *
 * \����str    ת�����ַ���
 * \����Сд�ַ���
 */
PSTR tolower(PSTR str);

/**
 * \ת��Ϊ��д���ַ�����
 *
 * \����str    ת�����ַ���
 * \���ش�д�ַ���
 */
PSTR toupper(PSTR str);
#endif

/**
 * \brief Compare two string with case ignore.
 *
 * \param dst ��һ���ַ�������
 * \param src �ڶ����ַ�������
 * \����
 *	<0 �� dst < src
 *	=0 �� dst = src
 *	>0 �� dst > src
 *
 * \�Ƚ�����case�����ַ�����
 */
Sint32 stricmp(PCSTR dst, PCSTR src);

/**
 * \brief Trim left space chars here just ' '.
 *
 * \param str the string to be trimed
 * \return the trimed string
 *
 * \�����ַ�ֻ�����������¿ռ�'��
 *
 * \����str���ַ�����trimed
 * \����trimed�ַ���
 */
PSTR trimleft(PSTR str);

/**
 * \brief Trim right space chars here just .
 *
 * \param str the string to be trimed
 * \return the trimed string
 *
 * \������ȷ�Ŀռ��ַ�����ֻ��' '��
 *
 * \����str���ַ�����trimed
 * \����trimed�ַ���
 */
PSTR trimright(PSTR str);


/**
 * \brief Trim left&right space chars.
 *
 * \param str the string to be trimed
 * \return the trimed string
 *
 * \�������ҿռ��ַ���
 *
 * \����str���ַ�����trimed
 * \����trimed�ַ���
 */
PSTR trim(PSTR str);

/**
 * \brief Split the string with specific char.
 * 
 * \param str the string to be splited
 * \param sep the seperator char
 * \param[out] values the splited string array
 * \param size the max size of values
 * \return real size of values array returned
 *
 * \�Ĳ�����ض��ַ����ַ�����
 *
 * \����str���ַ�����splited
 * \�����ķָ����ַ�����
 * \����[��]�ַ�������ֵ��splited
 * \����ֵ�Ĵ�С�����ߴ�
 * \���ط���ֵ�����ʵ�ʴ�С
 */
Sint32 split(PSTR str, char sep, PSTR values[], Sint32 size);

/**
 * \�õ�wstring�ĳ��ȡ�
 *
 * \�����ֽڵ�wstring�ĳ���(�ֽ�)

Sint32 wstrlen(PCWSTR str);
 */
/**
 * \brief Copy characters of one wstring to another.
 *
 * \param dst Destination string
 * \param src Source string
 * \return the destination string
 *
 * \һwstring���ַ����Ƶ���һ����
 *
 * \����dst��Ŀ���ַ���
 * \ src�����ַ�������
 * \����Ŀ���ַ���
 */

PWSTR wstrcpy(PWSTR dst, PCWSTR src);

PWSTR wstrncat(PWSTR dst, PCWSTR src, Sint32 size);

/**
 * \һwstring���ַ����Ƶ���һ����
 *
 * \����dst     Ŀ���ַ���
 * \����src     �����ַ���
 * \����        Ҫ���Ƶ��ֽڴ�С
 * \����Ŀ���ַ���
 */
PWSTR wstrncpy(PWSTR dst, PCWSTR src, Sint32 size);

/**
 * \�Ƚ��ַ�����
 *
 * \���� str1 the ��һ���ַ���
 * \���� str2 the �ڶ����ַ���
 * \����
 *	 0 �� str1 == str2
 *	<0 �� str1 < str2
 *	>0 �� str1 > str2
 */
Sint32 wstrcmp(PCWSTR str1, PCWSTR str2);

/**
 * \brief Find a wchar in wstring.
 * 
 * \param str the wstring
 * \param chr1 the first byte of the wchar
 * \param chr2 the second byte of the wchar
 * \return the first occurrence of c in string, NULL when not found
 *
 * \����wstring�е�һ��wchar��
 *
 * \����str     wstring
 * \����chr1    wchar�ĵ�һ�ֽ�
 * \����chr2    wchar�ĵڶ��ֽ�
 * \����c��һ�γ������ַ�����NULLʱδ�ҵ�
 */
PCWSTR wstrchr(PCWSTR str, UCHAR chr1, UCHAR chr2);

/**
 * \brief Trim left a wstring.
 *
 * \param str the wstring to be trimed
 * \return the trimed string
 *
 * \����������wstring�ġ�
 *
 * \����str�е�wstring����trimed
 * \����trimed�ַ���
 */
PWSTR wtrimleft(PWSTR str);

/**
 * \brief Trim right a wstring.
 * 
 * \param str the wstring to be trimed
 * \return the trimed string
 *
 * \����һ��wstring��Ȩ����
 *
 * \����str�е�wstring����trimed
 * \����trimed�ַ���
 */
PWSTR wtrimright(PWSTR str);

/**
 * \brief Trim a wstring.
 * 
 * \param str the wstring to be trimed
 * \return the trimed string
 *
 * \�޼�wstring�ġ�
 *
 * \����str�е�wstring����trimed
 * \����trimed�ַ���
 */
PWSTR wtrim(PWSTR str);


/**
 * \utf8�ַ���ת��ΪUnicode�ַ�����
 *
 * \����UTF8               Ҫת����UTF8�ַ���
 * \����[��,��]Unicode     ת��Unicode�Ļ�����
 * \����[��,��]size        Unicode�������Ĵ�С
 * \����ת����ĳ���(�ֽ�)
 */
Sint32 str2wstr(PCSTR utf8, PWSTR unicode, Sint32 size);


/*
 * \Unicode�ַ���ת����utf8���ַ�����
 *
 * \����Unicode Ҫת����Unicode�ַ���
 * \����UTF8    ת��utf8�Ļ�����
 * \����size    utf8������������С
 * \����ת����ĳ���(�ֽ�)
 */
Sint32 wstr2str(PCWSTR unicode, PSTR utf8, Sint32 size);

char *strDup(char *pcStr);
PWSTR wstrcat(PWSTR dst, PCWSTR src);
char *strChrEx(const char *src,int c);
PWSTR trimCRLF(PWSTR str);
char *itoa(int num,char *str,int radix);
PWSTR wstrdup(PCWSTR str);

#endif
