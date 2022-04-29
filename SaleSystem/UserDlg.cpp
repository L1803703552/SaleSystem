// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_user = TEXT("销售员");
	m_name = name;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString name, pwd;
	CInfoFile file;
	file.ReadLogin(name, pwd);
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入密码不能为空！"), TEXT("警告"), MB_ICONEXCLAMATION);
	}
	else if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("两次输入密码不同！"), TEXT("警告"), MB_ICONEXCLAMATION);
	}
	else if (m_surePwd == pwd)
	{
		MessageBox(TEXT("新密码不能与旧密码相同！"), TEXT("警告"), MB_ICONEXCLAMATION);
	}
	else if (m_newPwd == m_surePwd)
	{
		pwd = m_newPwd;
		CStringA tmp1,tmp2;
		tmp1 = name;
		tmp2 = pwd;
		file.WritePwd(tmp1.GetBuffer(), tmp2.GetBuffer());
		MessageBox(TEXT("修改成功！"), TEXT("提示"), MB_ICONINFORMATION);
		m_newPwd.Empty();
		m_surePwd.Empty();
		UpdateData(FALSE);
	}
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
