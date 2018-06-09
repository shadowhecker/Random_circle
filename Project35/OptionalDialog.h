#pragma once


// COptionalDialog 对话框

class COptionalDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionalDialog)

public:
	COptionalDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionalDialog();
	double m_str_INT_RADIUS;
	double m_str_EX_RADIUS;
	double m_CELL_NUM;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
