
// SocketChatServerDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SocketChatServer.h"
#include "SocketChatServerDlg.h"
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


// CSocketChatServerDlg 대화 상자



CSocketChatServerDlg::CSocketChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKETCHATSERVER_DIALOG, pParent)
	, m_portNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_portNum);
	DDX_Control(pDX, IDC_LIST_LOG, m_loglist);
}

BEGIN_MESSAGE_MAP(CSocketChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_START, &CSocketChatServerDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	/* 에코 서버는 수신과 송신이 동시에 일어나지 않기 때문에 하나의 WSAOVERLAPPED 구조체를 사용할 수 있다.\
		만약 송, 수신을 독립적으로 수행해야 한다면 독립적으로 동작하는 비동기 입출력이 두 개이므로\
		송, 수신 각각의 WSAOVERLAPPED 구조체를 사용해야 한다.
		*/
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};


// CSocketChatServerDlg 메시지 처리기

BOOL CSocketChatServerDlg::OnInitDialog()
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
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		//printf("윈도우 소켓 초기화 실패\n");
		m_loglist.InsertString(-1, _T("윈도우 소켓 초기화 실패"));
		return FALSE;
	}

	// 입출력 완료 포트 생성
	HANDLE hcp = CreateIoCompletionPort(	// IOCP 객체 생성. 성공하면 IOCP 핸들(hcp) 반환
		INVALID_HANDLE_VALUE,				// 첫 인수로 INVALID_HANDLE_VALUE 지정
		NULL, 0, 0);
	if (hcp == NULL) return -1;

	// CPU 개수 확인
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// 작업자 스레드 생성
	HANDLE hThread;
	unsigned int ThreadId;

	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++)
	{
		// 시스템 정보를 읽어와 CPU(코어) 개수의 두 배만큼 완료 작업을 처리하는 WorkerThread 생성.\
			완료 작업을 처리하는 쓰레드가 CPU의 두 배일때 IOCP의 성능이 뛰어나다.\
			IOCP는 완료 루틴과 다르게 IOCP의 핸들만 알고 있으면 어떤 쓰레드든지 IOCP의 입출력 완료 정보 처리 가능.

		CWinThread* th = AfxBeginThread(WorkerThread, this);
		if (th == NULL) return -1;
		CloseHandle(hThread);
	}

	if (!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSocketChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocketChatServerDlg::OnPaint()
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
HCURSOR CSocketChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketChatServerDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_portNum;

	UpdateData(FALSE);
}


bool CSocketChatServerDlg::CreateListenSocket()
{
	// TODO: 여기에 구현 코드 추가.
	int retval;
	// 대기 소켓 생성
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return false;
	}

	// 대기 소켓의 로컬 주소, 포트 설정
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listenSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	// 대기 소켓의 접속 대기 큐 생성 및 클라이언트 접속 대기
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}


void CSocketChatServerDlg::DisplayMessage()
{
	// TODO: 여기에 구현 코드 추가.
	LPVOID pMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg,
		0, NULL
	);

	m_loglist.InsertString(-1, (LPTSTR)pMsg);
	LocalFree(pMsg);
}


void CSocketChatServerDlg::ConnectClient()
{
	// TODO: 여기에 구현 코드 추가.
	while (1) {
		int retval;
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		SOCKET client_sock = accept(listenSock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			DisplayMessage();
			continue;
		}
		printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		// 소켓과 입출력 완료 포트 연결
		HANDLE hResult = CreateIoCompletionPort((HANDLE)client_sock, hcp,
			(DWORD)client_sock, 0);
		if (hResult == NULL) return;

		// 소켓 정보 구조체 할당
		SOCKETINFO *ptr = new SOCKETINFO;
		if (ptr == NULL) {
			printf("[오류] 메모리가 부족합니다!\n");
			break;
		}

		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->sock = client_sock;
		ptr->recvbytes = 0;
		ptr->sendbytes = 0;

		// wsabuf.buf는 buffer의 포인터만 받을 수 있음. 따라서 buffer를 바로 wsabuf.buf로 받을 수 있는 구조가 될 수 없다.\
			char 배열 buffer를 만든 후 그 주소값을 wsabuf.buf로 보내줘야 함.
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;


		// 비동기 입출력 시작
		DWORD recvbytes;
		DWORD flags = 0;
		// 비동기함수 WSARecv
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				//소켓 비정상 종료
				DisplayMessage();
			}
			continue;
		}
	}
	WSACleanup();
}


UINT WorkerThread(LPVOID pParam)
{
	// TODO: 여기에 구현 코드 추가.
	HANDLE hcp = (HANDLE)pParam;
	int retval;

	while (1) {
		// 비동기 입출력 완료 기다리기
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO *ptr;
		retval = GetQueuedCompletionStatus(hcp, // IOCP의 핸들
			&cbTransferred,						// 입출력 완료한 바이트 수
			(LPDWORD)&client_sock,				// IOCP 입출력 작업을 구분하는 key값. 소켓과 IOCP를 연결할 때 소켓 핸들을 지정했으므로 입출력을 완료한 소켓 핸들이 out parameter로 반환된다.
			(LPOVERLAPPED *)&ptr,				// WSAOVERLAPPED의 주소. 소켓정보 구조체로 형식 변환되어 사용됨.
			INFINITE);							// 입출력 작업이 완료할 때까지 쓰레드가 무한정 대기.

		// 클라이언트 정보 얻기
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);


		if (retval == 0 || cbTransferred == 0) {
			if (retval == 0) {
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock,
					&(ptr->overlapped), &temp1, FALSE, &temp2);
				CSocketChatServerDlg dlg;
				dlg.DisplayMessage();
			}
			closesocket(ptr->sock);
			//printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
			//	inet_ntoa(clientaddr.sin_addr),
			//	ntohs(clientaddr.sin_port));
			CString msg;
			msg.Format(_T("[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n"),
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			delete ptr;
			continue;
		}

		// 데이터의 송, 수신이 완료되었을 때 에코 작성을 처리하는 부분\
			완료 루틴과 크게 다르지 않음.			
		// 데이터 전송량 갱신
		if (ptr->recvbytes == 0) {
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;

			// 받은 데이터 출력
			//ptr->buf[ptr->recvbytes] = '\0';
			//printf("[TCP/%s:%d] %s\n",
			//	inet_ntoa(clientaddr.sin_addr),
			//	ntohs(clientaddr.sin_port), ptr->buf);
			CString msg;
			msg.Format(_T("[TCP/%s:%d] %s"),
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port), ptr->buf);
		}
		else {
			ptr->sendbytes += cbTransferred;
		}

		if (ptr->recvbytes > ptr->sendbytes) {
			// 데이터 보내기
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf + ptr->sendbytes;
			ptr->wsabuf.len = ptr->recvbytes - ptr->sendbytes;

			DWORD sendbytes;
			retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
				0, &(ptr->overlapped), NULL);	// 마지막 인수로 완료 루틴 콜백 함수를 지정하지 않는다.
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					CSocketChatServerDlg dlg;
					dlg.DisplayMessage();
				}
				continue;
			}
		}
		else {
			ptr->recvbytes = 0;

			// 데이터 받기
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFSIZE;

			DWORD recvbytes;
			DWORD flags = 0;
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
				&flags, &(ptr->overlapped), NULL);	// 마지막 인수로 완료 루틴 콜백 함수를 지정하지 않는다.
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					CSocketChatServerDlg dlg;
					dlg.DisplayMessage();
				}
				continue;
			}
		}
	}
	return 0;
}


void CSocketChatServerDlg::SetLogList(LPTSTR logMsg)
{
	// TODO: 여기에 구현 코드 추가.
	m_loglist.InsertString(-1, logMsg);
}
