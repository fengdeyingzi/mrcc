

#include <mrc_base.h>
#include <mrc_bmp.h>
#include "mrc_skyfont.h"

#include "momo.h"

#define MAKER(a) ((a & 0xF800) >> 8)
#define MAKEG(a) ((a & 0x07E0) >> 3)
#define MAKEB(a) ((a & 0x001F) << 3)
#define MAKERGB565(r, g, b) (((uint16)(r >> 3) << 11) | ((uint16)(g >> 2) << 5) | (b >> 3))


/*
sky字体绘制
风的影子
*/

typedef struct
{
	char *bitbuf;
	char *filename;	 //字体文件名
	long f;			 //文件指针
	long font_size;	 //字号
	long ansi_size;	 //ansi字符宽度
	int width;
	int height;
} FONT;

typedef struct
{
	char width[128];
	char height[128];

} FONT_ANSI;  //所有ansi字符宽高

FONT_ANSI *font_ansi;

FONT *font_sky16;
char *font_sky16_bitbuf[32];
static char *font_sky16_filename = NULL;
int font_sky16_f = 0;
int font_sky16_font_size = 16;
int font_sky16_ansi_size = 8;
// typedef void (*mrc_skyfont_load_cb_t)(int32 result);
mrc_skyfont_load_cb_t skyfont_cb;

int xl_font_sky16_init()  //字体初始化，打开字体文件
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
		mrc_printf("%s\n","字体加载失败");
		if (skyfont_cb != NULL) {
			skyfont_cb(MR_FAILED);
		}
		return -1;
	}

	//gEmulatorCfg.androidDrawChar = FALSE;
	mrc_printf("字体加载成功%d\n", (int)font_sky16_f);
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

int xl_font_sky16_close()  //关闭字体
{
	return mrc_close(font_sky16_f);
}

void dpoint(int x, int y, int color) {
	uint16 *screenBuf = w_getScreenBuffer();
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;
	*(screenBuf + y * SCREEN_WIDTH + x) = color;
}

//获取二进制缓存里指定像素的值
int xl_font_sky16_getfontpix(char *buf, int n) {
	//计算在第几个字节，从0开始
	buf += n / 8;
	//计算在第几位n%8
	return (128 >> (n % 8)) & *buf;
}
int getfontpix(char *buf, int n)  //获取字体第n个点信息
{
	//计算在第几个字节，从0开始
	buf += n / 8;
	//计算在第几位n%8
	return (128 >> (n % 8)) & *buf;
}

//获得字符的位图
char *xl_font_sky16_getChar(uint16 id) {
	mrc_seek(font_sky16_f, id * 32, 0);
	//memset(wordBuf, 0, 32);
	mrc_read(font_sky16_f, font_sky16_bitbuf, 32);

	return (char *)font_sky16_bitbuf;
}

//画一个字
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
	//log_i("字体加载",(int)font_sky16_f);
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

//获得换行文本的高度
int xl_font_sky16_textWidthHeightLines(uint8 *pcText, uint16 showWidth, int32 *width, int32 *height, int32 *lines) {
	return 0;
}

//获取一个文字的宽高
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

//获取单行文字的宽高
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
 * 从左往右画字符串,只支持Unicode编码
 * 
 * 输入:
 * szText:    必须是Unicode编码的字符串
 * off:       有效字符串偏移,必须>=0,以一个Unicode占用的字节为单位
 * len:       有效字符串长度,若长度<0,则自动计算长度(以两个'\0'作标志),以一个Unicode占用的字节为单位
 * x,y:       显示文本的左上角x,y坐标
 * rect:      定义可视区域(位于可视区域外的部分将不被显示)
 * colorst:   定义画笔颜色
 * flag:      可以取如下值:(可以用或操作符'|'来表示多种选择)
 *						   0; //默认,不支持换行符(忽略字符),不支持自动换行,不支持半个字符
 *						   SKYFONT_SUPPORT_CRLF; //支持换行符
 *                         SKYFONT_SUPPORT_AUTO_NEWLINE; //支持自动换行(指超出可视区域宽度换行)
 *						   SKYFONT_SUPPORT_HALF_CHAR; //支持半个字符
 *						   *** 注意: 使用换行符或自动换行时, rect将作为排版区域使用 ***
 *
 * 返回:
 * a) 一个32位的int值:
 *					  MRC_SKYFONT_GET_LINE(i) - 占用行数(未被忽略的字符均计算在内,半行算作一行)
 *					  MRC_SKYFONT_GET_OFF(i) - 第一个被忽略的字符的off值,若off==len,则说明全部字符都参与了运算
 *											   被忽略的字符是指: 此字符开始的之后的所有字符,均不可能在可视区域内.
 * b) -1 失败
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
 * 获取字符串的宽和高,同时返回行数
 *
 * 输入:
 * szText:           必须是Unicode编码的字符串
 * off:              有效字符串偏移,必须>=0,以一个Unicode占用的字节为单位
 * len:              有效字符串长度,若长度<0,则自动计算长度(以两个'\0'作标志),以一个Unicode占用的字节为单位
 * x,y:				 显示文本的左上角x,y坐标
 * rect:			 定义可视区域(位于可视区域外的部分将不被显示)(宽和高为-1时,则表示无限)
 * flag:			 可以取如下值:(可以用或操作符'|'来表示多种选择)
 *								  0; //默认,不支持换行符(忽略字符),不支持自动换行,不支持半个字符
 *								  SKYFONT_SUPPORT_CRLF; //支持换行符
 *								  SKYFONT_SUPPORT_AUTO_NEWLINE; //支持自动换行(指超出可视区域宽度换行)
 *								  SKYFONT_SUPPORT_HALF_CHAR; //支持半个字符
 *								  *** 注意: 使用换行符或自动换行时, rect将作为排版区域使用 ***
 *
 * 输出:
 * width:			字符串的宽度(以单行计算)
 * height:			字符串的高度(未被忽略的字符均计算在内)
 * *** 注意: 半个字符算作一个字符来计算宽度和高度 ***
 *
 * 返回:
 * a) 一个32位的int值:
 *					  MRC_SKYFONT_GET_LINE(i) - 占用行数(未被忽略的字符均计算在内,半行算作一行)
 *					  MRC_SKYFONT_GET_OFF(i) - 第一个被忽略的字符的off值,若off==len,则说明全部字符都参与了运算
 *											   被忽略的字符是指: 此字符开始的之后的所有字符,均不可能在可视区域内.
 * b) -1 失败
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
 * 加载字库
 * fontNum: 缓冲的字符个数, 0则不缓冲
 * 返回: MR_SUCCESS成功, MR_FAILED失败
 */
int32 mrc_skyfont_load(int fontNum, mrc_skyfont_load_cb_t cb) {
	skyfont_cb = cb;
	return xl_font_sky16_init();
}

/*
 * 卸载字库,释放后字库将停止工作,如果要重新工作,请使用 mrc_skyfont_load 再次加载
 * 返回: MR_SUCCESS成功, MR_FAILED失败
 */
int32 mrc_skyfont_unload(void) {
	return xl_font_sky16_close();
}

