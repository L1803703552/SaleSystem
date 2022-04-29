#pragma once
#include "afxwin.h"



// CDelDlg 窗体视图

class CDelDlg : public CFormView
{
	DECLARE_DYNCREATE(CDelDlg)

protected:
	CDelDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CDelDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_DEL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo1;
	CComboBox m_combo2;
	int m_price1;
	int m_price2;
	int m_left1;
	int m_left2;
	int m_num;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
};


