#pragma once


// COptionalDialog �Ի���

class COptionalDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionalDialog)

public:
	COptionalDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptionalDialog();
	double m_str_INT_RADIUS;
	double m_str_EX_RADIUS;
	double m_CELL_NUM;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};
