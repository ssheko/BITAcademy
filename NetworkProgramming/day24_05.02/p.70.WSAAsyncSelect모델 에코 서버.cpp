#include <winsock2.h>
#include <stdio.h>

#define BUFFERSIZE 1024
#define WM_SOCKET (WM_USER +1)

#pragma warning(disable:4996)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvbytes;
	int sendbytes;
	BOOL recvdelayed;
};

HWND hwnd; // �������� �ڵ�
SOCKET listenSock;	// ��� ���� �ڵ�
int nTotalSockets = 0;	// ��� ������ ����
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ���� �Լ� ���� �⼮
void DisplayMessage()
{
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

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

bool CreateListenSocket()
{
	int retval;
	// ��� ���� ����
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return FALSE;
	}
	// ��� ���ϰ� ����� ���� �޼��� WM_SOCKET�� �����Ѵ�.
	// �ͺ��ŷ �������� �����ϴ� �ϵ� ���� �Ѵ�.
	retval = WSAAsyncSelect(listenSock, hwnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return FALSE;
	}

	// ��� ������ ���� �ּ�, ��Ʈ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listenSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return FALSE;
	}
	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return FALSE;
	}
	return TRUE;
}

// ���� ������ �߰��Ѵ�.
BOOL AddSocketInfo(SOCKET sock)
{
	// FD_SETSIZE - ���� ��� ����
	if (nTotalSockets >= (FD_SETSIZE - 1))
	{
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		return FALSE;
	}

	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets++] = ptr;

	return TRUE;
}

// ���� ������ �����Ѵ�
void RemoveSocketInfo(int nIndex)
{
	SOCKETINFO *ptr = SocketInfoArray[nIndex];

	// Ŭ���̾�Ʈ ���� ���
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
	printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port));

	closesocket(ptr->sock);
	delete ptr;

	for (int i = nIndex; i < nTotalSockets; i++) {
		SocketInfoArray[i] = SocketInfoArray[i + 1];
	}

	nTotalSockets--;
}

int GetSocketInfo(SOCKET sock)
{
	for (int i = 0; i < nTotalSockets; ++i)
	{
		if (SocketInfoArray[i]->sock == sock)
			return i;
	}
	return -1;	// Ŭ���̾�Ʈ���� ���� ó�� �ؾ���.
}

int main(int argc, char* argv[])
{
	// ������ Ŭ���� ���
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = NULL;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = "MyWindowClass";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&wndclass)) return -1;

	// ������ ����
	hwnd = CreateWindow("MyWindowClass", "TCP ����", WS_OVERLAPPEDWINDOW, 0, 0, 600, 300,
		NULL, (HMENU)NULL, NULL, NULL);
	if (hwnd == NULL) return -1;
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// ��� ���� �ʱ�ȭ(socket()+bind()+listne())
	if (!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// �޼��� ����
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ���� ����
	WSACleanup();
	return msg.wParam;
}

// ������ �޼��� ó��
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SOCKET:	// ���� ���� ������ �޼���
	{
		// ������ ��ſ� ����� ����
		SOCKETINFO *ptr;
		SOCKET client_sock= NULL;
		SOCKADDR_IN clientaddr;
		int addrlen;
		int retval;

		// ���� �߻� ���� Ȯ��
		if (WSAGETSELECTERROR(lParam))
		{
			RemoveSocketInfo(GetSocketInfo(wParam));
			break;
		}

		// �޼��� ó��
		switch (WSAGETSELECTEVENT(lParam)) {
		case FD_ACCEPT:
			addrlen = sizeof(clientaddr);
			client_sock = accept(wParam, (SOCKADDR *)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					DisplayMessage();
				break;
			}

			printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			AddSocketInfo(client_sock);
			retval = WSAAsyncSelect(client_sock, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				RemoveSocketInfo(GetSocketInfo(client_sock));
			}
			break;

			// Read���ڸ��� write�� echo���༭ break�� �ʿ����.
		case FD_READ:
			ptr = SocketInfoArray[GetSocketInfo(wParam)];
			if (ptr->recvbytes > 0) {
				ptr->recvdelayed = TRUE;
				break;
			}

			// ������ �ޱ�
			retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//���� ������ ����
					DisplayMessage();
					RemoveSocketInfo(GetSocketInfo(wParam));
				}
				break;
			}
			ptr->recvbytes = retval;
			
			// ���� ������ ���
			ptr->buf[retval] = '\0';
			addrlen = sizeof(clientaddr);
			getpeername(wParam, (SOCKADDR *)&clientaddr, &addrlen);

			printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port),
				ptr->buf);

		case FD_WRITE:
			ptr = SocketInfoArray[GetSocketInfo(wParam)];
			if (ptr->recvbytes <= ptr->sendbytes)
				break;

			// ������ ������
			retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//���� ������ ����
					DisplayMessage();
					RemoveSocketInfo(wParam);
				}
				break;
			}
			ptr->sendbytes += retval;

			// ���� �����͸� ��� ���´��� üũ
			if (ptr->recvbytes == ptr->sendbytes) {
				ptr->recvbytes = ptr->sendbytes = 0;
				if (ptr->recvdelayed) {
					ptr->recvdelayed = FALSE;
					PostMessage(hwnd, WM_SOCKET, wParam, FD_READ);
				}
			}
			break;
		case FD_CLOSE:
			RemoveSocketInfo(GetSocketInfo(wParam));
			break;
		}
	}
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}