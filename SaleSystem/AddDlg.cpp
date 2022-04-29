// AddDlg.cpp : 实现文件
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


// CAddDlg 诊断

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


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此添加控件通知处理程序代码
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
			UpdateData(FALSE); //内容更新到对应的控件
			break;
		}
	}

	file.ls.clear(); //清空list的内容


}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num1 <= 0)
	{
		MessageBox(TEXT("个数必须大于0！"),_T("警告"), MB_ICONWARNING);
		return;
	}

	CString type;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取组合框当前内容
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("添加了 商品：%s \r\n单价：%d \r\n个数：%d"), type, m_price1, m_num1);
	MessageBox(str,_T("提示"), MB_ICONINFORMATION);


	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
			m_left = it->num;
			break;
		}
	}
	file.WirteDocline(); //更新文件内容

	m_num1 = 0;
	UpdateData(FALSE); //更新到对应的控件

}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name2.IsEmpty())
	{
		MessageBox(_T("商品名不能为空！"), _T("警告"), MB_ICONWARNING);
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
			MessageBox(_T("商品已存在！"), _T("警告"), MB_ICONWARNING);
			m_name2.Empty();
			m_price2 = 0;
			m_num2 = 0;
			UpdateData(FALSE);
			return;
		}
	}
	if (m_price2 < 0)
	{
		MessageBox(_T("单价不能小于0！"), _T("警告"), MB_ICONWARNING);
		m_name2.Empty();
		m_price2 = 0;
		m_num2 = 0;
		UpdateData(FALSE);
		return;
	}
	if (m_num2 <= 0)
	{
		MessageBox(_T("个数必须大于0！"), _T("警告"), MB_ICONWARNING);
		m_name2.Empty();
		m_price2 = 0;
		m_num2 = 0;
		UpdateData(FALSE);
		return;
	}
	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(_T("添加成功！"), _T("提示"), MB_ICONINFORMATION);
	m_combo.AddString(m_name2);
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}
