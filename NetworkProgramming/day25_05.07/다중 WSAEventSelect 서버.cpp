
// MyClientMFCDlg.cpp: ���� ����
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



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

 // �����Դϴ�.
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


// CMyClientMFCDlg ��ȭ ����


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


// CMyClientMFCDlg �޽��� ó����

BOOL CMyClientMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);         // ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);      // ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	if (!CMyClientMFCDlg::m_Socket.Create())
		AfxMessageBox(_T("Create() ����"));


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyClientMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMyClientMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyClientMFCDlg::OnBnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	CMyClientMFCDlg::m_Socket.OnSend(userName + L": " + edit_str_input);
	edit_str_input = _T("");
	UpdateData(FALSE);
}


void CMyClientMFCDlg::OnBnClickedButtonIdok()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Socket.OnSend(L"*" + userName + L"���� �����ϼ̽��ϴ�.*");
	m_Socket.OnClose();
	OnOK();
}


void CMyClientMFCDlg::OnBnClickedButtonCon()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DWORD address;
	ip_address.GetAddress(address);
	if (!m_Socket.Connect(address, 40100))
		AfxMessageBox(_T("Connect() ����"));
	else {
		AfxMessageBox(_T("Connect() ����"));
		ip_address.SetAddress(0); //��ư ��Ȱ��ȭ�� �ٲٱ�
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	userName = input_str_id;
	m_Socket.OnSend(L"*" + userName + L"���� �����ϼ̽��ϴ�.*");
	input_str_id = _T(""); //��ư ��Ȱ��ȭ�� �ٲٱ�
	UpdateData(FALSE);
}



#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define BUFSIZE 512
#pragma warning(disable:4996)
using namespace std;


// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	OVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

// ���� ����� �Լ�
DWORD WINAPI WorkerThread(LPVOID arg);
vector<SOCKETINFO*> socket_array;

// ���� ��� �Լ�
void err_quit(const char *msg);
void err_display(const char *msg);

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// ����� �Ϸ� ��Ʈ ����
	HANDLE hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hcp == NULL) return -1;

	// CPU ���� Ȯ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU ���� * 2)���� �۾��� ������ ����
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
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// ���ϰ� ����� �Ϸ� ��Ʈ ����
		HANDLE hResult = CreateIoCompletionPort((HANDLE)client_sock, hcp, (DWORD)client_sock, 0);
		if (hResult == NULL) return -1;

		// ���� ���� ����ü �Ҵ�
		SOCKETINFO *ptr = new SOCKETINFO;
		if (ptr == NULL) {
			printf("[����] �޸𸮰� �����մϴ�!\n");
			break;
		}

		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->sock = client_sock;
		ptr->recvbytes = 0;
		ptr->sendbytes = 0;
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;


		// �񵿱� ����� ����
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
	// ���� ����
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
		// �񵿱� ����� �Ϸ� ��ٸ���
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO *ptr;
		retval = GetQueuedCompletionStatus(hcp, &cbTransferred,
			(LPDWORD)&client_sock, (LPOVERLAPPED *)&ptr, INFINITE);

		// Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

		for (int i = 0; i < socket_array.size(); i++) {
			if (client_sock == socket_array[i]->sock) {
				currentClient = i;
			}
		}

		// �񵿱� ����� ��� Ȯ��
		if (retval == 0 || cbTransferred == 0) {
			if (retval == 0) {
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped), &temp1, FALSE, &temp2);
				err_display("WSAGetOverlappedResult()");
			}

			//������ Ŭ���̾�Ʈ �迭���� ����
			for (auto it = socket_array.begin(); it != socket_array.end();) {
				if ((*it)->sock == ptr->sock) {
					socket_array.erase(it);
					break;
				}
			}
			closesocket(ptr->sock);
			printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			delete ptr;
			continue;
		}

		// ������ ���۷� ����
		if (ptr->recvbytes == 0) {
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;
			// ���� ������ ���
			ptr->buf[ptr->recvbytes] = '\0';
			printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
		}
		else {
			ptr->sendbytes += cbTransferred;
		}

		if (ptr->recvbytes > ptr->sendbytes) {
			// ������ ������
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
			// ������ �ޱ�
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

// ���� �Լ� ���� ��� �� ����
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

// ���� �Լ� ���� ���
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