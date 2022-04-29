#pragma once
#include "afxwin.h"



// CAddDlg ������ͼ

class CAddDlg : public CFormView
{
	DECLARE_DYNCREATE(CAddDlg)

protected:
	CAddDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CAddDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADD };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	CComboBox m_combo;
	int m_price1;
	int m_num1;
	CString m_name2;
	int m_price2;
	int m_num2;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	int m_left;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

