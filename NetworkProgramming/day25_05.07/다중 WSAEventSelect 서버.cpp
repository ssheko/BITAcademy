
// MyClientMFCDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MyClientMFC.h"
#include "MyClientMFCDlg.h"
#include "afxdialogex.h"
#include "CConnectSocket.h"
#include<process.h>

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


// CMyClientMFCDlg 대화 상자


CMyClientMFCDlg::CMyClientMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCLIENTMFC_DIALOG, pParent)
	, edit_str_input(_T(""))
	, input_str_id(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyClientMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, edit_str_input);
	DDX_Control(pDX, IDC_LIST1, list_msg_list);
	DDX_Control(pDX, IDC_IPADDRESS1, ip_address);
	DDX_Text(pDX, IDC_EDIT2, input_str_id);
}

BEGIN_MESSAGE_MAP(CMyClientMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMyClientMFCDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_IDOK, &CMyClientMFCDlg::OnBnClickedButtonIdok)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CMyClientMFCDlg::OnBnClickedButtonCon)
	ON_BN_CLICKED(IDC_BUTTON_inputOK, &CMyClientMFCDlg::OnBnClickedButtoninputok)
END_MESSAGE_MAP()


// CMyClientMFCDlg 메시지 처리기

BOOL CMyClientMFCDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);         // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);      // 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	if (!CMyClientMFCDlg::m_Socket.Create())
		AfxMessageBox(_T("Create() 오류"));


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyClientMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyClientMFCDlg::OnPaint()
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
HCURSOR CMyClientMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyClientMFCDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CMyClientMFCDlg::m_Socket.OnSend(userName + L": " + edit_str_input);
	edit_str_input = _T("");
	UpdateData(FALSE);
}


void CMyClientMFCDlg::OnBnClickedButtonIdok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Socket.OnSend(L"*" + userName + L"님이 퇴장하셨습니다.*");
	m_Socket.OnClose();
	OnOK();
}


void CMyClientMFCDlg::OnBnClickedButtonCon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD address;
	ip_address.GetAddress(address);
	if (!m_Socket.Connect(address, 40100))
		AfxMessageBox(_T("Connect() 오류"));
	else {
		AfxMessageBox(_T("Connect() 성공"));
		ip_address.SetAddress(0); //버튼 비활성화로 바꾸기
		CWinThread* pThread = AfxBeginThread(recvThread, this);
	}
}

UINT CMyClientMFCDlg::recvThread(void* arg) {
	CMyClientMFCDlg* thisContext = (CMyClientMFCDlg*)arg;
	while (!thisContext->m_bClosedByEndDialog) {
		thisContext->m_Socket.OnReceive();
	}
	return 0;
}

void CMyClientMFCDlg::OnBnClickedButtoninputok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	userName = input_str_id;
	m_Socket.OnSend(L"*" + userName + L"님이 입장하셨습니다.*");
	input_str_id = _T(""); //버튼 비활성화로 바꾸기
	UpdateData(FALSE);
}



#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define BUFSIZE 512
#pragma warning(disable:4996)
using namespace std;


// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	OVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

// 소켓 입출력 함수
DWORD WINAPI WorkerThread(LPVOID arg);
vector<SOCKETINFO*> socket_array;

// 오류 출력 함수
void err_quit(const char *msg);
void err_display(const char *msg);

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// 입출력 완료 포트 생성
	HANDLE hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hcp == NULL) return -1;

	// CPU 개수 확인
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU 개수 * 2)개의 작업자 스레드 생성
	HANDLE hThread;
	DWORD ThreadId;
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++) {
		hThread = CreateThread(NULL, 0, WorkerThread, hcp, 0, &ThreadId);
		if (hThread == NULL) return -1;
		CloseHandle(hThread);
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");


	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	while (1)

	{
		// accept()
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		SOCKET client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			continue;
		}
		printf("[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// 소켓과 입출력 완료 포트 연결
		HANDLE hResult = CreateIoCompletionPort((HANDLE)client_sock, hcp, (DWORD)client_sock, 0);
		if (hResult == NULL) return -1;

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
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;


		// 비동기 입출력 시작
		DWORD recvbytes;
		DWORD flags = 0;
		socket_array.push_back(ptr);
		retval = WSARecv(client_sock, &(ptr->wsabuf), 1, &recvbytes, &flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				err_display("WSARecv()");
			}
			continue;
		}
	}
	// 윈속 종료
	WSACleanup();
	return 0;
}


DWORD WINAPI WorkerThread(LPVOID arg)
{
	HANDLE hcp = (HANDLE)arg;
	int retval;
	int currentClient = 0;

	while (1)

	{
		// 비동기 입출력 완료 기다리기
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO *ptr;
		retval = GetQueuedCompletionStatus(hcp, &cbTransferred,
			(LPDWORD)&client_sock, (LPOVERLAPPED *)&ptr, INFINITE);

		// 클라이언트 정보 얻기
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

		for (int i = 0; i < socket_array.size(); i++) {
			if (client_sock == socket_array[i]->sock) {
				currentClient = i;
			}
		}

		// 비동기 입출력 결과 확인
		if (retval == 0 || cbTransferred == 0) {
			if (retval == 0) {
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped), &temp1, FALSE, &temp2);
				err_display("WSAGetOverlappedResult()");
			}

			//종료한 클라이언트 배열에서 삭제
			for (auto it = socket_array.begin(); it != socket_array.end();) {
				if ((*it)->sock == ptr->sock) {
					socket_array.erase(it);
					break;
				}
			}
			closesocket(ptr->sock);
			printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			delete ptr;
			continue;
		}

		// 데이터 전송량 갱신
		if (ptr->recvbytes == 0) {
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;
			// 받은 데이터 출력
			ptr->buf[ptr->recvbytes] = '\0';
			printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
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

			for (int i = 0; i < socket_array.size(); i++) {
				if (i == currentClient)
					continue;
				send(socket_array[i]->sock, ptr->wsabuf.buf, strlen(ptr->wsabuf.buf) + 1, 0);
			}
			retval = WSASend(socket_array[currentClient]->sock, &(ptr->wsabuf), 1, &sendbytes, 0, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					err_display("WSASend()");
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
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes, &flags, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					err_display("WSARecv()");
				}
				continue;
			}
		}
	}
	return 0;
}

// 소켓 함수 오류 출력 후 종료
void err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

// 소켓 함수 오류 출력
void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}



BOOL CConnectSocket::OnReceive() {
	int retval;
	char buf[BUFFERSIZE];
	TCHAR szBuffer[BUFFERSIZE];
	ZeroMemory(buf, sizeof(buf));
	retval = recv(client_sock, buf, sizeof(buf) - 1, 0);
	if (retval == SOCKET_ERROR || retval == 0) {
		DisplayMessage();
		return FALSE;
	}
	buf[retval] = '\0';
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buf, strlen(buf) + 1, szBuffer, BUFFERSIZE);
	CMyClientMFCDlg* pMain = (CMyClientMFCDlg *)AfxGetApp()->m_pMainWnd;
	pMain->list_msg_list.AddString(szBuffer);
	pMain->list_msg_list.SetCurSel(pMain->list_msg_list.GetCount() - 1);
}

BOOL CConnectSocket::OnSend(LPCTSTR lpWBuf) {
	char buf[BUFFERSIZE];
	int len = WideCharToMultiByte(CP_ACP, 0, lpWBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, lpWBuf, -1, buf, len, NULL, NULL);
	int retval = send(
		client_sock,
		buf,
		strlen(buf),
		0
	);
	if (retval == SOCKET_ERROR) {
		DisplayMessage();
		return false;
	}
	return true;
}