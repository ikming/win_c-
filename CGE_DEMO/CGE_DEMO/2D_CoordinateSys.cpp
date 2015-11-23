#include "stdafx.h"
#include "2D_Coordinatesys.h"
#include <assert.h>


RECT	mTextRect;

void	Init_2D_CorSys(HWND hWnd,P_2D_COORSYS p2DCoorSys)  //init_2d(); HWND 有窗口句柄意味着什么呢？
                                                          // 我们定义的P_2D_COORSYS 
														  //句柄：是由操作环境定义的一个唯一的整数值，
														  //它被程序用来标识或者切换到对象，如窗体或控件等
{
	RECT	mClientRect;

	if((p2DCoorSys == NULL) || (hWnd == NULL))
		return;

	p2DCoorSys->bShowGrid = FALSE;

	GetClientRect(hWnd,&mClientRect);
	p2DCoorSys->shOP_XinScreen = mClientRect.right / 2;
	p2DCoorSys->shOP_YinScreen = mClientRect.bottom / 2;
	
	p2DCoorSys->shMouseXPos = 0;
	p2DCoorSys->shMouseYPos = 0;
	p2DCoorSys->shPixelMapRatio = 10;

	p2DCoorSys->shX_MinusAxisValue = 40 ;//x轴的负半轴 ，
	p2DCoorSys->shX_PlusAxisValue = 40;   //x轴正半轴
	p2DCoorSys->shY_MinusAxisValue = 40;   //y轴负半轴
	p2DCoorSys->shY_PlusAxisValue = 40;     //y轴正半轴

	mTextRect.top = 5;
	mTextRect.left = 5;
	mTextRect.bottom = mTextRect.top + 20 * 8;
	mTextRect.right = mTextRect.left + 300;
	return;
}

void	UpdateOriginalPoint(HWND hWnd,P_2D_COORSYS p2DCoorSys)
{
	RECT	mClientRect;

	if (p2DCoorSys== NULL || hWnd== NULL)  
	return;

	GetClientRect(hWnd,&mClientRect);
	p2DCoorSys->shOP_XinScreen = mClientRect.right / 2;
	p2DCoorSys->shOP_YinScreen = mClientRect.bottom / 2;

}

void	SwitchShowGridFlag(P_2D_COORSYS p2DCoorSys)
{
	if(p2DCoorSys == NULL)
		return;
	p2DCoorSys->bShowGrid ^= p2DCoorSys->bShowGrid;

	return;
}

void	SetMousePosIn2DCorSys(HWND hWnd,P_2D_COORSYS p2DCoorSys,POINT mCurMousePoint)
{
	//int 
	if((hWnd == NULL) || (p2DCoorSys == NULL))
		return;

	p2DCoorSys->shMouseXPos = (mCurMousePoint.x - p2DCoorSys->shOP_XinScreen) / p2DCoorSys->shPixelMapRatio;
	p2DCoorSys->shMouseYPos = (p2DCoorSys->shOP_YinScreen - mCurMousePoint.y) / p2DCoorSys->shPixelMapRatio;
}

void	Draw2DCorSys(HWND hWnd,HDC hdc,P_2D_COORSYS p2DCoorSys)
{
	HPEN   m_COOR_Pen,mOldPen1,m_Grid_Pen,mOldPen2;
	RECT   mOPAixsRect,mHelpRect;
	HFONT  mTextFont1,mTextFont2,mOldFont;
	int	   iFontSize;
	TCHAR  chHelpString[200];
// 
	if((p2DCoorSys == NULL) || (hWnd == NULL) || (hdc == NULL))
 		return;

	m_COOR_Pen = CreatePen(PS_SOLID,2,RGB(0,0,0));
	mOldPen1 = (HPEN)SelectObject(hdc,m_COOR_Pen);

	//draw X axis
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_MinusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen);

	//draw arrow
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio - 5,
		p2DCoorSys->shOP_YinScreen - 5);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
		p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio - 5,
		p2DCoorSys->shOP_YinScreen + 5);

	//draw Y aixs
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		+ p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
	//draw arrow
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen - 5,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5);
	MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio,NULL);
	LineTo(hdc,p2DCoorSys->shOP_XinScreen + 5,p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5);

	//display "+x"
	iFontSize = 40;
	mTextFont1 = CreateFont(iFontSize,0,0,0,FW_BOLD,
		0/*非斜体*/,0/*不带下划线*/,0,GB2312_CHARSET/*字符集*/,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,(LPCSTR)"Arial");
	mOldFont = (HFONT)SelectObject(hdc,mTextFont1);
	SetTextColor(hdc,RGB(0,0,255));

	mOPAixsRect.left = p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio + 5;
	mOPAixsRect.right = mOPAixsRect.left + 40;
	mOPAixsRect.top = p2DCoorSys->shOP_YinScreen - 20;
	mOPAixsRect.bottom = p2DCoorSys->shOP_YinScreen +20;
	DrawText(hdc,"+x",2,&mOPAixsRect,DT_LEFT | DT_VCENTER);
	//display "+y"
	mOPAixsRect.left = p2DCoorSys->shOP_XinScreen - 20;
	mOPAixsRect.right = mOPAixsRect.left + 40;
	mOPAixsRect.bottom = p2DCoorSys->shOP_YinScreen
		- p2DCoorSys->shY_PlusAxisValue * p2DCoorSys->shPixelMapRatio +30;
	mOPAixsRect.top = mOPAixsRect.bottom - 40;
	DrawText(hdc,"+y",2,&mOPAixsRect,DT_LEFT | DT_VCENTER);

	
	//display help information.
	iFontSize = 15;
	mTextFont2 = CreateFont(iFontSize,0,0,0,FW_BOLD,
		0/*非斜体*/,0/*不带下划线*/,0,GB2312_CHARSET/*字符集*/,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,(LPCSTR)"Arial");
	mOldFont = (HFONT)SelectObject(hdc,mTextFont2);
	SetTextColor(hdc,RGB(255,0,0));


	mHelpRect.left = mTextRect.left;
	mHelpRect.top = mTextRect.top;
	mHelpRect.bottom = mHelpRect.top + 20;
	mHelpRect.right = mHelpRect.left + 300;

	sprintf(chHelpString,"X_OP:%d  Y_OP:%d\0",p2DCoorSys->shOP_XinScreen,p2DCoorSys->shOP_YinScreen);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	mHelpRect.top = mHelpRect.bottom;
	mHelpRect.bottom = mHelpRect.top + 20;
	sprintf(chHelpString,"Pixel Scale Ratio: 1:%d\0",p2DCoorSys->shPixelMapRatio);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	mHelpRect.top = mHelpRect.bottom;
	mHelpRect.bottom = mHelpRect.top + 20;
	sprintf(chHelpString,"Mouse_X:%d  Mouse_Y:%d\0",p2DCoorSys->shMouseXPos,p2DCoorSys->shMouseYPos);
	DrawText(hdc,chHelpString,strlen(chHelpString),&mHelpRect,DT_LEFT|DT_VCENTER);

	//draw grid.
	if(p2DCoorSys->bShowGrid)
	{
		int iTmp;

		m_Grid_Pen = CreatePen(PS_SOLID,1,RGB(255,0,0));
		mOldPen2 = (HPEN)SelectObject(hdc,m_Grid_Pen);
	
		for(iTmp = 1; iTmp <= p2DCoorSys->shX_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shX_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - iTmp * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - p2DCoorSys->shY_MinusAxisValue * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shY_PlusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen - iTmp * p2DCoorSys->shPixelMapRatio);
		}
		for(iTmp = 1; iTmp <= p2DCoorSys->shY_MinusAxisValue; iTmp++)
		{
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen + p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio);
			MoveToEx(hdc,p2DCoorSys->shOP_XinScreen,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio,NULL);
			LineTo(hdc,p2DCoorSys->shOP_XinScreen - p2DCoorSys->shX_PlusAxisValue * p2DCoorSys->shPixelMapRatio,
				p2DCoorSys->shOP_YinScreen + iTmp * p2DCoorSys->shPixelMapRatio);
		}


	}

	SelectObject(hdc,mOldPen1);
	SelectObject(hdc,mOldPen2);
	DeleteObject(m_COOR_Pen);
	DeleteObject(m_Grid_Pen);
	SelectObject(hdc,mOldFont);
	DeleteObject(mOldFont);
	return;
}

void	UpdateTextRect(HWND hWnd)
{
	if(hWnd == NULL)
		return;
	InvalidateRect(hWnd,&mTextRect,TRUE);
	UpdateWindow(hWnd);
}

void	SwitchGridShow(P_2D_COORSYS p2DCoorSys)
{
	if(p2DCoorSys != NULL)
		p2DCoorSys->bShowGrid ^= TRUE;

}

void	IncreaseMapRatio(P_2D_COORSYS p2DCoorSys)
{
	if(p2DCoorSys != NULL)
	{
		if(p2DCoorSys->shPixelMapRatio < 50)
			p2DCoorSys->shPixelMapRatio += 10;
	}
}
void	DecreaseMapRatio(P_2D_COORSYS p2DCoorSys)
{
	if(p2DCoorSys != NULL)
	{
		if(p2DCoorSys->shPixelMapRatio > 10)
			p2DCoorSys->shPixelMapRatio -= 10;
	}
}