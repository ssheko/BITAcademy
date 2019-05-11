
// SocketChatClientDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SocketChatClient.h"
#include "SocketChatClientDlg.h"
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


// CSocketChatClientDlg 대화 상자



CSocketChatClientDlg::CSocketChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKETCHATCLIENT_DIALOG, pParent)
	, strEditMsg(_T(""))
	, strEditNickname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDR, ctrlIPAddr);
	DDX_Control(pDX, IDC_EDIT_MSG, ctrlEditMsg);
	DDX_Control(pDX, IDC_LIST_MSG, ctrlListMsg);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, ctrlButtonConnect);
	DDX_Text(pDX, IDC_EDIT_MSG, strEditMsg);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, strEditNickname);
}

BEGIN_MESSAGE_MAP(CSocketChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSocketChatClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocketChatClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDOK, &CSocketChatClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSocketChatClientDlg 메시지 처리기

BOOL CSocketChatClientDlg::OnInitDialog()
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

	ctrlIPAddr.SetAddress(htonl(inet_addr("127.0.0.1")));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSocketChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocketChatClientDlg::OnPaint()
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
HCURSOR CSocketChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



UINT recvThread(void* arg) {
	CSocketChatClientDlg *thisContext = (CSocketChatClientDlg*)arg;
	while (1) {
		thisContext->ReceiveMessage(thisContext->sock);
	}
	return 0;
}
int CSocketChatClientDlg::ReceiveMessage(SOCKET s)
{
	// TODO: 여기에 구현 코드 추가.
	int received;
	char ptr[BUFFERSIZE];
	TCHAR szBuffer[BUFFERSIZE];
	ZeroMemory(ptr, sizeof(ptr));
	received = recv(s, ptr, sizeof(ptr) - 1, 0);
	if (received == SOCKET_ERROR || received == 0) {
		DisplayMessage();
		return FALSE;
	}

	ptr[received] = '\0';
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, ptr, strlen(ptr) + 1, szBuffer, BUFFERSIZE);
	ctrlListMsg.InsertString(-1, szBuffer);
	ctrlListMsg.SetCurSel(ctrlListMsg.GetCount() - 1);
	return -1;
}


void CSocketChatClientDlg::DisplayMessage()
{
	// TODO: 여기에 구현 코드 추가.

	LPVOID pMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // 오류 메세지 저장 메모리를 내부에서 할당하라
		FORMAT_MESSAGE_FROM_SYSTEM,		// 운영체제로부터 오류 메세지를 가져온다
		NULL,
		WSAGetLastError(),				// 오류 코드
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 언어 (제어판 설정 언어)
		(LPTSTR)&pMsg,					// 오류 메세지 outparam
		0, NULL);

	AfxMessageBox((LPTSTR)pMsg);				// 오류 메세지 출력

	LocalFree(pMsg);					// 오류 메세지 저장 메모리 반환
}


int CSocketChatClientDlg::InitSocket(CString IPAddress)
{
	// TODO: 여기에 구현 코드 추가.
	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}

	// 클라이언트 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = inet_addr((CStringA)IPAddress);	//IPAddress

	// 서버에 접속 요청
	retval = connect(
		sock,	// 소켓 핸들
		(SOCKADDR *)&serveraddr,	//접속 서버 주소값
		sizeof(serveraddr)			// 주소값 크기
	);	// 통신 소켓(성공하면 자동으로 지역포트, 지역주소를 할당

	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	ctrlButtonConnect.EnableWindow(FALSE);
	CWinThread* pThread = AfxBeginThread(recvThread, this);

	return 0;
}


void CSocketChatClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE IPfirst, IPSecond, IPThird, IPFourth;
	//ctrlIPAddr.SetAddress(htonl(inet_addr("127.0.0.1")));
	ctrlIPAddr.GetAddress(IPfirst, IPSecond, IPThird, IPFourth);
	CString ipAddress;
	ipAddress.Format(_T("%d.%d.%d.%d"), IPfirst, IPSecond, IPThird, IPFourth);

	if (IPfirst == NULL || IPSecond == NULL || IPThird == NULL || IPFourth == NULL)
	{
		AfxMessageBox(_T("Wrong IP Address"));
	}
	//AfxMessageBox(ipAddress);
	InitSocket(ipAddress);
}

void CSocketChatClientDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	SendMessageToServer();
	strEditMsg = _T("");
	UpdateData(FALSE);
}


int CSocketChatClientDlg::SendMessageToServer()
{
	// TODO: 여기에 구현 코드 추가.
	int retval;


	// 데이터 통신에 사용할 변수
	char buf[BUFFERSIZE];
	CString bufString;
	WCHAR buff[BUFFERSIZE];

	lstrcpyW(buff, strEditNickname + ": " + strEditMsg);
	int len = WideCharToMultiByte(CP_ACP, 0, buff, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, buff, -1, buf, len, NULL, NULL);

	// 서버에 데이터 보내기
	retval = send(
		sock,		//통신 소켓 핸들
		buf,		//보낼 애플리케이션 버퍼
		strlen(buf),// 보낼 데이터 크기
		0			// 대부분 0 or MSG_DONTROUTE나 MSG_OOB를 사용 가능
	);

	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return 0;
	}

	return 0;
}


void CSocketChatClientDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 소켓 닫기
	closesocket(sock);
	WSACleanup();

	CDialogEx::OnOK();
}
