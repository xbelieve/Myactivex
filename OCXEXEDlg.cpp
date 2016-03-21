// OCXEXEDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "OCXEXE.h"
#include "OCXEXEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//// CAboutDlg dialog used for App About
//
//class CAboutDlg : public CDialog
//{
//public:
//	CAboutDlg();
//
//// Dialog Data
//	enum { IDD = IDD_ABOUTBOX };
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//// Implementation
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//END_MESSAGE_MAP()
//
//
//// COCXEXEDlg dialog




COCXEXEDlg::COCXEXEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COCXEXEDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

COCXEXEDlg::~COCXEXEDlg()
{
	if (m_windows.size()>0 )
	{
		for (int i = 0; i < m_windows.size(); i++)
		{
			VideoDestroy(m_windows[i]);
			m_windows[i] = NULL;
		}
	}
}

void COCXEXEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDB_ADD, m_bnAdd);
}

BEGIN_MESSAGE_MAP(COCXEXEDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_ADD, &COCXEXEDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDB_START, &COCXEXEDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDB_REMOVE, &COCXEXEDlg::OnBnClickedRemove)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// COCXEXEDlg message handlers

BOOL COCXEXEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	CString strAboutMenu;
	//	//strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		//pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ShowWindow(true);

	OCXDLLDialog *dlg = VideoCreate(NULL);
	dlg->SetParent(this);
	dlg->ShowWindow(SW_SHOW);
	//dlg->MoveWindow(((int)m_windows.size() & 1) * 250, ((int)m_windows.size() & 2) * 50, 250, 100);

	m_windows.push_back(dlg);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//void COCXEXEDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	//{
//	//	CAboutDlg dlgAbout;
//	//	dlgAbout.DoModal();
//	//}
//	//else
//	{
//		CDialog::OnSysCommand(nID, lParam);
//	}
//}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COCXEXEDlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
//HCURSOR COCXEXEDlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}


void COCXEXEDlg::OnBnClickedAdd()
{
	OCXDLLDialog *dlg = VideoCreate(NULL);

	dlg->SetParent(this);
	dlg->ShowWindow(SW_SHOW);
	//dlg->MoveWindow(((int)m_windows.size() & 1) * 250, ((int)m_windows.size() & 2) * 50, 250, 100);
	m_windows.push_back(dlg);
}

void COCXEXEDlg::OnBnClickedRemove()
{
	if (m_windows.size() > 0) {
		OCXDLLDialog *dlg = m_windows.back();
		m_windows.pop_back();
		dlg->SetParent(NULL);
		VideoDestroy(dlg);
	}
}

void COCXEXEDlg::OnBnClickedStart()
{
	if (m_windows.size() > 0) {
		// This will connect to live video on localhost (127.0.0.1), camera #1, using user “admin?and password “admin?
		VideoPlay(m_windows.back(), 0xC0A80191, 50010, _T("admin"), _T("A1crUF4="), 0);
		//0xA9FEDC30
	}
}

int COCXEXEDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//OnInitDialog();
	//// TODO:  Add your specialized creation code here
	//if (m_ProgressBar.Load(MAKEINTRESOURCE(IDR_PROGRESSBAR), _T("GIF")))
	//	m_ProgressBar.Draw();

	return 0;
}

void COCXEXEDlg::OnConnect(unsigned long IP, unsigned short port, LPCTSTR user, LPCTSTR pass)
{
	VideoPlay(m_windows.back(), IP, port, user, pass, 0);
}