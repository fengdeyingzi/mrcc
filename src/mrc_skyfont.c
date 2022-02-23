

#include <mrc_base.h>
#include <mrc_bmp.h>
#include "mrc_skyfont.h"

#include "momo.h"

#define MAKER(a) ((a & 0xF800) >> 8)
#define MAKEG(a) ((a & 0x07E0) >> 3)
#define MAKEB(a) ((a & 0x001F) << 3)
#define MAKERGB565(r, g, b) (((uint16)(r >> 3) << 11) | ((uint16)(g >> 2) << 5) | (b >> 3))


/*
sky�������
���Ӱ��
*/

typedef struct
{
	char *bitbuf;
	char *filename;	 //�����ļ���
	long f;			 //�ļ�ָ��
	long font_size;	 //�ֺ�
	long ansi_size;	 //ansi�ַ����
	int width;
	int height;
} FONT;

typedef struct
{
	char width[128];
	char height[128];

} FONT_ANSI;  //����ansi�ַ����

FONT_ANSI *font_ansi;

FONT *font_sky16;
char *font_sky16_bitbuf[32];
static char *font_sky16_filename = NULL;
int font_sky16_f = 0;
int font_sky16_font_size = 16;
int font_sky16_ansi_size = 8;
// typedef void (*mrc_skyfont_load_cb_t)(int32 result);
mrc_skyfont_load_cb_t skyfont_cb;

int xl_font_sky16_init()  //�����ʼ�����������ļ�
{
	int id = 0;
	font_sky16_filename = "system/gb16.uc2";
	font_sky16 = malloc(sizeof(FONT));
	font_ansi = malloc(sizeof(FONT_ANSI));
	//font_sky16_filename = "system/gb16_mrpoid.uc2";

	font_sky16_f = mrc_open(font_sky16_filename, 1);
	//font_sky16_f= open(font_sky16_filename, O_RDONLY, 0777);
	//int f = open(LOGFILE,O_READ,0777);
	//lseek(f,0,2);
	//write(f,text,strlen(text));
	if (font_sky16_f == 0) {
		mrc_printf("%s\n","�������ʧ��");
		if (skyfont_cb != NULL) {
			skyfont_cb(MR_FAILED);
		}
		return -1;
	}

	//gEmulatorCfg.androidDrawChar = FALSE;
	mrc_printf("������سɹ�%d\n", (int)font_sky16_f);
	//font_sky16_bitbuf=malloc(32);
	while (id < 128) {
		font_ansi->width[id] = 8;
		font_ansi->height[id] = 16;
		id++;
	}
	font_sky16_font_size = 16;

	font_sky16_ansi_size = 8;
	if (skyfont_cb != NULL) {
		skyfont_cb(MR_SUCCESS);
	}

	return 0;
}

int xl_font_sky16_close()  //�ر�����
{
	return mrc_close(font_sky16_f);
}

void dpoint(int x, int y, int color) {
	uint16 *screenBuf = w_getScreenBuffer();
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;
	*(screenBuf + y * SCREEN_WIDTH + x) = color;
}

//��ȡ�����ƻ�����ָ�����ص�ֵ
int xl_font_sky16_getfontpix(char *buf, int n) {
	//�����ڵڼ����ֽڣ���0��ʼ
	buf += n / 8;
	//�����ڵڼ�λn%8
	return (128 >> (n % 8)) & *buf;
}
int getfontpix(char *buf, int n)  //��ȡ�����n������Ϣ
{
	//�����ڵڼ����ֽڣ���0��ʼ
	buf += n / 8;
	//�����ڵڼ�λn%8
	return (128 >> (n % 8)) & *buf;
}

//����ַ���λͼ
char *xl_font_sky16_getChar(uint16 id) {
	mrc_seek(font_sky16_f, id * 32, 0);
	//memset(wordBuf, 0, 32);
	mrc_read(font_sky16_f, font_sky16_bitbuf, 32);

	return (char *)font_sky16_bitbuf;
}

//��һ����
char *xl_font_sky16_drawChar(uint16 id, int x, int y, uint16 color) {
	//  printfs("drawChar 16 font");
	// font_sky16_f = mr_open(font_sky16_filename, 1);
	int y2 = y + 16;  //font_sky16_font_size;
	int n = 0;

	int ix = x;
	int iy = 0;
	mrc_seek(font_sky16_f, id * 32, 0);
	//memset(wordBuf, 0, 32);
	mrc_read(font_sky16_f, font_sky16_bitbuf, 32);
	//	mr_close(font_sky16_f);
	//log_i("�������",(int)font_sky16_f);
	//log_i(font_sky16_filename,id);
	//int x2 = x+ font_sky16_font_size;

	for (iy = y; iy < y2; iy++) {
		ix = x;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;

		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
		if (getfontpix((char *)font_sky16_bitbuf, n))
			dpoint(ix, iy, color);
		n++;
		ix++;
	}
	return (char *)font_sky16_bitbuf;
}

//��û����ı��ĸ߶�
int xl_font_sky16_textWidthHeightLines(uint8 *pcText, uint16 showWidth, int32 *width, int32 *height, int32 *lines) {
	return 0;
}

//��ȡһ�����ֵĿ��
void xl_font_sky16_charWidthHeight(uint16 id, int32 *width, int32 *height) {
	if (id < 128) {
		if (width) {
			*width = font_ansi->width[id];
		}
		if (height) {
			*height = font_ansi->height[id];
		}
	} else {
		if (width) {
			*width = 16;
		}
		if (height) {
			*height = 16;
		}
	}
}

//��ȡ�������ֵĿ��
void xl_font_sky16_textWidthHeight(char *text, int32 *width, int32 *height) {
	int textIdx = 0;
	uint16 id = 0;
	int32 fontw = 0, fonth = 0;
	while (text[textIdx] != 0) {
		id = (uint16)((text[textIdx] << 8) | (text[textIdx + 1]));
		xl_font_sky16_charWidthHeight(id, &fontw, &fonth);
		(*width) += fontw;
		(*height) += fonth;
		textIdx += 2;
	}
}
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
int32 mrc_skyfont_drawTextLeft(char *szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, mr_colourSt colorst, uint16 flag) {
	int i = 0;
	uint16 *unText = (uint16 *)szText;
	uint32 color = MAKERGB565(colorst.r, colorst.g, colorst.b);
	uint16 id = 0;
	int32 w, h;
	int16 ix = x, iy = y;
	int max_x = rect.x + rect.w;
	int max_y = rect.y + rect.h;
	int min_x = rect.x;
	int32 lines = 1;
	int32 offindex = off;
	int32 maxlen = (int32)len;
	if(maxlen<0)maxlen = mrc_wstrlen(szText)/2;
	if (max_x > SCREEN_WIDTH)
		max_x = SCREEN_WIDTH;
	if (max_y > SCREEN_HEIGHT)
		max_y = SCREEN_HEIGHT;
	for (i = off; i < maxlen; i++) {
		id = (uint16)(((unText[i] << 8) & 0xff00) | (unText[i] >> 8));
		xl_font_sky16_drawChar(id, ix, iy, color);
		xl_font_sky16_charWidthHeight(id, &w, &h);
		ix += w;
		if ((flag & SKYFONT_SUPPORT_CRLF) && id == 0xa00) {
			iy += h + 2;
			ix = min_x;
			lines++;
		} else if ((flag & SKYFONT_SUPPORT_AUTO_NEWLINE) && ((ix + 16 > max_x) || (id == 0xa00))) {
			ix = min_x;
			iy += h + 2;
			lines++;
		} else if((flag & SKYFONT_SUPPORT_HALF_CHAR) && ((ix+8 > max_x) || (id == 0xa00))){
            ix = min_x;
			iy += h + 2;
			lines++;
		}
		if (ix < max_x && iy < max_y) {
			offindex++;
		}
	}
	return (lines << 20) | offindex;
}

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
int32 mrc_skyfont_textWidthHeight(char *szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, uint16 flag, int32 *width, int32 *height) {
	int i = 0;
	uint16 *unText = (uint16 *)szText;
	uint16 id = 0;
	int32 w, h;
	int16 ix = x, iy = y;
	int max_x = rect.x + rect.w;
	int max_y = rect.y + rect.h;
	int min_x = rect.x;
	int32 lines = 1;
	int32 offindex = off;
	int32 dw = 0, dh = 16;
	int32 maxlen = (int32)len;
	if(maxlen<0)maxlen = mrc_wstrlen(szText)/2;
	if (max_x > SCREEN_WIDTH)
		max_x = SCREEN_WIDTH;
	if (max_y > SCREEN_HEIGHT)
		max_y = SCREEN_HEIGHT;
	for (i = off; i < maxlen; i++) {
		id = (uint16)(((unText[i] << 8) & 0xff00) | (unText[i] >> 8));
		xl_font_sky16_charWidthHeight(id, &w, &h);
		ix += w;
		dw += w;
		if ((flag & SKYFONT_SUPPORT_CRLF) && id == 0xa00) {
			iy += h + 2;
			dh += h + 2;
			ix = min_x;
			lines++;
		} else if ((flag & SKYFONT_SUPPORT_AUTO_NEWLINE) && ((ix + 16 > max_x) || (id == 0xa00))) {
			ix = min_x;
			iy += h + 2;
			dh += h + 2;
			lines++;
		} else if((flag & SKYFONT_SUPPORT_HALF_CHAR) && ((ix+8 > max_x) || (id == 0xa00))){
            ix = min_x;
			iy += h + 2;
			dh += h + 2;
			lines++;
		}
		if (ix < max_x && iy < max_y) {
			offindex++;
		}
	}
	*width = dw;
	*height = dh;
	return (lines << 20) | offindex;
}

/*
 * �����ֿ�
 * fontNum: ������ַ�����, 0�򲻻���
 * ����: MR_SUCCESS�ɹ�, MR_FAILEDʧ��
 */
int32 mrc_skyfont_load(int fontNum, mrc_skyfont_load_cb_t cb) {
	skyfont_cb = cb;
	return xl_font_sky16_init();
}

/*
 * ж���ֿ�,�ͷź��ֿ⽫ֹͣ����,���Ҫ���¹���,��ʹ�� mrc_skyfont_load �ٴμ���
 * ����: MR_SUCCESS�ɹ�, MR_FAILEDʧ��
 */
int32 mrc_skyfont_unload(void) {
	return xl_font_sky16_close();
}

