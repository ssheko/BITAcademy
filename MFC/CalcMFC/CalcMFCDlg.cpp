
// CalcMFCDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CalcMFC.h"
#include "CalcMFCDlg.h"
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


// CCalcMFCDlg 대화 상자



CCalcMFCDlg::CCalcMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCMFC_DIALOG, pParent)
	, strFirst(_T(""))
	, strSecond(_T(""))
	, strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRST, strFirst);
	DDX_Text(pDX, IDC_EDIT_SECOND, strSecond);
	DDX_Text(pDX, IDC_EDIT_RESULT, strResult);
	DDX_Control(pDX, IDC_EDIT_FIRST, editFirst);
	DDX_Control(pDX, IDC_EDIT_SECOND, editSecond);
}

BEGIN_MESSAGE_MAP(CCalcMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CCalcMFCDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalcMFCDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalcMFCDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalcMFCDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalcMFCDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_EQ, &CCalcMFCDlg::OnBnClickedButtonEq)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CCalcMFCDlg::OnBnClickedButtonInit)
END_MESSAGE_MAP()


// CCalcMFCDlg 메시지 처리기

BOOL CCalcMFCDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalcMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalcMFCDlg::OnPaint()
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
HCURSOR CCalcMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalcMFCDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CCalcMFCDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strOp = '+';
}


void CCalcMFCDlg::OnBnClickedButtonSub()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strOp = '-';
}


void CCalcMFCDlg::OnBnClickedButtonMul()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strOp = '*';
}


void CCalcMFCDlg::OnBnClickedButtonDiv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strOp = '/';
}


void CCalcMFCDlg::OnBnClickedButtonEq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HMODULE hModule = ::LoadLibrary(_T("CalcDLL.dll"));	// 쓰기 위해 연결
	editFirst.GetWindowTextW(strFirst);
	editSecond.GetWindowTextW(strSecond);
	//MessageBox(strFirst);
	int(WINAPI* pfnCalculate)(int,int,CString&) = NULL;	// 함수포인터 선언
	int result = 0;
	pfnCalculate =
		(int(WINAPI*)(int,int,CString&))::GetProcAddress(hModule, "Calculate");	// 함수포인터	// MBCS 타입.
	//int result = ::Calculate(_ttoi(strFirst), _ttoi(strSecond), strOp);
	if (pfnCalculate != NULL)
	{
		if (result = pfnCalculate(_ttoi(strFirst), _ttoi(strSecond), strOp))
			strResult.Format(_T("%d"), result);
		else
			AfxMessageBox(_T("ERROR: Failed to get function address"));
	}
	
	//strResult.Format(_T("%d"), result);
	::FreeLibrary(hModule);
	UpdateData(FALSE);
}


void CCalcMFCDlg::OnBnClickedButtonInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strFirst = _T("0");
	strSecond = _T("0");
	strResult = _T("0");
	UpdateData(FALSE);
	
}
//int WINAPI CCalcMFCDlg::Calculate2(int fir, int sec, CString &op)	//
//{
//	int result = 0;
//	switch (*op)
//	{
//	case '+':
//		result = fir + sec;
//		break;
//	case '-':
//		result = fir - sec;
//		break;
//	case '*':
//		result = fir * sec;
//		break;
//	case '/':
//		result = fir / sec;
//		break;
//	default:
//		result = 0;
//		break;
//	}
//	return result;
//}