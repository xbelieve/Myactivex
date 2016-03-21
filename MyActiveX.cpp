// MyActiveX.cpp : Implementation of CMyActiveXApp and DLL registration.

#include "stdafx.h"
#include "MyActiveX.h"
#include "comcat.h"
#include "strsafe.h"
#include "objsafe.h"
#include "OCXEXEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMyActiveXApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xCBE9E0B0, 0x95DB, 0x4495, { 0x8B, 0xE8, 0xE4, 0xCB, 0x41, 0x6E, 0xF0, 0x7D } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

// CLSID_SafeItem - Necessary for safe ActiveX control
// Id taken from IMPLEMENT_OLECREATE_EX function in xxxCtrl.cpp

const CATID CLSID_SafeItem =
{0x36299202, 0x9ef, 0x4abf,{ 0xad, 0xb9, 0x47, 0xc5, 0x99, 0xdb, 0xe7, 0x78}};



// CMyActiveXApp::InitInstance - DLL initialization

BOOL CMyActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
		//COCXEXEDlg dlg;
		//m_pMainWnd = &dlg;
		//INT_PTR nResponse = dlg.ShowWindow(true);
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
	}

	return bInit;
}



// CMyActiveXApp::ExitInstance - DLL termination

int CMyActiveXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// HRESULT CreateComponentCategory - Used to register ActiveX control as safe

HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (FAILED(hr))
        return hr;

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered.
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409 ; // english
    size_t len;
    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is.
    // The second parameter of StringCchLength is the maximum
    // number of characters that may be read into catDescription.
    // There must be room for a NULL-terminator. The third parameter
    // contains the number of characters excluding the NULL-terminator.
	hr = StringCchLength(catDescription, STRSAFE_MAX_CCH, &len);
	if (SUCCEEDED(hr))
	   {
        if (len>127)
		   {
           len = 127;
		   }
		}   
    else
	    {
		// TODO: Write an error handler;
		}
	// The second parameter of StringCchCopy is 128 because you need 
    // room for a NULL-terminator.    
	hr = StringCchCopy(catinfo.szDescription, len + 1, 
           catDescription);
	// Make sure the description is null terminated.
        catinfo.szDescription[len + 1] = '\0';

    hr = pcr->RegisterCategories(1, &catinfo);
        pcr->Release();

    return hr;
}

// HRESULT RegisterCLSIDInCategory - Register your component categories information

HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
// Register your component categories information.
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
                NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))
    {
       // Register this category as being "implemented" by the class.
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if (pcr != NULL)
        pcr->Release();
		
    return hr;
}

// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    HRESULT hr;    // HResult used by Safety Functions

	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

    // Mark the control as safe for initializing.

	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
    if (FAILED(hr))
        return hr;

    // Mark the control as safe for scripting.

	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
    if (FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
    if (FAILED(hr))
        return hr;

	return NOERROR;
}

// HRESULT UnRegisterCLSIDInCategory - Remove entries from the registry

HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))
    {
       // Unregister this category as being "implemented" by the class.
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if (pcr != NULL)
        pcr->Release();

    return hr;
}

// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    HRESULT hr;    // HResult used by Safety Functions

	AFX_MANAGE_STATE(_afxModuleAddrThis);

	hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (SUCCEEDED(hr))
		hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	return hr;

	//if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
	//	return ResultFromScode(SELFREG_E_TYPELIB);

	//if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
	//	return ResultFromScode(SELFREG_E_CLASS);

 //   // Remove entries from the registry.

 //   hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
 //   if (FAILED(hr))
 //       return hr;

 //   hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
 //   if (FAILED(hr))
 //       return hr;

	//return NOERROR;
}
