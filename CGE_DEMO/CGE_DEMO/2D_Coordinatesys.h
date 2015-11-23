#ifndef COORSYS_2D_H
#define COORSYS_2D_H

#define X_MARGIN	20
#define Y_MARGIN	20

struct COORSYS_2D
{
	SHORT shOP_YinScreen;
	SHORT shOP_XinScreen;
	SHORT shPixelMapRatio;
	SHORT shMouseXPos;
	SHORT shMouseYPos;
	SHORT shX_PlusAxisValue;
	SHORT shX_MinusAxisValue;
	SHORT shY_PlusAxisValue;
	SHORT shY_MinusAxisValue;
	BOOL  bShowGrid;
};

typedef COORSYS_2D* P_2D_COORSYS; //typedef int* pint; 是语句，由编译器在编译过程中编译处理

void	Init_2D_CorSys(HWND hWnd,P_2D_COORSYS p2DCoorSys);
void	UpdateOriginalPoint(HWND hWnd,P_2D_COORSYS p2DCoorSys);


void	SwitchShowGridFlag(P_2D_COORSYS p2DCoorSys);
void	SetMousePosIn2DCorSys(HWND hWnd,P_2D_COORSYS p2DCoorSys,POINT mCurMousePoint);
void	Draw2DCorSys(HWND hWnd,HDC hdc,P_2D_COORSYS p2DCoorSys);


void	UpdateTextRect(HWND hWnd);
void	SwitchGridShow(P_2D_COORSYS p2DCoorSys);

void	IncreaseMapRatio(P_2D_COORSYS p2DCoorSys);
void	DecreaseMapRatio(P_2D_COORSYS p2DCoorSys);


#endif