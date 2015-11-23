# if _MSC_VER > 1000
# pragma once
# endif //

class Berier()
{
public:
	void MyDraw(const POINT& p0,const POINT& p1,const POINT& p2,const POINT& p3);
	double F(double t,int p0,int p1,int p2, int p3);
    void OnMouseMove(UINT nFlags,POINT point);
	void OnLButtonDown(UINT nFlags,POINT point);
	void OnButtonUp(UINT nFlags,POINT point);


}