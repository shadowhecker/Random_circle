#pragma once
#include<afxwin.h>
#include <vector>
#include <random>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<math.h>

using namespace std;


class cell_parameter {
public:
	double x;
	double y;
	double radius;
	cell_parameter(double num1, double num2, double num3) { x = num1; y = num2; radius = num3; }
	cell_parameter() {}
};
class CMyApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMyWindow :public CFrameWnd
{
protected:
	CPoint heart;
	int cell_num;//已有孔洞的数目
	double INT_RADIUS;//内圆的半径
	double EX_RADIUS;//外圆半径
	int CELL_NUM;
	vector<cell_parameter> return_parameter;//这是要返回的圆的坐标和半径等参数
	void DrawGrid(CDC *pDC);
	void DrawX(CDC *pDC, cell_parameter cell);//画孔
	void DrawO(CDC *pDC);//画内外圆
	BOOL If_in_radius(CPoint point,double radius);//该点画圆是否落在两个圆中间
	BOOL If_cross(CPoint point, double radius);//判断该圆是否与其他的圆有交集
	cell_parameter random_circle();//随机创建孔洞

	CButton m_wndPushButton_start;
	CButton m_wndPushButton_reset;
public:
	CMyWindow();
protected:
	virtual void PostNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreatestruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPushButtonClicked_Start();
	afx_msg void OnPushButtonClicked_Reset();
	DECLARE_MESSAGE_MAP()
};