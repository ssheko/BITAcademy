
// day22_04.30_1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "day22_04.30_1.h"
#include "day22_04.30_1Dlg.h"
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


// Cday2204301Dlg 대화 상자



Cday2204301Dlg::Cday2204301Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAY22_0430_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cday2204301Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cday2204301Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &Cday2204301Dlg::OnBnClickedButtonRun)
END_MESSAGE_MAP()


// Cday2204301Dlg 메시지 처리기

BOOL Cday2204301Dlg::OnInitDialog()
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

void Cday2204301Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cday2204301Dlg::OnPaint()
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
HCURSOR Cday2204301Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
UINT ThreadWaitNotepad(LPVOID pParam)
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//// ver.2,3 => 메모장 실행 스레드를 ThreadWaitNotepad 함수로 만들고, 버튼 클릭시 해당 스레드 생성
	TCHAR szWinPath[MAX_PATH];
	::GetWindowsDirectory(szWinPath, MAX_PATH);	// C \ windows 폴더
	lstrcat(szWinPath, _T("\\notepad.exe"));	// strcat과 같음 // C \ windows \ notepad.exe

	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.hwnd = NULL;
	sei.lpFile = szWinPath;
	sei.nShow = SW_SHOW;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	// SEE_MASK_NOCLOSEPROCESS: 프로세스 실행 성공 시 (노트패드) 핸들을 hProcess에 저장

	sei.lpVerb = _T("open");
	sei.lpParameters = NULL;

	if (ShellExecuteEx(&sei)) {
		// //ver.3 => 메모장 켜진 상태에서 프로그램 종료할 경우 메모리 누수 오류 발생
		// hProcess가 끝날때까지 무한 대기.
		// sei.hProcess가 set될때까지 기다림 (메모리 영역이 바뀔때까지)
		//::WaitForSingleObject(sei.hProcess, INFINITE);
		//AfxMessageBox(_T("메모장 종료"));

		// //ver.4	=> Cday2204301App::ExitInstance() 추가해 종료 이벤트 발생시켜 메모리 누수 오류 해결
		HANDLE arhList[2];
		arhList[0] = sei.hProcess;			// 메모장 프로세스 핸들
		arhList[1] = (HANDLE)g_ExitEvent;	// 종료 이벤트 핸들

		DWORD dwResult = ::WaitForMultipleObjects(2, arhList, FALSE, INFINITE);
		// FALSE: 감시대상 객체 중 하나라도 Set되면 함수 반환
		// TRUE: 둘 다 Set될 때까지 무한 대기. 

		if(dwResult == WAIT_OBJECT_0)
			AfxMessageBox(_T("메모장 종료"));
		else if (dwResult == WAIT_OBJECT_0 + 1) 
			OutputDebugString(_T("WorkerThreadDemo 예제 종료 \n"));	// Debug창에 출력하는 매크로 함수
		

	}
	g_pThread = NULL;
	return 0;
}


void Cday2204301Dlg::OnBnClickedButtonRun()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//// ver.1 => 버튼 클릭시 메모장 실행
	//TCHAR szWinPath[MAX_PATH];
	//::GetWindowsDirectory(szWinPath, MAX_PATH);	// C windows 폴더
	//lstrcat(szWinPath, _T("\\notepad.exe"));	// strcat과 같음 // C windows 밑 notepad.exe

	//SHELLEXECUTEINFO sei;
	//::ZeroMemory(&sei, sizeof(sei));
	//sei.cbSize = sizeof(sei);
	//sei.hwnd = NULL;
	//sei.lpFile = szWinPath;
	//sei.nShow = SW_SHOW;
	//sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//// SEE_MASK_NOCLOSEPROCESS: 프로세스 실행 성공 시 (노트패드) 핸들을 hProcess에 저장

	//sei.lpVerb = _T("open");
	//sei.lpParameters = NULL;

	//if (ShellExecuteEx(&sei)) {
	//	// hProcess가 끝날때까지 무한 대기.
	//	// sei.hProcess가 set될때까지 기다림 (메모리 영역이 바뀔때까지)
	//	::WaitForSingleObject(sei.hProcess, INFINITE);
	//}


	//// ver.2 => 메모장 실행 스레드를 ThreadWaitNotepad 함수로 만들고, 버튼 클릭시 해당 스레드 생성
	//CWinThread* pThread = AfxBeginThread(ThreadWaitNotepad, NULL);
	//if (pThread == NULL) {
	//	AfxMessageBox(_T("Error: Failed to begin worker-thread"));
	//}

	//// ver.3
	if (g_pThread != NULL)
	{
		AfxMessageBox(_T("메모장이 이미 실행 중입니다."));
		return;
	}

	g_pThread = AfxBeginThread(ThreadWaitNotepad, NULL);
	if (g_pThread == NULL) {
			AfxMessageBox(_T("Error: Failed to begin worker-thread"));
	}
}