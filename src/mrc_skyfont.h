#ifndef _MRC_SKYFONT_H_
#define _MRC_SKYFONT_H_

//字间距
#define SKYFONT_WORD_SPACE (0)
//行间距
#define SKYFONT_LINE_SPACE (1)

//小字体宽, ASCII码的字符被定义为小字体
#define SKYFONT_SMALL_WIDTH (8)
//大字体宽, 非ASCII码的字符被定义为大字体
#define SKYFONT_LARGE_WIDTH (12)
//字体高
#define SKYFONT_HEIGHT (12)

//是否支持\r或\n换行符
#define SKYFONT_SUPPORT_CRLF 1
//是否支持超出可视宽时自动换行
#define SKYFONT_SUPPORT_AUTO_NEWLINE 2
//是否支持显示半个字符
#define SKYFONT_SUPPORT_HALF_CHAR 4
//以上三个选项可以使用任意组合,组合使用或操作符 | 来进行

//计算返回值中的行数
#define MRC_SKYFONT_GET_LINE(i) (((unsigned int)((i)&0xFFF00000))>>20)
//计算返回值中的off值
#define MRC_SKYFONT_GET_OFF(i) ((unsigned int)((i)&0x000FFFFF))

typedef struct _skyfont_screenRect_t {
	int16 x;
	int16 y;
	int16 w;
	int16 h;
} skyfont_screenRect_t;

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
extern int32 mrc_skyfont_drawTextLeft(char* szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, mr_colourSt colorst, uint16 flag);

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
extern int32 mrc_skyfont_textWidthHeight(char *szText, int off, int len, int16 x, int16 y, skyfont_screenRect_t rect, uint16 flag, int32 *width, int32 *height);

/*
 * mrc_skyfont_load 回调接口
 * result: 字库加载的结果: MR_SUCCESS成功 或 MR_FAILED失败
 */
typedef void (*mrc_skyfont_load_cb_t)(int32 result);

/*
 * 加载字库
 * fontNum: 缓冲的字符个数, 0则不缓冲
 * 返回: MR_SUCCESS成功, MR_FAILED失败
 */
extern int32 mrc_skyfont_load(int fontNum, mrc_skyfont_load_cb_t cb);

/*
 * 卸载字库,释放后字库将停止工作,如果要重新工作,请使用 mrc_skyfont_load 再次加载
 * 返回: MR_SUCCESS成功, MR_FAILED失败
 */
extern int32 mrc_skyfont_unload(void);

#endif