#include "i18n.h"
#include "application.h"
#include "mainwnd.h"
#include "momo.h"
#include "smp.h"
#include "smp_menu.h"
#include "smp_toolbar.h"
#include "smp_textinfo.h"
#include "smp_menuwnd.h"
#include "smp_edit.h"
#include "smp_button.h"
#include "smp_msgbox.h"
#include "smp_flashbox.h"
#include "bmp.h"
#include "smp_label.h"
#include "smp_progbar.h"
#include "smp_combobox.h"
#include "smp_list.h"
#include "topwnd.h"
#include "mr_string.h"
#include "smp_titlebar.h"
#include "opendlg.h"
#include "smp_inputbox.h"
#include "plt_open.h"
//#include "smp_advbar.h"
#include "help.h"
#include "picoc.h"
#include "mpcrun.h"
#include "xl_debug.h"
#include "xl_coding.h"
#include "FileRW.h"
#include "mrc_graphics.h"
#include "myfunc.h"

//查看输出的文件名
#define newfile "c/print.txt"


static const DWORD miOptions[] = 
{
    STR_EDIT,
    STR_FILE,
    STR_RUN,
    STR_BUILDER,
    STR_OTHER,
    STR_EXIT
};
static const DWORD editOptions[] =
{
    STR_EDITCODE,
    STR_EDITUP,
    STR_EDITDOWN,
    STR_EDITPAT,
    STR_EDITJMP,
    STR_EDITCOPY,
    STR_EDITAFFIX,
    STR_EDITFADD,
    STR_EDITBADD,
    STR_EDITREMOVE
};
static const DWORD fileOptions[] =
{
    STR_NEW,
    SMP_MENU_SEPERATOR,//分隔符
    STR_OPEN,
    STR_SAVE,
    STR_SAVETO
};
static const DWORD otherOptions[] =
{
    STR_SMALLFONT,
    STR_ABOUT,
    STR_HELP
};


//子窗口ID
enum
{
	MAINWND_EDIT = 1,
    MAINWND_TITLEBAR,//标题条
	MAINWND_TOOLBAR,
    MAINWND_TEXTINFO,
	MAINWND_OPTMENU,
	MAINWND_MSGBOXEXIT,
    MAINWND_JMP_INPUTBOX,
    MAINWND_FNAME_INPUT,
    MAINWND_MSG_TONOTEDIR,
    MAINWND_DLG_OPEN //正常打开文件
};
static void CreateChain(PSTR data); /*创建链表*/
static void CreateChain2(PSTR data); /*创建链表*/
static void RefText(void);
static int32 OpenFile(HWND hWnd,const char *filename);
static int32 OpenOtherFile(const char *filename);
static int32 load_program(PCSTR fname);

typedef struct chain  /*定义链表结构体，此链表所有操作从1开始*/  
{
	char txt[514];
	struct chain *next;
}CHAIN;

static HWND hText ;             //文本框句柄
static HWND hToolBar;
static HWND hTitlebar;           //工具条句柄
static int chain_len;        //链表节点数(页数)
static int current;    //当前位置(从1开始)
static CHAIN *chain_head;    //头节点
static char path[256];          //编辑器打开的文件路径
static char path_coding[8];
static UCHAR MAIN_TITLE[256];
static UCHAR CONTENT_TITLE[32];
static UCHAR CONTENT_TEXT[258];
extern char *reload_package,*reload_name;

char advFocus;
/////////////////////////////////////////////////////////

char *getEditPath(void){
return path;
}

static VOID ShowOptMenu(HWND hWnd)
{    
    SMP_Menu_ClearMenuItems();
    SMP_Menu_SetMenuItem2(0, miOptions, TABLESIZE(miOptions));//文件浏览菜单
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions), editOptions, TABLESIZE(editOptions));//编辑
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions)+TABLESIZE(editOptions), fileOptions, TABLESIZE(fileOptions));//文件
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions)+TABLESIZE(editOptions)+TABLESIZE(fileOptions), otherOptions, TABLESIZE(otherOptions));//其它

    if(readCfg(CFG_SMALLFONT))//小字体
        SMP_Menu_CheckMenuItem(21,TRUE);
    ////////////////////////////////////////////
    SMP_Menu_SetSubMenu(0,TABLESIZE(miOptions));
    SMP_Menu_SetSubMenu(1,TABLESIZE(miOptions)+TABLESIZE(editOptions));
    SMP_Menu_SetSubMenu(4,TABLESIZE(miOptions)+TABLESIZE(editOptions)+TABLESIZE(fileOptions));
	
    SMP_Menu_Popup(MAINWND_OPTMENU, SMP_MENUS_BOTTOMLEFT, hWnd, 0, _HEIGHT(hWnd) - SMP_ITEM_HEIGHT, NULL);
}

//设置标题 （GB编码）
static void setMainTitle(char *title){
    PCWSTR temp_un = (PCWSTR)xl_ex_coding(title, mrc_strlen(title)+1,"GB2312", "UNICODE");
            mrc_memcpy(MAIN_TITLE, temp_un, mrc_wstrlen((char*)temp_un)+2);
            SMP_Titlebar_SetContent(hTitlebar, RESID_INVALID, MAIN_TITLE,FALSE);
            mrc_free((void*)temp_un);
}

// 打开文件 自动设置标题栏 自动设置编码 支持打开其它文件 刷新编辑器
static int32 OpenFile(HWND hWnd,const char *filename){
    char *temp_name = NULL;
    char temp[128];
    
	if (load_program((PCSTR)filename)) {
		if (OpenOtherFile(SMP_DIALOG_PATH) == MR_FAILED) {
			SMP_MsgBox(0, hWnd, NULL,
					   SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL);
		}else{
            return 0;
        }

		
	} else {
		mrc_strcpy(path, SMP_DIALOG_PATH);
		temp_name = file_getName(path);
        mrc_sprintf(temp,"%s (%s)",temp_name,path_coding);
		setMainTitle(temp);
		RefText();
		_SET_USERDATA(hWnd, 0);
        return 0;
	}
    return -1;
}

// 打开其它文件
static int32 OpenOtherFile(const char *filename){
    BITMAP_565 *bmp = NULL;
    // char *temp_mrpname, *temp_filename;
    
    char *endName = mrc_strrchr(filename, '.');
    if(endName!=NULL){
        if(mrc_strcmp(endName,".mrp") == 0){
            // temp_mrpname = mrc_malloc(128);
            // temp_filename = mrc_malloc(128);
            // mrc_getReloadFile(&temp_mrpname, &temp_filename);
            // mrc_printf("getReloadFile %s %s\n",temp_mrpname,temp_filename);
            mrc_setReloadFile(mrc_getPackName(), (mrc_getVersion()<2000)?"start.mr":"cfunction.ext");
            // mrc_free(temp_mrpname);
            // mrc_free(temp_filename);
            mrc_runMrp((char*)filename, (mrc_getVersion()<2000)?"start.mr":"cfunction.ext", NULL);
            return 0;
        } else if(mrc_strcmp(endName, ".png") == 0){
            bmp = readBitmap565((char *)filename);
            drawBitmap565(bmp,0,0);
            bitmap565Free(bmp);
            mrc_refreshScreen(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            mrc_sleep(1000);
            return 0;
        } else if(mrc_strcmp(endName, ".bmp") == 0){
            bmp = readBitmap565((char *)filename);
            drawBitmap565(bmp,0,0);
            bitmap565Free(bmp);
            mrc_refreshScreen(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            mrc_sleep(1000);
            return 0;
        }
    }
    return -1;
}

static int32 load_program(PCSTR fname)
{
	int32 handle;
	int32 len;
    PSTR p;
    char *endName = NULL;
	debug_printf("加载文件");
	debug_printf((char*)fname);
	len = mrc_getLen(fname);
    if(len < 0) return -1;
	if (len == 0) {
		CreateChain2(NULL);
		RefText();
	}
	endName = mrc_strrchr(fname,'.');
	if (endName != NULL) {
        if(mrc_strcmp(endName,".c")==0 || mrc_strcmp(endName,".C")==0 || mrc_strcmp(endName,".h")==0 || mrc_strcmp(endName,".H")==0 || mrc_strcmp(endName,".txt")==0 || mrc_strcmp(endName,".TXT")==0){
           if (len > 102400)
			return -1;	//最大100k
		handle = mrc_open(fname, MR_FILE_RDONLY);
		if (!handle)
			return -1;

		p = (PSTR)mrc_malloc(len + 2);
		if (p) {
			mrc_read(handle, p, len);
			p[len] = p[len + 1] = 0;
		} else {
			mrc_close(handle);
			return -1;
		}
		mrc_close(handle);
		CreateChain2(p);
		free(p);
		return 0; 
        }else{
            return -1;
        }
		
	} else {
		return -1;
	}
}

static CHAIN* FindNode(int wz)  /*查找链表中的第chain_current个数据*/
{
	CHAIN *dd;
    int curwz=1;

	if(!chain_head)
	    return NULL;

	if(wz > chain_len)
        wz = chain_len;
    else if(wz < 1) 
        wz = 1;

    dd = chain_head;
	while(curwz < wz)
	{
		dd = dd->next;
        curwz++;
	}
	return dd;
}

static void DelNode(int wz)//删除一个链表项
{
	CHAIN *p1,*p2;
    int curwz=1;

	if(wz<1 || wz > chain_len)
	{
		return;
	}
	p2 = p1 = chain_head;
	while(wz != curwz && p1->next!=NULL)
	{
		p2 = p1;
		p1 = p1->next;
        curwz++;
	}
	if(wz == curwz)
	{
        CHAIN *p;

		if(p1 == chain_head)
        {
            p = chain_head->next;
            if(!p)
            {
               SGL_MEMSET(chain_head->txt,0,514);
               return;
            }
            else
            {
                free(chain_head);
                chain_head = p;
            }
        }
		else
        {
            p = p2->next;
            p2->next = p1->next;
            free(p);
        }
		chain_len--;// 链表长度减1
	}
}

static void Insert(CHAIN *data, int wz)//插入一个链表项
{
	CHAIN *ph,*p2;
    int curwz=1;

	p2 = ph = chain_head;
	if(!chain_head)
	{
		chain_head = data;
		chain_head->next=NULL;
	}
	else
	{
		while((wz > curwz) && (ph->next != NULL))
		{
			p2 = ph;// 保存上一个结点
			ph = ph->next;// 移到下一个结点
            curwz++;
		}
		if(wz <= curwz) //之前或当前
		{
			if(chain_head == ph) chain_head = data;
			else p2->next = data; // 上一个结点的下一下结点是插入的数据
			data->next = ph; // 插入的数据的下一下结点
		}
		else //最末尾
		{
			ph->next = data;
			data->next = NULL;
		}
	}
	chain_len++;
}

void CreateChain2(PSTR data) /*创建链表*/
{
    // UnicodeSt uniText;
    CHAIN *dd;
    int32 curwz;
    int32 item_len;
    char *temp_un = NULL;
    char *temp_node_un = NULL;
    int32 is_gbk = TRUE;
    // char *endName = NULL;
    is_gbk = isGB2312(data, mrc_strlen(data));
    if(is_gbk){
        mrc_strcpy(path_coding,"GB2312");
    }else{
        mrc_strcpy(path_coding,"UTF-8");
    }
    temp_un = xl_ex_coding(data, mrc_strlen(data), path_coding, "UNICODE");
    temp_node_un = temp_un;
    curwz = current = 1; //初始化页面为第一页
    
	dd = chain_head;
	do {
        item_len = TestUNStr((uint16*)temp_node_un,200); //返回的长度其实是un字符数，非字节数
        if(item_len)
        {
            if(!dd)
            {
                dd=(CHAIN*)mrc_malloc(sizeof(CHAIN));
                Insert(dd,curwz);
            }
            SGL_MEMSET(dd->txt,0,514);//在插入链表时会对NEXT进行赋值所以不必关心NEXT。
            // CharToUnicode(code, &uniText.pText, &uniText.len);
            
            mrc_memcpy((PWSTR)dd->txt, (PCWSTR)temp_node_un,item_len*2);
	        // mrc_freeOrigin(uniText.pText, uniText.len);
	        dd = dd->next;
            temp_node_un+=item_len*2;
            curwz++;
        }
	} while(item_len);

    
    item_len = chain_len;//删除多余的链表,因为删除时chain_len的值会不断改变所以用aa来代替
    while(item_len >= curwz)
    {
        DelNode(curwz);
        item_len--;
    }
}

void CreateChain(PSTR data) /*创建链表*/
{
    UnicodeSt uniText;
    PSTR code;
    CHAIN *dd;
    int32 curwz;
    int32 aa;

    curwz = current = 1;
    code = (PSTR)SGL_MALLOC(514);
	dd = chain_head;
	do {
        aa = TestStr(data,255);
        if(aa)
        {
            if(!dd)
            {
                dd=(CHAIN*)mrc_malloc(sizeof(CHAIN));
                Insert(dd,curwz);
            }
            SGL_MEMSET(dd->txt,0,514);//在插入链表时会对NEXT进行赋值所以不必关心NEXT。
            SGL_MEMSET(code,0,514);//这两次memset都是必需的！！！
            mrc_strncpy(code,data,aa);
            CharToUnicode(code, &uniText.pText, &uniText.len);
            wstrncpy((PWSTR)dd->txt, (PCWSTR)uniText.pText,512);
	        mrc_freeOrigin(uniText.pText, uniText.len);
	        dd = dd->next;
            data+=aa;
            curwz++;
        }
	} while(aa);
    mrc_free(code);
    aa = chain_len;//删除多余的链表,因为删除时chain_len的值会不断改变所以用aa来代替
    while(aa >= curwz)
    {
        DelNode(curwz);
        aa--;
    }
}

void FreeChain(void)//释放整个链表
{
	CHAIN *dd;

	while(chain_head)
    {
		dd = chain_head->next;
		free(chain_head);
		chain_head = dd;
	}
}

static int Insert1(int wz)//插入一个节点(页)
{   
    CHAIN *dd;

    dd = (CHAIN*)mrc_malloc(sizeof(CHAIN));
    if(!dd) return -1;
    SGL_MEMSET(dd->txt,0,514);//在插入链表时会对NEXT进行赋值所以不必关心NEXT。
    Insert(dd,wz);
    return 0;
}
static int NodePat(void)//分页是将当前页分成两页，把当前页的前半部分内容放到后插入的节点中
{
	CHAIN *pat1, *pat2;

    pat2 = FindNode(current);
	if(!pat2)
	    return -1;
    if(Insert1(current))//前插入
        return -1;
    pat1 = FindNode(current);
	if(!pat1)
	    return -1;

    memcpy(pat1->txt,pat2->txt,256);//前半部分到新节点

    mrc_memmove(pat2->txt,pat2->txt+256,514-256);//将后半部分内容前移
    pat2->txt[259]=pat2->txt[260]='\0';

    return 0;
}

/////////////////////////////////////////////////////////////////////
//xldebug 修复保存代码造成文件清空问题
int32 SaveCode(PSTR name)
{
    int32 f = 0;
	int32 code_len = 0;
	char temp[300];
	PSTR code;
	CHAIN *tmp=chain_head;
	//计算代码长度
	while(tmp){
        code = UnicodeToChar((PCWSTR)tmp->txt);  
		code_len += mrc_strlen(code);
        tmp = tmp->next;
		SGL_FREE(code);
    }
	if(code_len<=0)return -1;
    if(!name) return -1;
	mrc_sprintf(temp, "%s.bak", name);
	//不删除文件，而是直接重命名
    mrc_remove(temp);
	mrc_rename(name, temp);
    f = mrc_open(name,4|8);
    if(!f)
        return -1;
    else
    {
        
        tmp=chain_head;

        while(tmp)
        {
            code = UnicodeToChar((PCWSTR)tmp->txt);  
			code_len = mrc_strlen(code);
            if(code)
            {
                mrc_write(f,code,mrc_strlen(code));
                SGL_FREE(code);
            }
            tmp = tmp->next;
        }
        mrc_close(f);
    }
    return 0;
}



static void RefText(void)
{
    CHAIN *tmp;
    static char txt[60];
    UnicodeSt uniText;
    mr_datetime timer;

    if(current > chain_len)
        current = chain_len;
    else if(current < 1) 
        current =1;

    mrc_getDatetime(&timer);
    mrc_sprintf(txt,"%d/%d %d:%02d",current,chain_len,timer.hour,timer.minute);
    CharToUnicode(txt, &uniText.pText, &uniText.len);
    wstrcpy((PWSTR)txt, (PCWSTR)uniText.pText);
	mrc_freeOrigin(uniText.pText, uniText.len);

    tmp = FindNode(current);
    SMP_TextInfo_SetContent(hText,(PCWSTR)tmp->txt);
    SGL_UpdateWindow(hText);
    SMP_Toolbar_SetStrings2(hToolBar,SGL_LoadString(STR_MENU),(PCWSTR)txt,NULL,TRUE);
	SMP_Titlebar_SetContentR(hTitlebar,(PCWSTR)txt,TRUE);
}

static void MenuEvent(HWND hWnd, WORD code)
{
    int32 printFileLen = 0;
    
    char *temp_buf = NULL;
    char *temp_un = NULL;
    char *temp_title_un = NULL;
    switch(code)
	{
	case STR_EXIT: // 退出
		SMP_MsgBox(MAINWND_MSGBOXEXIT, hWnd, NULL, SGL_LoadString(STR_MSG), SGL_LoadString(STR_HINT1), ID_OK|ID_CANCEL|ID_YESNO , NULL);
		break;
    case STR_NEW: //新建
        printFileLen = mrc_getLen(newfile);
        if(printFileLen==-1){
            SMP_MsgBox(0, hWnd, NULL, 
                SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL); 
        }else if(printFileLen<128){
            temp_buf = mrc_malloc(258);
            my_readAllEx(newfile, temp_buf, &printFileLen);
            temp_buf[printFileLen] = 0;
            temp_un = xl_ex_coding(temp_buf,printFileLen,"GB2312","UNICODE");
            temp_title_un = xl_ex_coding(newfile, mrc_strlen(newfile), "GB2312","UNICODE");
            mrc_memcpy(CONTENT_TITLE, temp_title_un, mrc_wstrlen(temp_title_un)+2);
            mrc_memcpy(CONTENT_TEXT, temp_un, mrc_wstrlen(temp_un)+2);
            SMP_MsgBox(0, hWnd, NULL, 
                CONTENT_TITLE, CONTENT_TEXT, ID_OK, NULL); 
            mrc_free(temp_un);
            mrc_free(temp_title_un);
            mrc_free(temp_buf);
        }
        else if(load_program(newfile))
        {
            SMP_MsgBox(0, hWnd, NULL, 
                SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL); 
            return;
        }else{
        path[0]=0;
        setMainTitle(newfile);
        RefText();
        }
		
        break;
    case STR_RUN: //运行
        SaveCode(path); //xldebug
		setRunPath(path);//设置运行文件的路径 tempfile_path并没有被释放
        CreateChain(NULL);//释放编辑器内存
        _FUNCSET_STYLE(FUNC_RELOADTXT);//让编辑器能够重新打开文件
        PicocRun(0);
        break;
    case STR_SMALLFONT://小字体
        {
            char data=0;

            if(readCfg(CFG_SMALLFONT))//非小字体时设置下次为小字体
                data=FALSE;
            else
                data=TRUE;
            writeCfg(CFG_SMALLFONT,data);
            SMP_MsgBox(0,hWnd,NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SETSUC),ID_OK,NULL);
            return;
        }
    case STR_OPEN://打开
        ShowOpenDlg(MAINWND_DLG_OPEN, TOPWND_MAINWND, DIALOG_SELECTFILE);
        break;
    case STR_ABOUT: //关于
        {
            UnicodeSt uniText;
            char tmp[256];
            int mainUsed,mainLeft,mainUp;

            mainUp=mrc_getMemStatus(&mainUsed, &mainLeft, NULL, NULL, NULL, NULL);
            mrc_sprintf(tmp,"风的影子 修改\r\n原作者：默水瓶\n内存:\n峰值%dB\n使用%dB\n剩余%dB\n手机C论坛：http://bbs.yzjlb.net",mainUp,mainUsed,mainLeft);
            CharToUnicode(tmp, &uniText.pText, &uniText.len);
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_ABOUT),(PWSTR)uniText.pText, ID_OK|SMP_MSGBOXS_AUTOCLOSE,NULL);
            mrc_freeOrigin(uniText.pText, uniText.len);
        }
        break;
    case STR_HELP: //帮助
        ShowHELP(TOPWND_MAINWND);
        break;
    case STR_EDITPAT: //分割页
        if(NodePat())
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_CANNOTPAT), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITCODE:  //编辑代码
        if(FALSE == advFocus)
        {
            //mrc_advStopDraw();//如果没有这句，菜单显示时将导致菜单被覆盖
            SGL_TextInput(hWnd);
        }
        break;
    case STR_EDITUP:  //上一页
        current--;
        RefText();
        break;
    case STR_EDITDOWN:  //下一页
        current++;
        RefText();
        break;
    case STR_EDITJMP:  //转到某页
        {
            UnicodeSt uniText;
            char tmp[20];

            mrc_sprintf(tmp,"%d",current);
            CharToUnicode(tmp, &uniText.pText, &uniText.len);
            SMP_InputBox(MAINWND_JMP_INPUTBOX, hWnd, SGL_LoadString(STR_EDITJMP1), (PCWSTR)uniText.pText, 10, ES_NUM, NULL);
            mrc_freeOrigin(uniText.pText, uniText.len);
        }
        break;
    case STR_EDITCOPY: // 复制本页
        {
            CHAIN *cur=NULL;

            cur = FindNode(current);
	        if(!cur)
	            return;
            else
               writeData(DATA_COPY,cur->txt,514);
        }
        break;
    case STR_EDITAFFIX: // 粘贴此页
        {
	        CHAIN *cur=NULL;

            cur = FindNode(current);
	        if(!cur)
	            return;
            else
            {
                int len;
                char *data;

                len = 514-mrc_wstrlen(cur->txt);
                data=mrc_malloc(len);
                readData(DATA_COPY,data,len);
                wstrncat((PWSTR)cur->txt,(PCWSTR)data,len);
                mrc_free(data);
            }
            RefText();
        }
        break;
    case STR_EDITFADD:	//前插入页
        if(Insert1(current))
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_1), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITBADD:	//后插入页
        current++;
        if(Insert1(current))
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_1), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITREMOVE: // 删除本页
        DelNode(current);
        RefText();
        break;
    case STR_SAVE: // 保存
        if(!path[0])
            goto saveto;//没有路径，另存
        else
        {
            if(!SaveCode(path))
		        SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVESUC), ID_OK,NULL);
            else
                SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVEFAI), ID_OK,NULL);
        }
        break;
    case STR_SAVETO:// 另存为 
saveto:
            SMP_InputBox(MAINWND_FNAME_INPUT, hWnd, SGL_LoadString(STR_INPUTNAME), SGL_LoadString(STR_TMPNAME), 128, ES_ALPHA, NULL);
        break;
    case STR_BUILDER: // 打包mrp
        if(!path[0]){ //请先打开文件
            SMP_MsgBox(0,hWnd, NULL, SGL_LoadString(STR_MSG),SGL_LoadString(STR_PLEASEOPEN),ID_OK, NULL );
        }
        else if(checkEndName(path, ".c")){
            mrc_drawText("开始打包",0,0,240, 0, 0,0,1);
            mrc_refreshScreen(0,0,SCREEN_WIDTH,24);
            packProject(path);
            SMP_MsgBox(0,hWnd, NULL, SGL_LoadString(STR_MSG),SGL_LoadString(STR_BUILDOK),ID_OK, NULL );
        }else{ //你打开的不是C文件
            SMP_MsgBox(0,hWnd, NULL, SGL_LoadString(STR_MSG),SGL_LoadString(STR_NOTCLANG),ID_OK, NULL );
        }
        // if(path)
        // SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_BUILDERERROR), ID_OK,NULL);
        break;
    }
}

static void KeyUpEvent(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
    case MR_KEY_UP:
        //mrc_advFocus();
        advFocus=TRUE;
        return;
    case MR_KEY_DOWN:
        //mrc_advUnFocus();
        advFocus=FALSE;
        return;
	case MR_KEY_SOFTLEFT:
		ShowOptMenu(hWnd);
		return;
	case MR_KEY_SOFTRIGHT://按右键
		return;
    case MR_KEY_0:// 复制本页
        MenuEvent(hWnd,STR_EDITCOPY);
        return;
    case MR_KEY_1: //下一页
        MenuEvent(hWnd,STR_EDITDOWN);
        return;
    case MR_KEY_2:// 转到某页
        MenuEvent(hWnd,STR_EDITJMP);
        return;
    case MR_KEY_3://前插入页
        MenuEvent(hWnd,STR_EDITFADD);
        return;
    case MR_KEY_4: //上一页
        MenuEvent(hWnd,STR_EDITUP);
        return;
    case MR_KEY_5://编辑代码
    case MR_KEY_SELECT:
        MenuEvent(hWnd,STR_EDITCODE);
        return;
    case MR_KEY_6://后插入页
        MenuEvent(hWnd,STR_EDITBADD);
        return;
    case MR_KEY_7:// 分割页
        MenuEvent(hWnd,STR_EDITPAT);
        return;
    case MR_KEY_9: //运行mpc
        MenuEvent(hWnd,STR_RUN);
        return;
    case MR_KEY_POUND:// 粘贴此页
        MenuEvent(hWnd,STR_EDITAFFIX);
        return;
    case MR_KEY_STAR:// 删除本页
        MenuEvent(hWnd,STR_EDITREMOVE);
        return;
	}
}

static void command(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    WID id = LOWORD(wParam);
    WORD code = HIWORD(wParam);

    switch(id)
    {
    case MAINWND_OPTMENU:
        MenuEvent(hWnd, code);
        break;
    case MAINWND_MSGBOXEXIT:
        switch(code)
        {
        case ID_OK:
            _FUNCSET_STYLE(FUNC_EXIT);
            mrc_setReloadFile(reload_package,reload_name);
            mrc_exit();
            return;
        }
        break;
    case MAINWND_JMP_INPUTBOX:
        {
            if(code == INPUT_OK)
            {
                PWSTR str = (PWSTR)lParam;
                PSTR tt=NULL;
                int32 data;

                tt = UnicodeToChar(str);
                data = mrc_atoi(tt);
                SGL_FREE(tt);
                current = data;
                RefText();
            }
        }
        break;
    case MAINWND_FNAME_INPUT:
        {
            if(code == INPUT_OK)
            {
                PWSTR str = (PWSTR)lParam;
                PSTR tt=NULL;

                tt = UnicodeToChar(str);
                mrc_strcpy(path,tt);//保存当前输入的文件名
                SGL_FREE(tt);
                if(!SaveCode(path))
                {
                    SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVESUC), ID_OK,NULL);
                }
                else
                {
                    path[0]=0;
                    SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVEFAI), ID_OK,NULL); 
                }
            }
        }
        break;
    case MAINWND_TITLEBAR:
        {
            //code即是下载完成或访问完成的结果
//             FPRINTF("advret:%d",code);
        }

    }//swithc(id)
}

static void ShowEvent(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    char *temp_name = NULL;
    
    if(_FUNCIS_SET_ANY(FUNC_LOAD))
    {
        if(0 == readCfg(CFG_FIRSTRUN))//第一次使用，显示欢迎
        {
            load_program("c/欢迎.txt");
            writeCfg(CFG_FIRSTRUN,_VERSION);
            RefText();
        }
        if(tempfile_path !=NULL && mrc_fileState((PSTR)tempfile_path)==MR_IS_FILE)
        {
            _FUNCCLR_STYLE(FUNC_LOAD);
            load_program(tempfile_path);
            //mrc_remove(tempfile_path);
            _SET_USERDATA(hWnd,0);
            RefText();
        }
    }
    if(SMP_DIALOG_ID==MAINWND_DLG_OPEN)
    {
        if(_USERDATA(hWnd) == DIALOG_GET)
        {
            OpenFile(hWnd, SMP_DIALOG_PATH);
            // if(load_program(SMP_DIALOG_PATH))
            // {
            //     if(OpenOtherFile(SMP_DIALOG_PATH) == MR_FAILED){
            //         SMP_MsgBox(0, hWnd, NULL, 
            //         SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL); 
            //     }
                
            //     return;
            // }else{
            //     mrc_strcpy(path, SMP_DIALOG_PATH);
            //     temp_name = file_getName(path);
            //     setMainTitle(temp_name);
            //     RefText();
            //     _SET_USERDATA(hWnd,0);
            // }
            
        }
    }
}
LRESULT MAINWND_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	
	switch(Msg)
	{
	case WM_CREATE:
	{
        path[0]=0;
        advFocus = chain_len = 0;//chain_len因为下面会插入一个所以应置0而不是1
	    current = 1;
        chain_head = NULL;
        Insert1(current);//插入第一个链表
        _FUNCSET_STYLE(FUNC_LOAD);

        //标题栏XL
 		hTitlebar = SGL_CreateWindow(SMP_Titlebar_WndProc,
 			0, 0, SCREEN_WIDTH, SMP_ITEM_HEIGHT,
 			MAINWND_TITLEBAR, 
 			SMP_TITLEBAR_STATIC, 0);
 		_FGCOLOR(hTitlebar) =  COLOR_lightwhite ;/* 标题文字颜色 */
 		SMP_Titlebar_SetContent(hTitlebar, RESID_INVALID, SGL_LoadString(STR_TITLE),FALSE);
 		SGL_AddChildWindow(hWnd, hTitlebar);


        //文本框
        hText = SGL_CreateWindow(SMP_TextInfo_WndProc,
            0,SMP_ITEM_HEIGHT,SCREEN_WIDTH,SCREEN_HEIGHT - SMP_ITEM_HEIGHT-SMP_ITEM_HEIGHT,
            MAINWND_TEXTINFO,WS_TABSTOP,0);
        _BGCOLOR(hText) = 0x444444;
        _FGCOLOR(hText) = 0x00f000;
        SMP_TextInfo_SetContent(hText,(PWSTR)chain_head->txt);
		SGL_AddChildWindow(hWnd, hText);

		//创建工具栏
		hToolBar = SGL_CreateWindow(SMP_Toolbar_WndProc, 
			0,  _HEIGHT(hWnd) - SMP_ITEM_HEIGHT, 
			_WIDTH(hWnd), SMP_ITEM_HEIGHT,
			MAINWND_TOOLBAR,
			0, 0);
		SMP_Toolbar_SetStrings2(hToolBar, SGL_LoadString(STR_MENU), NULL, NULL, FALSE);
		SGL_AddChildWindow(hWnd, hToolBar);

        //SMP_Advbar_AddToParent(hWnd,0,0,SCREEN_WIDTH,MAINWND_TITLEBAR,NULL);
        //SMP_Advbar_SetInfo(8000094,enable_smallfont);

        return 0;
	}
    case WM_DESTROY:
    {
        FreeChain();
        return 0;
    }
    case WM_INITFOCUS:
    {
        SGL_SetFocusWindow(hWnd,hText);
        return 0;
    }
//     case WM_HIDE:
    case WM_MENUSHOW:
    case WM_MODALSHOW:
        advFocus=FALSE;
        //mrc_advUnFocus();
        //mrc_advStopDraw();//如果没有这句，菜单显示时将导致菜单被覆盖
        break;
    case WM_PAINT:
        if(_FUNCIS_SET_ANY(FUNC_RELOADTXT))
        {
            _FUNCCLR_STYLE(FUNC_RELOADTXT);
            load_program(path); //xldebug
            RefText();
        }
    case WM_MENUHIDE:
    case WM_MODALHIDE:
        break;
    case WM_SHOW:
    {
        ShowEvent(hWnd, Msg, wParam, lParam);
        return 0;
    }
	case WM_KEYUP:
	{
        KeyUpEvent(hWnd, Msg, wParam, lParam);
        return 1;
	}
	case WM_COMMAND:
	{
        command(hWnd, Msg, wParam, lParam);
        return 0;
	}
    case WM_GETEDITINFO:
    {
		SGL_EditInfo* info = (SGL_EditInfo*)wParam;
        CHAIN *tmp;

        tmp = FindNode(current);
		info->title = SGL_LoadString(STR_EDIT);
		info->buffer = (PWSTR)tmp->txt;
		info->size = 512;
        return 0;
    }
    case WM_SETEDITTEXT:
	{
		PCWSTR pContent = (PCWSTR)wParam;
        CHAIN *tmp;
        mrc_printf("--> WM_setEditText ");
        tmp = FindNode(current);

        wstrncpy((PWSTR)tmp->txt, pContent,512);
        mrc_printf("--> copy Text");
        RefText();
        mrc_printf("--> RefText OK");
        return 0;
	}

	}
	return SMP_MenuWnd_WndProc(SGL_FindChildWindow(hWnd,MAINWND_TOOLBAR),hWnd, Msg, wParam, lParam);
}

