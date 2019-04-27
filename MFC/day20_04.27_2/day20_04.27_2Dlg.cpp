
// day20_04.27_2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "day20_04.27_2.h"
#include "day20_04.27_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cday2004272Dlg 대화 상자



Cday2004272Dlg::Cday2004272Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAY20_0427_2_DIALOG, pParent)
	, strTest(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cday2004272Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_TEST, edit);
	//  DDX_Text(pDX, IDC_EDIT_TEST, edit);
	DDX_Text(pDX, IDC_EDIT_TEST, strTest);
}

BEGIN_MESSAGE_MAP(Cday2004272Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &Cday2004272Dlg::OnBnClickedButtontest)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &Cday2004272Dlg::OnBnClickedButtonexit)
	ON_BN_CLICKED(IDC_BUTTON_YN, &Cday2004272Dlg::OnBnClickedButtonYn)
	ON_BN_CLICKED(IDC_BUTTON_OC, &Cday2004272Dlg::OnBnClickedButtonOc)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Cday2004272Dlg 메시지 처리기

BOOL Cday2004272Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	e.Attach(GetDlgItem(IDC_EDIT_TEST)->m_hWnd);	// edit control의 핸들을 받아와서 e에 attach. e는 edit control의 핸들을 가지고 있는 것

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cday2004272Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cday2004272Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cday2004272Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cday2004272Dlg::OnBnClickedButtontest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("MFC 버튼 테스트"));
}


void Cday2004272Dlg::OnBnClickedButtonexit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void Cday2004272Dlg::OnBnClickedButtonYn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iResult;

	iResult = AfxMessageBox
	(_T("YES/NO 버튼 클릭"), (MB_YESNO | MB_ICONEXCLAMATION));
	if (iResult == IDYES)
	{
		strTest = _T("YES 버튼 클릭");
		UpdateData(FALSE);	// FALSE: strTest값을 editText로 보냄.(윈도우 메시지 전송) \
							   TRUE: editText 값을 strTest 값으로 가져옴.(윈도우에서 이쪽으로 메세지 전송받음)
	}
	if (iResult == IDNO)
	{
		strTest = _T("NO 버튼 클릭");
		UpdateData(FALSE);
	}
}


void Cday2004272Dlg::OnBnClickedButtonOc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iResult;
	iResult = AfxMessageBox
	(_T("OK/CANCEL 버튼 클릭"), (MB_OKCANCEL | MB_ICONSTOP));
	if (iResult == IDOK)
	{		
		e.SetWindowTextW(_T("hi"));
		//SetDlgItemTextW(IDC_EDIT_TEST, _T("hi"));
		//strTest = _T("OK 버튼 클릭");
		//UpdateData(FALSE);
	}
	if (iResult == IDCANCEL)
	{
		strTest = _T("CANCEL 버튼 클릭");
		UpdateData(FALSE);
	}
}


void Cday2004272Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	e.Detach();
}
