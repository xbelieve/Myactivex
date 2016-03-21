#pragma once
//#include "maindialog.h"
#include "OCXEXEDlg.h"

// MyActiveXCtrl.h : Declaration of the CMyActiveXCtrl ActiveX Control class.


// CMyActiveXCtrl : See MyActiveXCtrl.cpp for implementation.
static const int DISPID_TEST_METHOD = 1025314;
class CMyActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMyActiveXCtrl)

// Constructor
public:
	CMyActiveXCtrl();

// Overrides
public:
	//virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// Implementation
protected:
	~CMyActiveXCtrl();

	DECLARE_OLECREATE_EX(CMyActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMyActiveXCtrl)      // GetTypeInfo
	//DECLARE_PROPPAGEIDS(CMyActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMyActiveXCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		eventidParameterLoaded = 1L,
		dispidLoadParameter = 3L,
		dispidOutputParameter = 2,
		dispidInputParameter = 1
	};
public:
	//CMainDialog m_MainDialog;
	COCXEXEDlg m_MainDialog;
	//COCXEXEDlg *m_pMainDialog;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg LONG TestMyMethod(BSTR param1, BSTR param2, BSTR param3, BSTR param4);
protected:
	void OnInputParameterChanged(void);
	CString m_InputParameter;
	void OnOutputParameterChanged(void);
	CString m_OutputParameter;
	void LoadParameter(void);
	LONG TestMyMethod(BSTR param1, BSTR param2, BSTR param3, BSTR param4);

	void FireParameterLoaded(void)
	{
		FireEvent(eventidParameterLoaded, EVENT_PARAM(VTS_NONE));
	}
};

