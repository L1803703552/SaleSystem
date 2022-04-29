// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	exit(0);
	//CDialogEx::OnCancel();
}


void CLoginDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_pwd.IsEmpty() || m_user.IsEmpty())
	{
		MessageBox(TEXT("�������ݲ���Ϊ�գ�"), TEXT("����"), MB_ICONWARNING);
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
			MessageBox(TEXT("�������"),TEXT("����"), MB_ICONWARNING);
	}
	else
	{
		MessageBox(TEXT("�û�������"), TEXT("����"), MB_ICONWARNING);
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CInfoFile file;
	file.ReadLogin(m_user, m_pwd);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
