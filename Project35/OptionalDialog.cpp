// OptionalDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OptionalDialog.h"
#include "afxdialogex.h"
#include "resource.h"

// COptionalDialog 对话框

IMPLEMENT_DYNAMIC(COptionalDialog, CDialog)

COptionalDialog::COptionalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

COptionalDialog::~COptionalDialog()
{
}

BOOL COptionalDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_EDIT1, m_str_INT_RADIUS);
	SetDlgItemInt(IDC_EDIT2, m_str_EX_RADIUS);
	SetDlgItemInt(IDC_EDIT3, m_CELL_NUM);
	return TRUE;
}


void COptionalDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT1, m_str_INT_RADIUS);
	DDX_Text(pDX, IDC_EDIT2, m_str_EX_RADIUS);
	DDX_Text(pDX, IDC_EDIT3, m_CELL_NUM);
}

void COptionalDialog::OnOK()
{
	GetDlgItemInt(IDC_EDIT1);
	GetDlgItemInt(IDC_EDIT2);
	GetDlgItemInt(IDC_EDIT3);
	CDialog::OnOK();
}


BEGIN_MESSAGE_MAP(COptionalDialog, CDialog)
	
END_MESSAGE_MAP()


// COptionalDialog 消息处理程序
