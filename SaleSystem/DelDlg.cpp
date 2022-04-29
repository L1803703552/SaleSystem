// DelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DEL)
	, m_price1(0)
	, m_price2(0)
	, m_left1(0)
	, m_left2(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT5, m_price2);
	DDX_Text(pDX, IDC_EDIT8, m_left1);
	DDX_Text(pDX, IDC_EDIT4, m_left2);
	DDX_Text(pDX, IDC_EDIT3, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDelDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDelDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDelDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDelDlg ���

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg ��Ϣ�������


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CInfoFile file;
	file.ReadDocline();
	m_combo1.ResetContent();
	m_combo2.ResetContent();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo1.AddString((CString)it->name.c_str());
		m_combo2.AddString((CString)it->name.c_str());
	}
	m_combo1.SetCurSel(0);
	m_combo2.SetCurSel(0);
	OnCbnSelchangeCombo1();
	OnCbnSelchangeCombo2();

}



void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CInfoFile file;
	CString sel;
	int index = m_combo1.GetCurSel();
	m_combo1.GetLBText(index, sel);
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (sel == (CString)it->name.c_str())
		{
			m_price1 = it->price;
			m_left1 = it->num;
			UpdateData(FALSE);
			break;
		}
	}
}


void CDelDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CInfoFile file;
	CString sel;
	int index = m_combo2.GetCurSel();
	m_combo2.GetLBText(index, sel);
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (sel == (CString)it->name.c_str())
		{
			m_price2 = it->price;
			m_left2 = it->num;
			UpdateData(FALSE);
			break;
		}
	}
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_combo1.SetCurSel(0);
	OnCbnSelchangeCombo1();
	m_num = 0;
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_combo2.SetCurSel(0);
	OnCbnSelchangeCombo2();
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_num <= 0)
	{
		MessageBox(_T("ɾ�������������0��"), _T("����"), MB_ICONWARNING);
		return;
	}
	UINT i;
	i = MessageBox(_T("ȷ��ɾ����"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}
	CInfoFile file;
	CString sel,sel2;
	int index = m_combo1.GetCurSel(), index2 = m_combo1.GetCurSel();
	m_combo1.GetLBText(index, sel);
	m_combo2.GetLBText(index2, sel2);
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (sel == (CString)it->name.c_str())
		{
			if (m_num > it->num)
			{
				MessageBox(_T("ɾ���������ڿ��������"), _T("����"), MB_ICONWARNING);
				return;
			}
			else
			{
				it->num -= m_num;
				m_num = 0;
				m_left1 = it->num;
				if (sel == sel2)
				{
					m_left2 = it->num;
				}
				break;
			}
		}
	}
	file.WirteDocline();
	UpdateData(FALSE);
	MessageBox(_T("ɾ���ɹ���"), _T("��ʾ"), MB_ICONINFORMATION);
}


void CDelDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	UINT i;
	i = MessageBox(_T("ȷ��ɾ����"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}
	CInfoFile file;
	CString sel,sel2;
	int index = m_combo2.GetCurSel();
	m_combo2.GetLBText(index, sel);
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (sel == (CString)it->name.c_str())
		{
			file.ls.remove(*it);
			break;
		}
	}
	file.WirteDocline();
	OnInitialUpdate();
	UpdateData(FALSE);
	MessageBox(_T("ɾ���ɹ���"), _T("��ʾ"), MB_ICONINFORMATION);
}
