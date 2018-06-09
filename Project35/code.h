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
	int cell_num;//���п׶�����Ŀ
	double INT_RADIUS;//��Բ�İ뾶
	double EX_RADIUS;//��Բ�뾶
	int CELL_NUM;
	vector<cell_parameter> return_parameter;//����Ҫ���ص�Բ������Ͱ뾶�Ȳ���
	void DrawGrid(CDC *pDC);
	void DrawX(CDC *pDC, cell_parameter cell);//����
	void DrawO(CDC *pDC);//������Բ
	BOOL If_in_radius(CPoint point,double radius);//�õ㻭Բ�Ƿ���������Բ�м�
	BOOL If_cross(CPoint point, double radius);//�жϸ�Բ�Ƿ���������Բ�н���
	cell_parameter random_circle();//��������׶�

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