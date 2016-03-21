// MyActiveXCtrl.cpp : Implementation of the CMyActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "MyActiveX.h"
#include "MyActiveXCtrl.h"
#include "MyActiveXPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMyActiveXCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CMyActiveXCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CMyActiveXCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CMyActiveXCtrl, COleControl)
	DISP_PROPERTY_NOTIFY_ID(CMyActiveXCtrl, "InputParameter", dispidInputParameter, m_InputParameter, OnInputParameterChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CMyActiveXCtrl, "OutputParameter", dispidOutputParameter, m_OutputParameter, OnOutputParameterChanged, VT_BSTR)
	DISP_FUNCTION_ID(CMyActiveXCtrl, "LoadParameter", dispidLoadParameter, LoadParameter, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CMyActiveXCtrl, "TestMyMethod", DISPID_TEST_METHOD, TestMyMethod, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CMyActiveXCtrl, COleControl)
	EVENT_CUSTOM_ID("ParameterLoaded", eventidParameterLoaded, FireParameterLoaded, VTS_NONE)
END_EVENT_MAP()



// Property pages

//// TODO: Add more property pages as needed.  Remember to increase the count!
//BEGIN_PROPPAGEIDS(CMyActiveXCtrl, 1)
//	PROPPAGEID(CMyActiveXPropPage::guid)
//END_PROPPAGEIDS(CMyActiveXCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMyActiveXCtrl, "MYACTIVEX.MyActiveXCtrl.1",
	0x36299202, 0x9ef, 0x4abf, 0xad, 0xb9, 0x47, 0xc5, 0x99, 0xdb, 0xe7, 0x78)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CMyActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DMyActiveX =
		{ 0x98AF8A06, 0x7DFE, 0x472D, { 0xA7, 0x13, 0xA0, 0xC6, 0xF2, 0x2F, 0xDC, 0x3D } };
const IID BASED_CODE IID_DMyActiveXEvents =
		{ 0x78099343, 0xA8FF, 0x4867, { 0xA5, 0x37, 0x6, 0xF3, 0x10, 0x34, 0xF2, 0x2B } };



// Control type information

static const DWORD BASED_CODE _dwMyActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMyActiveXCtrl, IDS_MYACTIVEX, _dwMyActiveXOleMisc)



unsigned long parseIPV4string(WCHAR* ipAddress) {
	unsigned int ipbytes[4] = {0};
	//FILE *pf = fopen("C:/Users/ALLENLN/log.txt", "a");
	//fwprintf(pf, L"ipaddress1: %s\n", ipAddress);
	
	swscanf(ipAddress, L"%u.%u.%u.%u", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
	//for (int i = 0; i < 4;i++)
	//{	
	//	fwprintf(pf, L"ip[%d]: %u\n",i, ipbytes[i]);
	//}
	//
	//fclose(pf);

	return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}




// CMyActiveXCtrl::CMyActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMyActiveXCtrl

BOOL CMyActiveXCtrl::CMyActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MYACTIVEX,
			IDB_MYACTIVEX,
			afxRegApartmentThreading,
			_dwMyActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CMyActiveXCtrl::CMyActiveXCtrl - Constructor

CMyActiveXCtrl::CMyActiveXCtrl()
{
	InitializeIIDs(&IID_DMyActiveX, &IID_DMyActiveXEvents);
	// TODO: Initialize your control's instance data here.
	//m_MainDialog.Create(IDD_OCXEXE_DIALOG, this);
	//m_pMainDialog = NULL;
	//m_pMainDialog = new COCXEXEDlg;
	//theApp.m_pMainWnd = m_pMainDialog;
//	m_pMainWnd = &dlg;
}



// CMyActiveXCtrl::~CMyActiveXCtrl - Destructor

CMyActiveXCtrl::~CMyActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
	//if (m_pMainDialog)
	//{
	//	delete m_pMainDialog;
	//	m_pMainDialog = NULL;
	//}
}



// CMyActiveXCtrl::OnDraw - Drawing function

//void CMyActiveXCtrl::OnDraw(
//			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
//{
//	if (!pdc)
//		return;
//
//	DoSuperclassPaint(pdc, rcBounds);
//	if (m_MainDialog.m_hWnd != NULL)
//	{
//		m_MainDialog.MoveWindow(rcBounds, TRUE);
//	}
//	CBrush brBackGnd(TranslateColor(AmbientBackColor()));
//	pdc->FillRect(rcBounds, &brBackGnd);
//}



// CMyActiveXCtrl::DoPropExchange - Persistence support

void CMyActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CMyActiveXCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CMyActiveXCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control will not be redrawn when making the transition
	// between the active and inactivate state.
	dwFlags |= noFlickerActivate;
	return dwFlags;
}



// CMyActiveXCtrl::OnResetState - Reset control to default state

void CMyActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CMyActiveXCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CMyActiveXCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	return COleControl::PreCreateWindow(cs);
}



// CMyActiveXCtrl::IsSubclassedControl - This is a subclassed control

BOOL CMyActiveXCtrl::IsSubclassedControl()
{
	return TRUE;
}



// CMyActiveXCtrl::OnOcmCommand - Handle command messages

LRESULT CMyActiveXCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}



// CMyActiveXCtrl message handlers

int CMyActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_pMainDialog->Create(IDD_OCXEXE_DIALOG, this);

	// TODO:  Add your specialized creation code here
	m_MainDialog.Create(IDD_OCXEXE_DIALOG, this);
	
	
	
	//COCXEXEDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = m_MainDialog.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}

	//// Since the dialog has been closed, return FALSE so that we exit the
	////  application, rather than start the application's message pump.
	//return FALSE;

	return 0;
}


LONG CMyActiveXCtrl::TestMyMethod(BSTR param1, BSTR param2, BSTR param3, BSTR param4)
{
	//FILE *pf = fopen("C:/Users/ALLENLN/log.txt", "a");
	//fwprintf(pf, L"input: %s\n", param1);

	unsigned long ipaddr = parseIPV4string(param1);
	
	//fprintf(pf, "ipaddress: %u\n", ipaddr);
	
	unsigned short port = _wtoi(param2);
	LPCTSTR user = param3;
	LPCTSTR pass = param4;

	//fprintf(pf, "ip: %lu, port: %u, user: %s, pass: %s\n", ipaddr, port, user, pass);
	
	//fclose(pf);
	m_MainDialog.OnConnect(ipaddr, port, user, pass);

	//m_MainDialog.OnConnect(0xC0A80191, 50010, _T("admin"), _T("A1crUF4="));
	return -5;
}

void CMyActiveXCtrl::OnInputParameterChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

void CMyActiveXCtrl::OnOutputParameterChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

void CMyActiveXCtrl::LoadParameter(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	// Copy text from the input parameter to the output parameter
	m_OutputParameter = m_InputParameter;
	// Fire an event to notify web page
	FireParameterLoaded();
}
