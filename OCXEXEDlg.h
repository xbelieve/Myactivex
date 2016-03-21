// OCXEXEDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <vector>
#include "..\OCXDLL\OCXDLLInterface.h"
#include "resource.h"

using namespace std;


// COCXEXEDlg dialog
class COCXEXEDlg : public CDialog
{
// Construction
public:
	COCXEXEDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~COCXEXEDlg();
// Dialog Data
	enum { IDD = IDD_OCXEXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	vector<OCXDLLDialog*> m_windows;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_bnAdd;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedRemove();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnConnect(unsigned long IP, unsigned short port, LPCTSTR user, LPCTSTR pass);
};
