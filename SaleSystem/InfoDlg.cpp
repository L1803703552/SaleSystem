// InfoDlg.cpp : ʵ���ļ�
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


// CInfoDlg ���

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


// CInfoDlg ��Ϣ�������


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString str[] = { _T("��ƷID"),_T("��Ʒ��"),_T("����"),_T("���") };
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
