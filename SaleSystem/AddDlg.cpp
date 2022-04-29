// AddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
	, m_left(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT3, m_num1);
	DDX_Text(pDX, IDC_EDIT7, m_name2);
	DDX_Text(pDX, IDC_EDIT5, m_price2);
	DDX_Text(pDX, IDC_EDIT4, m_num2);
	DDX_Text(pDX, IDC_EDIT8, m_left);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg ���

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg ��Ϣ�������


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}
	file.ls.clear();
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString text;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, text);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_price1 = it->price;
			m_num1 = 0;
			m_left = it->num;
			UpdateData(FALSE); //���ݸ��µ���Ӧ�Ŀؼ�
			break;
		}
	}

	file.ls.clear(); //���list������


}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_num1 <= 0)
	{
		MessageBox(TEXT("�����������0��"),_T("����"), MB_ICONWARNING);
		return;
	}

	CString type;
	//��ȡ��ǰѡ����
	int index = m_combo.GetCurSel();
	//��ȡ��Ͽ�ǰ����
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("����� ��Ʒ��%s \r\n���ۣ�%d \r\n������%d"), type, m_price1, m_num1);
	MessageBox(str,_T("��ʾ"), MB_ICONINFORMATION);


	//��Ҫ����#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //��ȡ��Ʒ��Ϣ
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
			m_left = it->num;
			break;
		}
	}
	file.WirteDocline(); //�����ļ�����

	m_num1 = 0;
	UpdateData(FALSE); //���µ���Ӧ�Ŀؼ�

}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_name2.IsEmpty())
	{
		MessageBox(_T("��Ʒ������Ϊ�գ�"), _T("����"), MB_ICONWARNING);
		m_name2.Empty();
		m_price2 = 0;
		m_num2 = 0;
		UpdateData(FALSE);
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (m_name2 == (CString)it->name.c_str())
		{
			MessageBox(_T("��Ʒ�Ѵ��ڣ�"), _T("����"), MB_ICONWARNING);
			m_name2.Empty();
			m_price2 = 0;
			m_num2 = 0;
			UpdateData(FALSE);
			return;
		}
	}
	if (m_price2 < 0)
	{
		MessageBox(_T("���۲���С��0��"), _T("����"), MB_ICONWARNING);
		m_name2.Empty();
		m_price2 = 0;
		m_num2 = 0;
		UpdateData(FALSE);
		return;
	}
	if (m_num2 <= 0)
	{
		MessageBox(_T("�����������0��"), _T("����"), MB_ICONWARNING);
		m_name2.Empty();
		m_price2 = 0;
		m_num2 = 0;
		UpdateData(FALSE);
		return;
	}
	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(_T("��ӳɹ���"), _T("��ʾ"), MB_ICONINFORMATION);
	m_combo.AddString(m_name2);
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}
