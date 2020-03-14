#ifndef _MOMO_H_
#define _MOMO_H_

#include "mrc_base.h"
#include "mrc_bmp.h"
#include "mrc_exb.h"
#include "mrc_image.h"
#include "mrc_base_i.h"
#include "mrc_skyfont.h"

#define _SET_BIT(var,bit) \
    (var |= (bit))

#define _CLR_BIT(var,bit) \
    (var &= ~(bit))

#define _IS_SET_BIT(var,bit) \
    (var & (bit))


#define _FUNCSET_STYLE(state) \
	(func_state |= (state))

#define _FUNCCLR_STYLE(state) \
	(func_state &= ~(state))

#define _FUNCIS_SET_ANY(state) \
	(func_state & (state))

#define FUNC_INITSUC 1
#define FUNC_EXIT    2
#define FUNC_LOAD    4
#define FUNC_RELOADTXT 8 //���к����¼��ر༭������





#define FPRINTF(...) \
    do{\
    int32 h31415926len;\
    char msgBuffer[256];\
    int32 h31415926 = mrc_open("debug.txt", MR_FILE_CREATE|MR_FILE_WRONLY);\
    mrc_seek(h31415926, 0, MR_SEEK_END);\
    h31415926len = MR_SPRINTF(msgBuffer, __VA_ARGS__);\
    mrc_write(h31415926, msgBuffer, h31415926len);\
    mrc_write(h31415926, "\r\n", 2);\
    mrc_close(h31415926);\
    }while(0)

extern char STOREDIR[];//�洢Ŀ¼����/��
extern char enable_smallfont;//�Ƿ�����С����
extern char FONT_W;
extern char FONT_H;
extern uint16 SCREEN_WIDTH;
extern uint16 SCREEN_HEIGHT;
extern int32 func_state;//��������״̬λ



enum {
    CFG_SMALLFONT,
    CFG_FIRSTRUN
};
//��ȡ���ã��ɹ���������ֵ��ʧ�ܷ���FALSE
#define readCfg(item)    RdWrCfg(item,0,TRUE)

//д����,����ֵ������
#define writeCfg(item,data)   RdWrCfg(item,data,FALSE)

int32 RdWrCfg(uint32 item, int32 data, int32 isRead);



enum {
    DATA_COPY
};
//��ȡ���ݣ��ɹ�����0ʧ�ܷ���-1��output��Ҫ�Լ������ͷ�
#define readData(item,output,len) RdWrData(item,output,len,TRUE)
//д�����ݣ��ɹ�����0ʧ�ܷ���-1
#define writeData(item,data,len) RdWrData(item,data,len,FALSE)
int32 RdWrData(uint32 item, void* data, uint32 len, int32 isRead);


//Ϊͨ��ȫ�ֱ�����ʼ��
int momo_init(void);

int momo_exit(void);

typedef struct STACKDATA {
    int16 stack[64];
    uint8 sp;
}STACKDATA;

//��ʼ������ջ�ռ�
void StackInit(void);

void push(int16 data);

int16 pop(void);

//�����ļ�
int CopyFile(const char* dst,const char* src);


//��Բtype�Ƿ�Ϊʵ��
void circle(int x0,int y0,int r,int color,int type);

//��ȡ��ǰϵͳĿ¼(��ʼ��ʱ����,֮ǰ��Ҫ���ļ�����,�ɹ�����·�����ȡ�ʧ�ܷ���MR_FAILED)
int32 GetCurSystemPath(char * out);

//��ȡĬ��ϵͳĿ¼
int32 GetDefSystemPath(char* out);

//���ļ�·������ļ�����:"c:/mythroad/a.txt"����a.txt,��Ҫfree
char* ExtractFileName(char* path);


//�ַ����ӽ���
char *stred(char *str, int len);

//�����Ľ�����
void MidShadeLine(int x, int y, int w, uint32 pixelA, uint32 pixelB);

/*����һ��

����
f       �ļ����
out     ����ַ���
�ɹ�����0,ʧ�ܷ���-1
*/
int readline(int32 f, char out[256]);


/*������Ļ(��С����)*/
void TextScreen(const char *text, int8 is_unicode);

//ɾ��һ���ļ���(����ɾ��)
int32 removeDir(const char* dirName);

//����Ƿ��޸�
int32 Check(char *key);

//���ӿո�
char *AddWhite(char *str, int32 len);

/*
 �л�MRP����Ŀ¼
 strDiskΪĿ¼�ַ���,��"A:/","B:/"
*/
int32 SwitchDisk(const char* strDisk);  

enum
{
	SHADE_UPDOWN,		//���ϵ���
	SHADE_LEFTRIGHT,	//������
	SHADE_DOWNUP,		//���µ���
	SHADE_RIGHTLEFT		//���ҵ���
};
/*
��һ���������
���룺
xy			xyλ��
wh			��ȸ߶�		
pixelA		��ʼ��ɫ
pixelB		������ɫ
*/
void DrawShadeRect(int16 x, int16 y, int16 w, int16 h, uint32 pixelA, uint32 pixelB, int8 mode);

//ͬ��
void ShadeRect(int x, int y, int w, int h, int AR, int AG, int AB, int BR, int BG, int BB, int mode);

/*��һ��������Ӱ*/
void DrawHatching(int x, int y, int w, int h);

/**/
/*��һ���߿�*/
void DrawRectangle(int x, int y, int w, int h, uint32 pixel);

/*��һ������һ����ȵ��߿�*/
void DrawRectangle2(int x, int y, int w, int h, int line, uint32 pixel);

//ȷ�������Ƿ����㹻�Ŀռ�
int32 getDiskSpace(void);


#define PIXEL888R(pixel)      (uint8)(((pixel) >> 16) & 0xff)
#define PIXEL888G(pixel)      (uint8)(((pixel) >> 8) & 0xff)
#define PIXEL888B(pixel)      (uint8)((pixel) & 0xff)

/* ��һ����ɫ�� */
#define FillBox(x, y, w, h, pixel) \
	mrc_drawRect((int16)(x), (int16)(y), (int16)(w), (int16)(h), PIXEL888R((pixel)), PIXEL888G((pixel)), PIXEL888B((pixel)))

/* ��һ��ˮƽ�� */
#define DrawHLine(x, y, w, pixel) \
	mrc_drawLine((int16)(x), (int16)(y), (int16)((x)+(w)-1), (int16)(y), PIXEL888R(pixel), PIXEL888G(pixel), PIXEL888B(pixel))

void DrawHatchingText(const char *Text, int16 x, int16 y, int is_unicode);

typedef struct COPYMEN{
	int (*arry)[32][32];
	int x;
	int y;
	int w;
	int h;
}COPYMENDATA;

//�����ڴ��
void copymen(COPYMENDATA *dest, COPYMENDATA *src);

void BMPScreen(const char *name, int16 w, int16 h,uint16 Mode, int32 BackColor);

//��ȡ����ʱ��
void GetLocalTimer(char output[6]);

/* ��ͼ , ����ToDir����"bmp/" */
void PrintScreen(const char *ToDir);


/* ��Ļ�м���ʾ���� (��С����)*/
void TextMiddle(const char *text, int8 is_unicode, int8 show);

//�����ַ������(��С����)
int32 strW(char* str, int is_uincode, uint16 font);

//�����ַ����߶�(��С����)
int32 strH(char* str, int is_uincode, uint16 font);

/*
���ļ�����ȡ��չ��
�ɹ������ļ���չ��ָ��,ʧ�ܷ��ؿ�
*/
char* GetFileExt(const char* path);


//����һ�����ȵ�GB�ַ����Ƿ�ȫ�����ذ�ȫ�ĳ���
int32 TestStr(char *str, int32 len);

//����һ��·��,�ɹ�����0ʧ�ܷ���-1
int32 MakePath(char *path);

//��������
void ShadeLine(int x, int y, int w, uint32 pixelA, uint32 pixelB);

//����12��������(ֻunicode)
int32 skyfontWidthHeight(char *szText, int32 *width, int32 *height);

int32 skyfontdraw(char* szText, int16 x, int16 y, mr_screenRectSt rect, mr_colourSt colorst, uint16 flag);


//ɾ���ַ����������ߵĿո�
char *strtrim(char *s);


/*
��ȡMRP�ڲ��ļ���Ϣ
MRPhandle[i]        MRP�ļ����
filename[i]         Ҫ��ȡ��Ϣ���ļ���
filepos[o]          �ļ���MRP�е�λ��
filelen[o]          �ļ���MRP�еĳ���
iszip[o]            �ļ���MRP�з�����ѹ����ʽ���
�ɹ�����0��ʧ�ܷ���-1
*/
int32 GetMRPFileInfo(int32 MRPhandle, char *filename, int32 *filepos, int32 *filelen, int32 *iszip);

//����GB�ַ������ַ���
int32 StrNum(char *str);

//�����ļ�����ͼƬ,ͼƬ��ʽ����ΪBMP24,JPG,GIF��ƽ̨֧�ֵĸ�ʽ
//�ɹ�����MR_SUCCESS,ʧ�ܷ���MR_FAILED��δʵ�ַ���MR_IGNORE.
int DrawIMG(char* filename, int x,int y);
int DrawIMGX(char* filename, int x,int y);


#endif