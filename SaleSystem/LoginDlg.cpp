// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	exit(0);
	//CDialogEx::OnCancel();
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_pwd.IsEmpty() || m_user.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空！"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (name == m_user)
	{
		if (pwd == m_pwd)
		{
			CDialog::OnOK();
		}
		else
			MessageBox(TEXT("密码错误！"),TEXT("警告"), MB_ICONWARNING);
	}
	else
	{
		MessageBox(TEXT("用户名有误！"), TEXT("警告"), MB_ICONWARNING);
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CInfoFile file;
	file.ReadLogin(m_user, m_pwd);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
