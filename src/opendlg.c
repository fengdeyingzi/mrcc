#include "opendlg.h"
#include "topwnd.h"
#include "mainwnd.h"
#include "smp.h"
#include "smp_menu.h"
#include "smp_toolbar.h"
#include "smp_titlebar.h"
#include "smp_menuwnd.h"
#include "smp_msgbox.h"
#include "bmp.h"
#include "smp_list.h"
#include "mr_string.h"
#include "i18n.h"
#include "smp_inputbox.h"
// #include "smp_advbar.h"
#include "application.h"


#define MAX_FILEN         1000
#define FILEN             MAX_FILEN * sizeof(PFILEST) //�����ʾ����1000��

//�������ϵ��Ӵ���ID�б�
enum
{
	DLGWND_TOOLBAR = 1,        //������
	DLGWND_OPTMENU,	    //���˵�
	DLGWND_LIST,
    DLGWND_INPUTBOX,
    DLGWND_REMOVEMSG,
    DLGWND_MSGCOPYSAME,
    DLGWND_MSGCUTSAME,
    DLGWND_INPUTRENAME
};

/* �ļ���Ϣ�ṹ�� �汾2(ָ����) */
typedef struct FileSt
{
	char* name;
	uint8 type;
	struct FileSt *next;
}FILEST, *PFILEST;

typedef enum DIALOGSTATE{
    DIALOGSTATE_NOP,
    DIALOGSTATE_CUT,
    DIALOGSTATE_COPY
}DIALOGSTATE;

char SMP_DIALOG_CUR_PATH[128];   //��ǰ����·��
char SMP_DIALOG_PATH[256];  //��������һ���ļ�������·��
char SMP_DIALOG_TEMP_PATH[256]; //��ʱʹ��
char SMP_DIALOG_TEMP[128];//·������ʱʹ��
static int16 filenum;
static int16 dirnum;
static int16 count;//�б�����
static int16 Index;
static SMP_DIALOG_TYPE DialogType;     //Ҫ��ʾ������
static DIALOGSTATE state;//����״̬
//����
static PFILEST *file;  //�ļ�
static PFILEST pFolder_head, pFolder_temp;   //�ļ�������
static PFILEST pFile_head, pFile_temp;       //�ļ�����
HWND hList;//�б��ھ��
uint8 SMP_DIALOG_ID;

static const DWORD miOptions[] = 
{
    STR_SELECT,     //0ѡ��
    STR_OPENDIR,    //1���ļ���
    STR_NEWDIR,		//2�½��ļ���
    STR_COPYFILE,   //3�����ļ�
    STR_RENAME,     //4������
    STR_CUT,        //5����
    STR_PASTE,      //6ճ��
    STR_REMOVE,     //7ɾ��
    STR_RETURN	    //8����	
};

static VOID ShowOptMenu(HWND hWnd)
{
    Index = SMP_List_GetHilightIndex(hList);

	SMP_Menu_ClearMenuItems();
	SMP_Menu_SetMenuItem2(0, miOptions, TABLESIZE(miOptions));
    if(!file[0])//��������ļ���ʱ
    {
        SMP_Menu_DisableMenuItem(0,1);      //0ѡ��
        SMP_Menu_DisableMenuItem(1,1);      //1���ļ���
//         SMP_Menu_DisableMenuItem(2,1);   //2�½��ļ���
        SMP_Menu_DisableMenuItem(3,1);      //3�����ļ�
        SMP_Menu_DisableMenuItem(4,1);      //4������
        SMP_Menu_DisableMenuItem(5,1);      //5����
//         SMP_Menu_DisableMenuItem(6,1);   //6ճ��
        SMP_Menu_DisableMenuItem(7,1);      //7ɾ��
    }                                       
    else if(DialogType == DIALOG_SELECTDIR || file[Index]->type==MR_IS_DIR)
        SMP_Menu_DisableMenuItem(3,1);//ͣ�����ļ�����
    else
        SMP_Menu_DisableMenuItem(1,1);//ͣ�����ļ���
	SMP_Menu_Popup(DLGWND_OPTMENU, SMP_MENUS_BOTTOMLEFT, hWnd, 0, _HEIGHT(hWnd) - SMP_ITEM_HEIGHT, NULL);
}

void ShowOpenDlg(uint8 Id, WID wndid, SMP_DIALOG_TYPE type)
{
    SMP_DIALOG_ID=Id;
	DialogType = type;
	HideTopWindow(wndid, 0, 0);
	ShowTopWindow(TOPWND_OPENDLG, NULL, (DWORD)wndid);
}

static void MakeDialogPath(void)
{
    if(!file) return;
    mrc_strcpy(SMP_DIALOG_PATH, SMP_DIALOG_CUR_PATH);
    mrc_strcat(SMP_DIALOG_PATH, file[Index]->name);
}
static void HideOpenDlg(HWND hWnd)
{
    MakeDialogPath();
	HideTopWindow(TOPWND_OPENDLG, FALSE, FALSE);
	ShowTopWindow((WID)_USERDATA(hWnd), NULL, DIALOG_GET);
}

static void InitSearch(void)//4.�ͷ��ϴε��ļ��ṹ�ռ䲢��ʼ����������
{
	int i;

	for(i=0; i<count; i++)
	{
		if(file[i])
		{
			if(file[i]->name)
				mrc_free(file[i]->name);
			mrc_free(file[i]);
		}
	}
    mrc_memset(file,0,FILEN);
	pFile_head = pFile_temp = NULL;
	pFolder_head = pFolder_temp = NULL;
	dirnum = filenum = count = Index = 0;
}

static int32 NewFileStruct(PSTR name, int32 type)
{
	int32 name_len;
	PFILEST temp;
	PSTR temp2;

	temp = (PFILEST)mrc_malloc(sizeof(FILEST));
	if(!temp) return -1;
	mrc_memset(temp, 0, sizeof(FILEST));
	name_len = mrc_strlen(name);
	if(name_len<16)
        name_len = 16;
    else
        name_len += 1;
	temp2 = (PSTR)mrc_malloc(name_len);
	if(!temp2)
	{
		mrc_free(temp);
		return -1;
	}
	mrc_strcpy(temp2, name);
	temp->name = temp2;

	//�����ۼ�
	count++;   //�б�����
	if(type == MR_IS_FILE)
		filenum++;
	else
		dirnum++;
	if(type == MR_IS_FILE)
	{
		if(filenum == 1)
			pFile_temp = pFile_head = temp;
		else
		{
			pFile_temp->next = temp;
			pFile_temp = temp;
		}
	}
	else
	{
		if(dirnum == 1)
			pFolder_temp = pFolder_head = temp;
		else
		{
			pFolder_temp->next = temp;
			pFolder_temp = temp;
		}
	}
	temp->type = (uint8)type;
	return MR_SUCCESS;
}

static void StartSearchDir(void)//����ָ��Ŀ¼
{
	uint32 len;
	char path[150] = {0};
	char name_get[100] = {0};  
	int32 handel, ret, type;

	len = sizeof(name_get);                     //�ļ������峤��
	InitSearch();//1.��ʼ��
	handel = mrc_findStart(SMP_DIALOG_CUR_PATH, name_get, len);   //�������·��������һ���Ͳ���ʧ��.
	if(handel > 0)               
	{
		ret ^= ret;//��������ʹѭ�����Խ���
		while(!ret && count < MAX_FILEN)
		{
			mrc_strcpy(path, SMP_DIALOG_CUR_PATH); //�ϳ�·��
			mrc_strcat(path, name_get);
            type = mrc_fileState(path);

			//���fileNameΪ"."������Ч�ļ��������������
			if(name_get[0] != '.' && type != MR_IS_INVALID) 
			{

				if(DialogType == DIALOG_SELECTDIR)//ѡ���ļ���
					if(type == MR_IS_FILE)
						goto next;
				if(MR_FAILED == NewFileStruct(name_get, type))
					goto end;
			}
next:
			ret = mrc_findGetNext(handel, name_get, len);
		}
end:
        mrc_findStop(handel);

        //5.�ļ���������б�(����������������,ֻ�ǽ��ļ��з���ǰ��,�ļ����ں���)
        type ^= type;
        pFolder_temp = pFolder_head;
        for(ret^=ret; ret<dirnum; ++ret)
        {
            file[type++] = pFolder_temp;
            if(!mrc_strcmp(SMP_DIALOG_TEMP,pFolder_temp->name))
                Index = (int16)type-1;
            pFolder_temp = pFolder_temp->next;
        }
        pFile_temp = pFile_head;
        for(ret^=ret; ret<filenum; ++ret)
        {
            file[type++] = pFile_temp;
            pFile_temp = pFile_temp->next;
        }
	}
}

static void RefList(void)//���������������б�
{
    StartSearchDir();
    SMP_List_Refresh(hList);
    SGL_UpdateWindow(hList);
}
static void FileList_Return(HWND hWnd)//�����ϼ�,hWnd:�ļ��б��ھ��
{
	PSTR position;

	position = mrc_strrchr((PCSTR)SMP_DIALOG_CUR_PATH ,'/');
	if(position != NULL)       //������ҳɹ�˵�����Ǹ�Ŀ¼
	{
		int len;
        char buf[128]={0};

		len = position - SMP_DIALOG_CUR_PATH;
		mrc_strncpy(buf ,(PSTR)SMP_DIALOG_CUR_PATH, len);//��Դ�ַ������� n ���ַ�����Ŀ���ַ���
		position = mrc_strrchr((PCSTR)buf, '/');
		if(position)   //������ҳɹ�˵���ǵ�һ����Ŀ¼
		{
			mrc_memset(SMP_DIALOG_CUR_PATH, 0, sizeof(SMP_DIALOG_CUR_PATH));
			len = position - buf + 1;//�����1
			mrc_strncpy(SMP_DIALOG_CUR_PATH, (PSTR)buf, len);
            mrc_strcpy(SMP_DIALOG_TEMP,position+1);
		}else    //Ϊһ����Ŀ¼���൱�ڷ�����ҳ
        {
            mrc_strcpy(SMP_DIALOG_TEMP,buf);
            SMP_DIALOG_CUR_PATH[0]='\0';
        }
        StartSearchDir();
        SMP_List_Refresh(hList);
        SMP_List_HilightByIndex(hList,Index);
	}
}
static int GetFileNumber(void)//1.��ȡ�б���Ŀ�Ļص�����
{
	return (int)count;
}

static void AddFileToList(int index, PSMPROWDATA pRowData)//2.���б�������ݵĻص�����
{
	int w, h;

	if (!pRowData || index < 0) //�����������
		return;

	//�ж����ͣ��ļ�/�ļ��У�
	switch(file[index]->type)
	{
	case MR_IS_FILE:
		pRowData->hBmp = SGL_LoadBitmap(BMP_FILE, &w, &h);
		break;
	case MR_IS_DIR:
		pRowData->hBmp = SGL_LoadBitmap(BMP_FOLDER, &w, &h);
		break;
    default:
        return;
	}

	pRowData->margin = 4;              //�б�����
	pRowData->colWidth0 = (uint16)w;   //ͼ����
	pRowData->colHeight0 = (uint16)h;  //ͼ��߶�
	pRowData->cols[0].width = SCREEN_WIDTH - 4 - w - 20;  //�б���
	pRowData->cols[0].str = (PCWSTR)file[index]->name;      //�ļ���
}


static void OpenDir(HWND hWnd)
{
    HWND hMsgBox = SMP_MsgBox(0, hWnd, NULL, SGL_LoadString(STR_MSG),
        SGL_LoadString(STR_STARTFIND), ID_NON, NULL);
    MR_STRCAT(SMP_DIALOG_CUR_PATH, file[Index]->name);
    MR_STRCAT(SMP_DIALOG_CUR_PATH, "/");
    StartSearchDir();
    SMP_List_Refresh(hList);
    SMP_Close_MsgBox(hMsgBox);
}
static void MenuEvent(HWND hWnd, WORD code)
{
    Index = SMP_List_GetHilightIndex(hList);

    switch(code)
    {
    case STR_SELECT: 
        if(DialogType == DIALOG_SELECTDIR)//ѡ���ļ���
        	HideOpenDlg(hWnd);
        else if(file[Index]->type == MR_IS_FILE)
        	HideOpenDlg(hWnd);
        return;
    case STR_OPENDIR:
        OpenDir(hWnd);
        return;
    case STR_NEWDIR:
        SMP_InputBox(DLGWND_INPUTBOX,hWnd,SGL_LoadString(STR_NEWDIR),SGL_LoadString(STR_NEWDIR),128,ES_ALPHA,NULL);
        return;
    case STR_RENAME://������
        {
            PSTR position;
            UnicodeSt uniText;

            MakeDialogPath();
            position = mrc_strrchr((PCSTR)SMP_DIALOG_PATH ,'/');
            if(!position) position=SMP_DIALOG_PATH;
            else position++;
            strcpy(SMP_DIALOG_TEMP_PATH,position);
            CharToUnicode(SMP_DIALOG_TEMP_PATH, &uniText.pText, &uniText.len);
            SMP_InputBox(DLGWND_INPUTRENAME,hWnd,SGL_LoadString(STR_RENAME),(PWSTR)uniText.pText,128,ES_ALPHA,NULL);
            mrc_freeOrigin(uniText.pText, uniText.len);
        }
        return;
    case STR_CUT:
        MakeDialogPath();
        state=DIALOGSTATE_CUT;
        return;
    case STR_COPYFILE:
        MakeDialogPath();
        state=DIALOGSTATE_COPY;
        return;
    case STR_PASTE://ճ��
        {
            PSTR position;

            if(state==DIALOGSTATE_NOP) break;
            if(mrc_fileState(SMP_DIALOG_PATH) == MR_IS_INVALID) break;
            position = mrc_strrchr((PCSTR)SMP_DIALOG_PATH ,'/');
            if(!position) position=SMP_DIALOG_PATH;
            else position++;
            strcpy(SMP_DIALOG_TEMP_PATH,SMP_DIALOG_CUR_PATH);
            strcat(SMP_DIALOG_TEMP_PATH,position);
            if(!mrc_strcmp(SMP_DIALOG_TEMP_PATH,SMP_DIALOG_PATH)) //·����ͬ��������
                break;
            if(state == DIALOGSTATE_COPY)//����
            {
                if(mrc_fileState(SMP_DIALOG_TEMP_PATH) != MR_IS_INVALID)
                    SMP_MsgBox(DLGWND_MSGCOPYSAME, hWnd, NULL, SGL_LoadString(STR_MSG), SGL_LoadString(STR_WARNING1), ID_OK|ID_CANCEL|ID_YESNO , NULL);
                else
                {
                    CopyFile(SMP_DIALOG_TEMP_PATH,SMP_DIALOG_PATH);
                    RefList();
                }
            }
            else//����
            {
                if(mrc_fileState(SMP_DIALOG_TEMP_PATH) != MR_IS_INVALID)
                    SMP_MsgBox(DLGWND_MSGCUTSAME, hWnd, NULL, SGL_LoadString(STR_MSG), SGL_LoadString(STR_WARNING1), ID_OK|ID_CANCEL|ID_YESNO , NULL);
                else
                {
                    mrc_rename(SMP_DIALOG_PATH,SMP_DIALOG_TEMP_PATH);
                    state=DIALOGSTATE_NOP;
                    RefList();
                }
            }
        }
        return;
    case STR_REMOVE:
        SMP_MsgBox(DLGWND_REMOVEMSG, hWnd, NULL, SGL_LoadString(STR_MSG), SGL_LoadString(STR_REALREMOVE), ID_OK|ID_CANCEL|ID_YESNO , NULL);
        return;
    case STR_RETURN:
        HideTopWindow(TOPWND_OPENDLG, 0, 0);
        ShowTopWindow((WID)_USERDATA(hWnd), NULL, 0); 
        return;
    }
}

LRESULT OpenDlg_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_CREATE:    //���Դ�������Ϣ���Ӵ˴����������ؼ�
	{   
        HWND hControl;
		//����������
		hControl = SGL_CreateWindow(SMP_Titlebar_WndProc,
			0, 0, SCREEN_WIDTH, SMP_ITEM_HEIGHT,
			0, SMP_TITLEBAR_STATIC,0);
		SMP_Titlebar_SetContent(hControl, RESID_INVALID, SGL_LoadString(STR_SELECT), FALSE);
		_FGCOLOR(hControl)=COLOR_lightwhite;
		SGL_AddChildWindow(hWnd, hControl);

		//����list
		hList = SGL_CreateWindow(SMP_List_WndProc,
			0, SMP_ITEM_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - 2*SMP_ITEM_HEIGHT,
			DLGWND_LIST, 0, 0);
		SMP_List_SetDataProvider(hList, GetFileNumber, AddFileToList);
		SGL_AddChildWindow(hWnd, hList);

		//����������
		hControl = SGL_CreateWindow(
			SMP_Toolbar_WndProc, 
			0, SCREEN_HEIGHT - SMP_ITEM_HEIGHT, 
			SCREEN_WIDTH,SMP_ITEM_HEIGHT,
			DLGWND_TOOLBAR, 0, 0);
		SMP_Toolbar_SetStrings(hControl, STR_MENU, RESID_INVALID, STR_BACK, FALSE);
		SGL_AddChildWindow(hWnd, hControl);
        file = NULL;
        SMP_DIALOG_TEMP[0]=0;
        //�������ó�ʼĿ¼
        mrc_strcpy(SMP_DIALOG_CUR_PATH,cdir);
        break;  
    }
    case WM_PAINT:
//         mrc_advStopDraw();
        break;
	case WM_SHOW:
	{
		if(!file)
		{
			file = mrc_malloc(FILEN);
            if(!file)
            {
				HideTopWindow(TOPWND_OPENDLG, 0, 0);
				ShowTopWindow((WID)_USERDATA(hWnd), NULL, 0); 
                return -1;
            }
            count = 0;//!
            mrc_memset(file,0,FILEN);//!
			StartSearchDir();
		}
        state=DIALOGSTATE_NOP;
		break;
	}
	case WM_HIDE:
	{
		if(file)
		{	
			InitSearch();
			free(file);
		}
		file=NULL;
		break;
	}
	case WM_INITFOCUS:  
	{
		SGL_SetFocusWindow(hWnd, hList);
		break;
	}	
	case WM_KEYUP:  
	{
		switch(wParam)
		{
		case MR_KEY_SOFTLEFT: 
			ShowOptMenu(hWnd);
			return 1;
		case MR_KEY_SOFTRIGHT:  //����
			if(!SMP_DIALOG_CUR_PATH[0])
			{
				HideTopWindow(TOPWND_OPENDLG, 0, 0);
				ShowTopWindow((WID)_USERDATA(hWnd), NULL, 0); 
			}else
				FileList_Return(hWnd);
			return 1;
		}
		break;
	}
	case WM_COMMAND:   
	{
		WID id = LOWORD(wParam);  
		WORD code = HIWORD(wParam);  

		switch(id)    
		{
		case DLGWND_LIST:
			{
				switch(code)
				{
				case SMP_LISTN_SELECTED:
				case SMP_LISTN_CLICKED:
					{
						Index = (int16)lParam;
                        if(!file[0])//û���ļ�
                            break;
						else if(file[Index]->type == MR_IS_FILE)//ѡ���ļ�  
							HideOpenDlg(hWnd);
						else if(DialogType == DIALOG_SELECTDIR)//ѡ���ļ���
                            HideOpenDlg(hWnd);
                        else//�����ļ���
                            OpenDir(hWnd);

					}
					break;
				}
			}
			break;

		case DLGWND_OPTMENU:
            MenuEvent(hWnd, code);
			break;

        case DLGWND_REMOVEMSG:
            if(code == ID_OK)
            {
                MakeDialogPath();
                if(file[Index]->type == MR_IS_FILE)
                    mrc_remove(SMP_DIALOG_PATH);
                else
                    removeDir(SMP_DIALOG_PATH);
                RefList();
            }
            break;

        case DLGWND_INPUTBOX: //����Ŀ¼
            if(code == INPUT_OK)
            {
                PSTR tt=NULL;

                tt = UnicodeToChar((PCWSTR)lParam);
                mrc_strcpy(SMP_DIALOG_PATH,SMP_DIALOG_CUR_PATH);
                mrc_strcat(SMP_DIALOG_PATH,tt);
                SGL_FREE(tt);
                mrc_mkDir(SMP_DIALOG_PATH);
                RefList();
            }
            break;

        case DLGWND_MSGCUTSAME:
            if(code == ID_OK)
            {
                removeDir(SMP_DIALOG_TEMP_PATH);
                mrc_rename(SMP_DIALOG_PATH,SMP_DIALOG_TEMP_PATH);
                state=DIALOGSTATE_NOP;
                RefList();
            }
            break;

        case DLGWND_MSGCOPYSAME: //ճ��
            if(code == ID_OK)
            {//����Ҫ��ɾ��
                CopyFile(SMP_DIALOG_TEMP_PATH,SMP_DIALOG_PATH);
                RefList();
            }
            break;

        case DLGWND_INPUTRENAME: //������
            if(code == INPUT_OK)
            {
                PSTR tt=NULL;
                
                tt = UnicodeToChar((PCWSTR)lParam);
                mrc_strcpy(SMP_DIALOG_TEMP_PATH,SMP_DIALOG_CUR_PATH);
                mrc_strcat(SMP_DIALOG_TEMP_PATH,tt);
                mrc_free(file[Index]->name);
                file[Index]->name = tt;//���õ�ǰ�ļ�(��)������,tt����Ҫ�ͷ�
                mrc_rename(SMP_DIALOG_PATH,SMP_DIALOG_TEMP_PATH);
                SGL_UpdateWindow(hList);
            }
            break;

		}//switch(id) �Ľ�������
		break;
	}//WM_COMMAND  ��������
	}
	return SMP_MenuWnd_WndProc(SGL_FindChildWindow(hWnd,DLGWND_TOOLBAR),hWnd, Msg, wParam, lParam);
}

