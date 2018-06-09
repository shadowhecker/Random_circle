#include "code.h"
#include "OptionalDialog.h"
CMyApp myApp;

#define IDC_START 100
#define IDC_RESET 101
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMyWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_START, OnPushButtonClicked_Start)
    ON_BN_CLICKED(IDC_RESET, OnPushButtonClicked_Reset)
END_MESSAGE_MAP()

CMyWindow::CMyWindow()
{
	HWND hwnd = ::GetDesktopWindow();
	CRect rect;
	::GetWindowRect(hwnd,&rect);
	Create(NULL, _T("CELL"),WS_OVERLAPPEDWINDOW| WS_HSCROLL| WS_VSCROLL, rect);
}

int CMyWindow::OnCreate(LPCREATESTRUCT lpCreatestruct)
{
	if (CFrameWnd::OnCreate(lpCreatestruct) == -1)
		return -1;
	CClientDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	heart.x = (rect.right-rect.left)/2;
	heart.y = (rect.bottom-rect.top)/2;//获得窗口中心坐标
	CRect rect1(100, 100, 300, 150);
	m_wndPushButton_start.Create(_T("Start"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect1, this, IDC_START);
	rect1.SetRect(100, 250, 300, 300);
	m_wndPushButton_reset.Create(_T("Reset"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect1, this, IDC_RESET);
	return 0;
}

void CMyWindow::OnSize(UINT nType, int cx, int cy)
{
	CClientDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	heart.x = (rect.right - rect.left)/2;
	heart.y = (rect.bottom - rect.top)/2;//获得窗口中心坐标
	InvalidateRect(&rect);
}

void CMyWindow::OnPushButtonClicked_Start()
{
	CDC *pDC = GetDC();
	COptionalDialog CMyDialog;
	if (CMyDialog.DoModal() == IDOK)
	{
		EX_RADIUS = CMyDialog.m_str_EX_RADIUS;
		INT_RADIUS = CMyDialog.m_str_INT_RADIUS;
		CELL_NUM = CMyDialog.m_CELL_NUM;
	}
	HCURSOR cursor = LoadCursor(NULL, IDC_WAIT);
	::SetCursor(cursor);
	DrawO(pDC);
	DrawGrid(pDC);
	cursor = LoadCursor(NULL, IDC_ARROW);
	::SetCursor(cursor);
	ReleaseDC(pDC);
}

void CMyWindow::OnPushButtonClicked_Reset()
{
	cell_num = 0;
	return_parameter.clear();
	EX_RADIUS = 0;
	INT_RADIUS = 0;
	CELL_NUM = 0;
	CClientDC *pDC;
	CRect rect;
	GetClientRect(rect);
	InvalidateRect(rect);
}

void CMyWindow::OnPaint()
{
	CPaintDC dc(this);
	DrawO(&dc);
}

void CMyWindow::PostNcDestroy()
{
	delete this;
}

void CMyWindow::DrawGrid(CDC * pDC)
{
	for (int i = 0; i < CELL_NUM; ++i)
	{
		cell_parameter cell;
		while (1)
		{
			cell = random_circle();
			CPoint point(cell.x, cell.y);
			if (If_in_radius(point, cell.radius) && If_cross(point, cell.radius))
				break;
		}
		return_parameter.push_back(cell);
		++cell_num;
		DrawX(pDC, return_parameter[i]);
		CString str;
		str.Format(_T("%d、x=%.4f ,y=%.4f ,radius=%.4f"), i+1,return_parameter[i].x-heart.x, return_parameter[i].y-heart.y, return_parameter[i].radius);
		CRect rect(heart.x + EX_RADIUS , 0 + i*20, heart.x * 2,  i*20 + 20);
		pDC->DrawText(str, rect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	}
}

void CMyWindow::DrawX(CDC * pDC, cell_parameter cell)
{
	CBrush brush(RGB(255, 0, 0));
	CBrush *oldbrush = pDC->SelectObject(&brush);
	pDC->Ellipse(cell.x - cell.radius, cell.y - cell.radius, cell.x+ cell.radius, cell.y+cell.radius);
	pDC->SelectObject(oldbrush);
}

void CMyWindow::DrawO(CDC * pDC)
{
	pDC->Ellipse(heart.x - EX_RADIUS, heart.y - EX_RADIUS, heart.x + EX_RADIUS, heart.y + EX_RADIUS);
	pDC->Ellipse(heart.x - INT_RADIUS, heart.y - INT_RADIUS, heart.x + INT_RADIUS, heart.y + INT_RADIUS);
}

BOOL CMyWindow::If_in_radius(CPoint point, double radius)
{
	double length = sqrt(pow(point.x - heart.x, 2) + pow(point.y - heart.y, 2));
	double length_1 = length + radius;
	double length_2 = length - radius;
	if (length_1<EX_RADIUS&&length_2>INT_RADIUS)
		return true;
	return FALSE;
}

BOOL CMyWindow::If_cross(CPoint point, double radius)
{
	if (cell_num == 0)
		return true;//表示没有交集
	else
	{
		for (int i = 0; i < return_parameter.size(); ++i)
		{
			double length = sqrt(pow(point.x - return_parameter[i].x, 2) + pow(point.y - return_parameter[i].y, 2));
			if (length < radius+ return_parameter[i].radius)
				return FALSE;
		}
		return true;
	}
}

cell_parameter CMyWindow::random_circle()
{
	std::default_random_engine e(time(0));
	std::uniform_real_distribution<double> r(INT_RADIUS, EX_RADIUS);
	double length = r(e);
	std::uniform_real_distribution<double> alpha(0, 2*3.1415926);
	double al = alpha(e);
	double x = cos(al)*length;
	double y = sin(al)*length;
	std::uniform_real_distribution<double> radius(1, (EX_RADIUS-INT_RADIUS));
	cell_parameter choose_c(x+double(heart.x), y+double(heart.y), radius(e));
	return choose_c;
}

