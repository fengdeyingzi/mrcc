#include "smp_label.h"
#include "mr_string.h"
#include "smp.h"
#include "bmp.h"

//��ǩ����
typedef struct SMP_LabelData
{
	DWORD bmp;		//λͼID
	PCWSTR str;		//�ַ�������
	int32 timer;	//��ʱ���Զ�����
	Uint32 interval;//�Զ�������ʱ����
	Sint32 cur;		//��ǰ�����Զ�����
	int32 len;		//�ַ�������(�ֽ�)
	int32 width;	//�ַ����ܿ��
	int32 height;	//���ݸ߶�
	BOOL playing;	//��ǰ�Զ�����״̬
}LABELDATA, *PLABELDATA;


//////////////////////////////////////////////////////////////////////////////////////

static VOID SMP_Label_Scroll(int32 data)
{
	HWND hWnd = (HWND)data;
	PLABELDATA pData = _GET_WINDATA(hWnd, PLABELDATA);

	pData->cur += 2;
	if(pData->cur >= pData->len)
		pData->cur = 0;

	SGL_UpdateWindow(hWnd);
}


VOID SMP_Label_SetContent(HWND hWnd, DWORD bmpID, PCWSTR content, Uint32 interval)
{
	PLABELDATA pData = _GET_WINDATA(hWnd, PLABELDATA);

	SMP_Label_StopAutoScroll(hWnd);	

	pData->str = content;
	pData->interval = interval;
	pData->cur = 0;
	pData->bmp = bmpID;
	
    if(enable_smallfont)
        skyfontWidthHeight((PSTR)pData->str,&pData->width, &pData->height);
    else
	    mrc_textWidthHeight((PSTR)pData->str, TRUE, (uint16)SGL_GetSystemFont(), &pData->width, &pData->height);
	pData->len = mrc_wstrlen((PSTR)pData->str);
}


VOID SMP_Label_StartAutoScroll(HWND hWnd)
{
	PLABELDATA pData;

    if(!hWnd)
	    return;

	pData = _GET_WINDATA(hWnd, PLABELDATA);

	if(pData->playing || !_IS_SET_ANY(hWnd, SMP_LABELS_AUTOSCROLL)) 
		return;

	pData->playing = TRUE;
	if(pData->width >= _WIDTH(hWnd))
	{
		if(!pData->timer)
			pData->timer = mrc_timerCreate();
		
		mrc_timerStart(pData->timer, pData->interval, (int32)hWnd, SMP_Label_Scroll, TRUE);
	}
}


VOID SMP_Label_StopAutoScroll(HWND hWnd)
{
    PLABELDATA pData;

    if(!hWnd)
        return;

	pData = _GET_WINDATA(hWnd, PLABELDATA);

	if(!pData->playing) 
		return;
	
	pData->playing = FALSE;
	if(pData->timer)
		mrc_timerStop(pData->timer);
}


LRESULT SMP_Label_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	PLABELDATA pData = _GET_WINDATA(hWnd, PLABELDATA);
	
	switch(Msg)
	{
	
	case WM_CREATE:
	{
		pData = (PLABELDATA)SGL_MALLOC(sizeof(LABELDATA));
		if(NULL == pData){
			//SGL_TRACE("%s, %d: memory out\n", __FILE__, __LINE__);
			return 1;
		}
		
		SGL_MEMSET(pData, 0, sizeof(LABELDATA));
		_SET_WINDATA(hWnd, pData);
		break;
	}

	case WM_DESTROY:
	{
		if(pData)
		{
			if(pData->timer)
				mrc_timerDelete(pData->timer);
			
			SGL_FREE(pData);
		}
		break;
	}

	case WM_SHOW:
	{
		SMP_Label_StartAutoScroll(hWnd);
		break;
	}

	case WM_HIDE:
	{
		SMP_Label_StopAutoScroll(hWnd);
		break;
	}

	case WM_PAINT:
	{
		int x=0, y=0, mid;
		mr_colourSt color = {0,};
		mr_screenRectSt rect;
		HFONT font = SGL_GetSystemFont();
		PCWSTR pContent = pData->str + pData->cur;

		color.r = PIXEL888RED(_FGCOLOR(hWnd));
		color.g = PIXEL888GREEN(_FGCOLOR(hWnd));
		color.b = PIXEL888BLUE(_FGCOLOR(hWnd));

		SGL_WindowToScreen(hWnd, &x, &y);
		rect.x = (uint16)(x + SMP_ITEM_CONTENT_MARGIN); rect.y = (uint16)y;
		rect.w = (uint16)(_WIDTH(hWnd) - 2*SMP_ITEM_CONTENT_MARGIN); rect.h = (uint16)_HEIGHT(hWnd);

        if(_IS_SET_ANY(hWnd, SMP_LABELS_AUTOSCROLL))//����ϴι����ı���
        {
            GAL_FillBox(x, y, _WIDTH(hWnd), _HEIGHT(hWnd), COLOR_controlbg);
        }
        
		if(_IS_SET_ANY(hWnd, WS_FOCUSED))//�������
			GAL_Rectangle(x, y, _WIDTH(hWnd), _HEIGHT(hWnd), COLOR_focus);

		if(RESID_INVALID != pData->bmp)
		{
			int w, h;
			HBITMAP bmp = SGL_LoadBitmap(pData->bmp, &w, &h);
			if(bmp)
			{
				mrc_bitmapShowEx((uint16 *)bmp, (int16)rect.x, (int16)(y + DIV(_HEIGHT(hWnd)-h, 2)), (int16)w, (int16)w, (int16)h, BM_TRANSPARENT, 0, 0);
				x += w + SMP_ITEM_CONTENT_MARGIN;
				rect.w -= w + SMP_ITEM_CONTENT_MARGIN;
			}
		}

		x += SMP_ITEM_CONTENT_MARGIN;
		rect.x = (int16)x;
		mid = DIV(_HEIGHT(hWnd)-pData->height, 2);
		if(_IS_SET_ANY(hWnd, SMP_LABELS_HCENTER) && pData->width < rect.w)//˵����ǩ�����������Ķ���
			mrc_drawTextEx((PSTR)pContent, (int16)(x + DIV(rect.w - pData->width, 2)), (int16)(y + mid), rect, color, 1, (uint16)font);
		else
			mrc_drawTextEx((PSTR)pContent, (int16)x, (int16)(y + mid), rect, color, 1, (uint16)font);

		if(_IS_SET_ANY(hWnd, SMP_LABELS_LINK))//������һ������
			GAL_DrawHLine(x, y+mid+pData->height, pData->width > rect.w? rect.w : pData->width, COLOR_blue);
		break;
	}

	case WM_MOUSEUP:
	{
		if(!_IS_SET_ANY(hWnd, SMP_LABELS_STATIC))
			SGL_NotifyParent(hWnd, SMP_LABELN_CLICKED, (DWORD)hWnd);
		break;
	}

	case WM_KEYUP:
	{
		if(wParam == MR_KEY_SELECT && !_IS_SET_ANY(hWnd, SMP_LABELS_STATIC))
		{
			SGL_NotifyParent(hWnd, SMP_LABELN_CLICKED, (DWORD)hWnd);
			return 1;
		}
		break;
	}

	case WM_SETFOCUS:
	case WM_KILLFOCUS:
	{
		SGL_UpdateWindow(hWnd);
		break;
	}	
	
	}

	return 0;
}

