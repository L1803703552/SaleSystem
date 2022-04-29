// InfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "InfoDlg.h"
#include "InfoFile.h"


// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString str[] = { _T("商品ID"),_T("商品名"),_T("单价"),_T("库存") };
	for (int i = 0; i < 4; i++)
	{
		m_list.InsertColumn(i+1, str[i], LVCFMT_CENTER, 100);
	}
	CInfoFile file;
	file.ReadDocline();
	int i = 0;
	CString info;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++,i++)
	{
		info.Format(_T("%d"), it->id);
		m_list.InsertItem(i, info);
		int j = 1;
		m_list.SetItemText(i, j++, (CString)it->name.c_str());
		info.Format(_T("%d"), it->price);
		m_list.SetItemText(i, j++, info);
		info.Format(_T("%d"), it->num);
		m_list.SetItemText(i, j++, info);
	}

}
