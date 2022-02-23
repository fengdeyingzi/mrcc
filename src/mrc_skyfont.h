#ifndef _MRC_SKYFONT_H_
#define _MRC_SKYFONT_H_

//�ּ��
#define SKYFONT_WORD_SPACE (0)
//�м��
#define SKYFONT_LINE_SPACE (1)

//С�����, ASCII����ַ�������ΪС����
#define SKYFONT_SMALL_WIDTH (8)
//�������, ��ASCII����ַ�������Ϊ������
#define SKYFONT_LARGE_WIDTH (12)
//�����
#define SKYFONT_HEIGHT (12)

//�Ƿ�֧��\r��\n���з�
#define SKYFONT_SUPPORT_CRLF 1
//�Ƿ�֧�ֳ������ӿ�ʱ�Զ�����
#define SKYFONT_SUPPORT_AUTO_NEWLINE 2
//�Ƿ�֧����ʾ����ַ�
#define SKYFONT_SUPPORT_HALF_CHAR 4
//��������ѡ�����ʹ���������,���ʹ�û������ | ������

//���㷵��ֵ�е�����
#define MRC_SKYFONT_GET_LINE(i) (((unsigned int)((i)&0xFFF00000))>>20)
//���㷵��ֵ�е�offֵ
#define MRC_SKYFONT_GET_OFF(i) ((unsigned int)((i)&0x000FFFFF))

typedef struct _skyfont_screenRect_t {
	int16 x;
	int16 y;
	int16 w;
	int16 h;
} skyfont_screenRect_t;

/*
 * �������һ��ַ���,ֻ֧��Unicode����
 * 
 * ����:
 * szText:    ������Unicode������ַ���
 * off:       ��Ч�ַ���ƫ��,����>=0,��һ��Unicodeռ�õ��ֽ�Ϊ��λ
 * len:       ��Ч�ַ�������,������<0,���Զ����㳤��(������'\0'����־),��һ��Unicodeռ�õ��ֽ�Ϊ��λ
 * x,y:       ��ʾ�ı������Ͻ�x,y����
 * rect:      �����������(λ�ڿ���������Ĳ��ֽ�������ʾ)
 * colorst:   ���廭����ɫ
 * flag:      ����ȡ����ֵ:(�����û������'|'����ʾ����ѡ��)
 *						   0; //Ĭ��,��֧�ֻ��з�(�����ַ�),��֧���Զ�����,��֧�ְ���ַ�
 *						   SKYFONT_SUPPORT_CRLF; //֧�ֻ��з�
 *                         SKYFONT_SUPPORT_AUTO_NEWLINE; //֧���Զ�����(ָ�������������Ȼ���)
 *						   SKYFONT_SUPPORT_HALF_CHAR; //֧�ְ���ַ�
 *						   *** ע��: ʹ�û��з����Զ�����ʱ, rect����Ϊ�Ű�����ʹ�� ***
 *
 * ����:
 * a) һ��32λ��intֵ:
 *					  MRC_SKYFONT_GET_LINE(i) - ռ������(δ�����Ե��ַ�����������,��������һ��)
 *					  MRC_SKYFONT_GET_OFF(i) - ��һ�������Ե��ַ���offֵ,��off==len,��˵��ȫ���ַ�������������
 *											   �����Ե��ַ���ָ: ���ַ���ʼ��֮��������ַ�,���������ڿ���������.
 * b) -1 ʧ��
 */
extern int32 mrc_skyfont_drawTextLeft(char* szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, mr_colourSt colorst, uint16 flag);

/*
 * ��ȡ�ַ����Ŀ�͸�,ͬʱ��������
 *
 * ����:
 * szText:           ������Unicode������ַ���
 * off:              ��Ч�ַ���ƫ��,����>=0,��һ��Unicodeռ�õ��ֽ�Ϊ��λ
 * len:              ��Ч�ַ�������,������<0,���Զ����㳤��(������'\0'����־),��һ��Unicodeռ�õ��ֽ�Ϊ��λ
 * x,y:				 ��ʾ�ı������Ͻ�x,y����
 * rect:			 �����������(λ�ڿ���������Ĳ��ֽ�������ʾ)(��͸�Ϊ-1ʱ,���ʾ����)
 * flag:			 ����ȡ����ֵ:(�����û������'|'����ʾ����ѡ��)
 *								  0; //Ĭ��,��֧�ֻ��з�(�����ַ�),��֧���Զ�����,��֧�ְ���ַ�
 *								  SKYFONT_SUPPORT_CRLF; //֧�ֻ��з�
 *								  SKYFONT_SUPPORT_AUTO_NEWLINE; //֧���Զ�����(ָ�������������Ȼ���)
 *								  SKYFONT_SUPPORT_HALF_CHAR; //֧�ְ���ַ�
 *								  *** ע��: ʹ�û��з����Զ�����ʱ, rect����Ϊ�Ű�����ʹ�� ***
 *
 * ���:
 * width:			�ַ����Ŀ��(�Ե��м���)
 * height:			�ַ����ĸ߶�(δ�����Ե��ַ�����������)
 * *** ע��: ����ַ�����һ���ַ��������Ⱥ͸߶� ***
 *
 * ����:
 * a) һ��32λ��intֵ:
 *					  MRC_SKYFONT_GET_LINE(i) - ռ������(δ�����Ե��ַ�����������,��������һ��)
 *					  MRC_SKYFONT_GET_OFF(i) - ��һ�������Ե��ַ���offֵ,��off==len,��˵��ȫ���ַ�������������
 *											   �����Ե��ַ���ָ: ���ַ���ʼ��֮��������ַ�,���������ڿ���������.
 * b) -1 ʧ��
 */
extern int32 mrc_skyfont_textWidthHeight(char *szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, uint16 flag, int32 *width, int32 *height);

/*
 * mrc_skyfont_load �ص��ӿ�
 * result: �ֿ���صĽ��: MR_SUCCESS�ɹ� �� MR_FAILEDʧ��
 */
typedef void (*mrc_skyfont_load_cb_t)(int32 result);

/*
 * �����ֿ�
 * fontNum: ������ַ�����, 0�򲻻���
 * ����: MR_SUCCESS�ɹ�, MR_FAILEDʧ��
 */
extern int32 mrc_skyfont_load(int fontNum, mrc_skyfont_load_cb_t cb);

/*
 * ж���ֿ�,�ͷź��ֿ⽫ֹͣ����,���Ҫ���¹���,��ʹ�� mrc_skyfont_load �ٴμ���
 * ����: MR_SUCCESS�ɹ�, MR_FAILEDʧ��
 */
extern int32 mrc_skyfont_unload(void);

#endif