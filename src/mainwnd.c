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
#include "string.h"
#include "smp_titlebar.h"
#include "opendlg.h"
#include "smp_inputbox.h"
#include "plt_open.h"
//#include "smp_advbar.h"
#include "help.h"
#include "picoc.h"
#include "mpcrun.h"
#include "xl_debug.h"

//�鿴������ļ���
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
    SMP_MENU_SEPERATOR,//�ָ���
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


//�Ӵ���ID
enum
{
	MAINWND_EDIT = 1,
    MAINWND_TITLEBAR,//������
	MAINWND_TOOLBAR,
    MAINWND_TEXTINFO,
	MAINWND_OPTMENU,
	MAINWND_MSGBOXEXIT,
    MAINWND_JMP_INPUTBOX,
    MAINWND_FNAME_INPUT,
    MAINWND_MSG_TONOTEDIR,
    MAINWND_DLG_OPEN //�������ļ�
};
static void CreateChain(PSTR data); /*��������*/
static void RefText(void);


typedef struct chain  /*��������ṹ�壬���������в�����1��ʼ*/  
{
	char txt[514];
	struct chain *next;
}CHAIN;

static HWND hText ;             //�ı�����
static HWND hToolBar;
static HWND hTitlebar;           //���������
static int chain_len;        //����ڵ���(ҳ��)
static int current;    //��ǰλ��(��1��ʼ)
static CHAIN *chain_head;    //ͷ�ڵ�
static char path[256];          //�༭���򿪵��ļ�·��
char advFocus;
/////////////////////////////////////////////////////////

char *getEditPath(void){
return path;
}

static VOID ShowOptMenu(HWND hWnd)
{    
    SMP_Menu_ClearMenuItems();
    SMP_Menu_SetMenuItem2(0, miOptions, TABLESIZE(miOptions));//�ļ�����˵�
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions), editOptions, TABLESIZE(editOptions));//�༭
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions)+TABLESIZE(editOptions), fileOptions, TABLESIZE(fileOptions));//�ļ�
    SMP_Menu_SetMenuItem2(TABLESIZE(miOptions)+TABLESIZE(editOptions)+TABLESIZE(fileOptions), otherOptions, TABLESIZE(otherOptions));//����

    if(readCfg(CFG_SMALLFONT))//С����
        SMP_Menu_CheckMenuItem(21,TRUE);
    ////////////////////////////////////////////
    SMP_Menu_SetSubMenu(0,TABLESIZE(miOptions));
    SMP_Menu_SetSubMenu(1,TABLESIZE(miOptions)+TABLESIZE(editOptions));
    SMP_Menu_SetSubMenu(4,TABLESIZE(miOptions)+TABLESIZE(editOptions)+TABLESIZE(fileOptions));
	
    SMP_Menu_Popup(MAINWND_OPTMENU, SMP_MENUS_BOTTOMLEFT, hWnd, 0, _HEIGHT(hWnd) - SMP_ITEM_HEIGHT, NULL);
}



static int32 load_program(PCSTR fname)
{
	int32 handle;
	int32 len;
    PSTR p;
	debug_printf("�����ļ�");
	debug_printf((char*)fname);
	len = mrc_getLen(fname);
    if(len < 0) return -1;
    if(len == 0)
    {
        CreateChain(NULL);
        RefText();
    }
    if(len > 102400) return -1;//���100k
    handle = mrc_open(fname, MR_FILE_RDONLY);
	if(!handle) return -1;

    p = (PSTR)mrc_malloc(len+2);
	if(p)
    {
		mrc_read(handle,p,len);
        p[len]=p[len+1]=0;
    }
	else
	{
		mrc_close(handle);
		return -1;
	}
	mrc_close(handle);
    CreateChain(p);
    free(p);
	return 0;
}

static CHAIN* FindNode(int wz)  /*���������еĵ�chain_current������*/
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

static void DelNode(int wz)//ɾ��һ��������
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
		chain_len--;// �����ȼ�1
	}
}

static void Insert(CHAIN *data, int wz)//����һ��������
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
			p2 = ph;// ������һ�����
			ph = ph->next;// �Ƶ���һ�����
            curwz++;
		}
		if(wz <= curwz) //֮ǰ��ǰ
		{
			if(chain_head == ph) chain_head = data;
			else p2->next = data; // ��һ��������һ�½���ǲ��������
			data->next = ph; // ��������ݵ���һ�½��
		}
		else //��ĩβ
		{
			ph->next = data;
			data->next = NULL;
		}
	}
	chain_len++;
}


void CreateChain(PSTR data) /*��������*/
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
            SGL_MEMSET(dd->txt,0,514);//�ڲ�������ʱ���NEXT���и�ֵ���Բ��ع���NEXT��
            SGL_MEMSET(code,0,514);//������memset���Ǳ���ģ�����
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
    aa = chain_len;//ɾ�����������,��Ϊɾ��ʱchain_len��ֵ�᲻�ϸı�������aa������
    while(aa >= curwz)
    {
        DelNode(curwz);
        aa--;
    }
}

void FreeChain(void)//�ͷ���������
{
	CHAIN *dd;

	while(chain_head)
    {
		dd = chain_head->next;
		free(chain_head);
		chain_head = dd;
	}
}

static int Insert1(int wz)//����һ���ڵ�(ҳ)
{   
    CHAIN *dd;

    dd = (CHAIN*)mrc_malloc(sizeof(CHAIN));
    if(!dd) return -1;
    SGL_MEMSET(dd->txt,0,514);//�ڲ�������ʱ���NEXT���и�ֵ���Բ��ع���NEXT��
    Insert(dd,wz);
    return 0;
}
static int NodePat(void)//��ҳ�ǽ���ǰҳ�ֳ���ҳ���ѵ�ǰҳ��ǰ�벿�����ݷŵ������Ľڵ���
{
	CHAIN *pat1, *pat2;

    pat2 = FindNode(current);
	if(!pat2)
	    return -1;
    if(Insert1(current))//ǰ����
        return -1;
    pat1 = FindNode(current);
	if(!pat1)
	    return -1;

    memcpy(pat1->txt,pat2->txt,256);//ǰ�벿�ֵ��½ڵ�

    mrc_memmove(pat2->txt,pat2->txt+256,514-256);//����벿������ǰ��
    pat2->txt[259]=pat2->txt[260]='\0';

    return 0;
}

/////////////////////////////////////////////////////////////////////
int32 SaveCode(PSTR name)
{
    int32 f = 0;

    if(!name) return -1;
    mrc_remove(name);
    f = mrc_open(name,4|8);
    if(!f)
        return -1;
    else
    {
        PSTR code;
        CHAIN *tmp=chain_head;

        while(tmp)
        {
            code = UnicodeToChar((PCWSTR)tmp->txt);         
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
    switch(code)
	{
	case STR_EXIT: // �˳�
		SMP_MsgBox(MAINWND_MSGBOXEXIT, hWnd, NULL, SGL_LoadString(STR_MSG), SGL_LoadString(STR_HINT1), ID_OK|ID_CANCEL|ID_YESNO , NULL);
		break;
    case STR_NEW: //�½�
        if(load_program(newfile))
        {
            SMP_MsgBox(0, hWnd, NULL, 
                SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL); 
            return;
        }
		path[0]=0;
        RefText();
        break;
    case STR_RUN: //����
        SaveCode(path); //xldebug
		setRunPath(path);//���������ļ���·�� tempfile_path��û�б��ͷ�
        CreateChain(NULL);//�ͷű༭���ڴ�
        _FUNCSET_STYLE(FUNC_RELOADTXT);//�ñ༭���ܹ����´��ļ�
        PicocRun(0);
        break;
    case STR_SMALLFONT://С����
        {
            char data=0;

            if(readCfg(CFG_SMALLFONT))//��С����ʱ�����´�ΪС����
                data=FALSE;
            else
                data=TRUE;
            writeCfg(CFG_SMALLFONT,data);
            SMP_MsgBox(0,hWnd,NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SETSUC),ID_OK,NULL);
            return;
        }
    case STR_OPEN://��
        ShowOpenDlg(MAINWND_DLG_OPEN, TOPWND_MAINWND, DIALOG_SELECTFILE);
        break;
    case STR_ABOUT: //����
        {
            UnicodeSt uniText;
            char tmp[256];
            int mainUsed,mainLeft,mainUp;

            mainUp=mrc_getMemStatus(&mainUsed, &mainLeft, NULL, NULL, NULL, NULL);
            mrc_sprintf(tmp,"���Ӱ�� �޸�\r\nԭ���ߣ�Ĭˮƿ\n�ڴ�:\n��ֵ%dB\nʹ��%dB\nʣ��%dB\n�ֻ�C��̳��http://bbs.yzjlb.net",mainUp,mainUsed,mainLeft);
            CharToUnicode(tmp, &uniText.pText, &uniText.len);
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_ABOUT),(PWSTR)uniText.pText, ID_OK|SMP_MSGBOXS_AUTOCLOSE,NULL);
            mrc_freeOrigin(uniText.pText, uniText.len);
        }
        break;
    case STR_HELP: //����
        ShowHELP(TOPWND_MAINWND);
        break;
    case STR_EDITPAT: //�ָ�ҳ
        if(NodePat())
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_CANNOTPAT), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITCODE:  //�༭����
        if(FALSE == advFocus)
        {
            //mrc_advStopDraw();//���û����䣬�˵���ʾʱ�����²˵�������
            SGL_TextInput(hWnd);
        }
        break;
    case STR_EDITUP:  //��һҳ
        current--;
        RefText();
        break;
    case STR_EDITDOWN:  //��һҳ
        current++;
        RefText();
        break;
    case STR_EDITJMP:  //ת��ĳҳ
        {
            UnicodeSt uniText;
            char tmp[20];

            mrc_sprintf(tmp,"%d",current);
            CharToUnicode(tmp, &uniText.pText, &uniText.len);
            SMP_InputBox(MAINWND_JMP_INPUTBOX, hWnd, SGL_LoadString(STR_EDITJMP1), (PCWSTR)uniText.pText, 10, ES_NUM, NULL);
            mrc_freeOrigin(uniText.pText, uniText.len);
        }
        break;
    case STR_EDITCOPY: // ���Ʊ�ҳ
        {
            CHAIN *cur=NULL;

            cur = FindNode(current);
	        if(!cur)
	            return;
            else
               writeData(DATA_COPY,cur->txt,514);
        }
        break;
    case STR_EDITAFFIX: // ճ����ҳ
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
    case STR_EDITFADD:	//ǰ����ҳ
        if(Insert1(current))
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_1), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITBADD:	//�����ҳ
        current++;
        if(Insert1(current))
            SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),(PWSTR)SGL_LoadString(STR_1), ID_OK,NULL);
        RefText();
        break;
    case STR_EDITREMOVE: // ɾ����ҳ
        DelNode(current);
        RefText();
        break;
    case STR_SAVE: // ����
        if(!path[0])
            goto saveto;//û��·�������
        else
        {
            if(!SaveCode(path))
		        SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVESUC), ID_OK,NULL);
            else
                SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_SAVEFAI), ID_OK,NULL);
        }
        break;
    case STR_SAVETO:// ���Ϊ 
saveto:
            SMP_InputBox(MAINWND_FNAME_INPUT, hWnd, SGL_LoadString(STR_INPUTNAME), SGL_LoadString(STR_TMPNAME), 128, ES_ALPHA, NULL);
        break;
    case STR_BUILDER:
        SMP_MsgBox(0,hWnd, NULL,SGL_LoadString(STR_MSG),SGL_LoadString(STR_BUILDERERROR), ID_OK,NULL);
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
	case MR_KEY_SOFTRIGHT://���Ҽ�
		return;
    case MR_KEY_0:// ���Ʊ�ҳ
        MenuEvent(hWnd,STR_EDITCOPY);
        return;
    case MR_KEY_1: //��һҳ
        MenuEvent(hWnd,STR_EDITDOWN);
        return;
    case MR_KEY_2:// ת��ĳҳ
        MenuEvent(hWnd,STR_EDITJMP);
        return;
    case MR_KEY_3://ǰ����ҳ
        MenuEvent(hWnd,STR_EDITFADD);
        return;
    case MR_KEY_4: //��һҳ
        MenuEvent(hWnd,STR_EDITUP);
        return;
    case MR_KEY_5://�༭����
    case MR_KEY_SELECT:
        MenuEvent(hWnd,STR_EDITCODE);
        return;
    case MR_KEY_6://�����ҳ
        MenuEvent(hWnd,STR_EDITBADD);
        return;
    case MR_KEY_7:// �ָ�ҳ
        MenuEvent(hWnd,STR_EDITPAT);
        return;
    case MR_KEY_9: //����mpc
        MenuEvent(hWnd,STR_RUN);
        return;
    case MR_KEY_POUND:// ճ����ҳ
        MenuEvent(hWnd,STR_EDITAFFIX);
        return;
    case MR_KEY_STAR:// ɾ����ҳ
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
                mrc_strcpy(path,tt);//���浱ǰ������ļ���
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
            //code����������ɻ������ɵĽ��
//             FPRINTF("advret:%d",code);
        }

    }//swithc(id)
}

static void ShowEvent(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if(_FUNCIS_SET_ANY(FUNC_LOAD))
    {
        if(0 == readCfg(CFG_FIRSTRUN))//��һ��ʹ�ã���ʾ��ӭ
        {
            load_program("c/��ӭ.txt");
            writeCfg(CFG_FIRSTRUN,_VERSION);
        }
        if(tempfile_path !=NULL && mrc_fileState((PSTR)tempfile_path)==MR_IS_FILE)
        {
            _FUNCCLR_STYLE(FUNC_LOAD);
            load_program(tempfile_path);
            //mrc_remove(tempfile_path);
            _SET_USERDATA(hWnd,0);
        }
    }
    if(SMP_DIALOG_ID==MAINWND_DLG_OPEN)
    {
        if(_USERDATA(hWnd) == DIALOG_GET)
        {
            if(load_program(SMP_DIALOG_PATH))
            {
                SMP_MsgBox(0, hWnd, NULL, 
                    SGL_LoadString(STR_MSG), SGL_LoadString(STR_LOADERROR), ID_OK, NULL); 
                return;
            }
            mrc_strcpy(path, SMP_DIALOG_PATH);
            _SET_USERDATA(hWnd,0);
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
        advFocus = chain_len = 0;//chain_len��Ϊ��������һ������Ӧ��0������1
	    current = 1;
        chain_head = NULL;
        Insert1(current);//�����һ������
        _FUNCSET_STYLE(FUNC_LOAD);

        //������XL
 		hTitlebar = SGL_CreateWindow(SMP_Titlebar_WndProc,
 			0, 0, SCREEN_WIDTH, SMP_ITEM_HEIGHT,
 			MAINWND_TITLEBAR, 
 			SMP_TITLEBAR_STATIC, 0);
 		_FGCOLOR(hTitlebar) =  COLOR_lightwhite ;/* ����������ɫ */
 		SMP_Titlebar_SetContent(hTitlebar, RESID_INVALID, SGL_LoadString(STR_TITLE),FALSE);
 		SGL_AddChildWindow(hWnd, hTitlebar);


        //�ı���
        hText = SGL_CreateWindow(SMP_TextInfo_WndProc,
            0,SMP_ITEM_HEIGHT,SCREEN_WIDTH,SCREEN_HEIGHT - SMP_ITEM_HEIGHT-SMP_ITEM_HEIGHT,
            MAINWND_TEXTINFO,WS_TABSTOP,0);
        _BGCOLOR(hText) = 0x444444;
        _FGCOLOR(hText) = 0x00f000;
        SMP_TextInfo_SetContent(hText,(PWSTR)chain_head->txt);
		SGL_AddChildWindow(hWnd, hText);

		//����������
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
        //mrc_advStopDraw();//���û����䣬�˵���ʾʱ�����²˵�������
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
        RefText();
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

        tmp = FindNode(current);

        wstrncpy((PWSTR)tmp->txt, pContent,512);
        RefText();
        return 0;
	}

	}
	return SMP_MenuWnd_WndProc(SGL_FindChildWindow(hWnd,MAINWND_TOOLBAR),hWnd, Msg, wParam, lParam);
}

