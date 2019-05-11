#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	// ���� ������ ���Ű� �۽��� ���ÿ� �Ͼ�� �ʱ� ������ �ϳ��� WSAOVERLAPPED ����ü�� ����� �� �ִ�.\
		���� ��, ������ ���������� �����ؾ� �Ѵٸ� ���������� �����ϴ� �񵿱� ������� �� ���̹Ƿ�\
		��, ���� ������ WSAOVERLAPPED ����ü�� ����ؾ� �Ѵ�.
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

SOCKET listenSock;	// ��� ���� �ڵ�

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


unsigned int WINAPI WorkerThread(void* pParam)
{
	HANDLE hcp = (HANDLE)pParam;
	int retval;

	while (1) {
		// �񵿱� ����� �Ϸ� ��ٸ���
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO *ptr;
		retval = GetQueuedCompletionStatus(hcp, // IOCP�� �ڵ�
			&cbTransferred,						// ����� �Ϸ��� ����Ʈ ��
			(LPDWORD)&client_sock,				// IOCP ����� �۾��� �����ϴ� key��. ���ϰ� IOCP�� ������ �� ���� �ڵ��� ���������Ƿ� ������� �Ϸ��� ���� �ڵ��� out parameter�� ��ȯ�ȴ�.
			(LPOVERLAPPED *)&ptr,				// WSAOVERLAPPED�� �ּ�. �������� ����ü�� ���� ��ȯ�Ǿ� ����.
			INFINITE);							// ����� �۾��� �Ϸ��� ������ �����尡 ������ ���.

		// Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);


		if (retval == 0 || cbTransferred == 0) {
			if (retval == 0) {
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock,
					&(ptr->overlapped), &temp1, FALSE, &temp2);
				DisplayMessage();
			}
			closesocket(ptr->sock);
			printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			delete ptr;
			continue;
		}

		// �������� ��, ������ �Ϸ�Ǿ��� �� ���� �ۼ��� ó���ϴ� �κ�\
			�Ϸ� ��ƾ�� ũ�� �ٸ��� ����.			
		// ������ ���۷� ����
		if (ptr->recvbytes == 0) {
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;

			// ���� ������ ���
			ptr->buf[ptr->recvbytes] = '\0';
			printf("[TCP/%s:%d] %s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port), ptr->buf);
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
			retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
				0, &(ptr->overlapped), NULL);	// ������ �μ��� �Ϸ� ��ƾ �ݹ� �Լ��� �������� �ʴ´�.
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					DisplayMessage();
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
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
				&flags, &(ptr->overlapped), NULL);	// ������ �μ��� �Ϸ� ��ƾ �ݹ� �Լ��� �������� �ʴ´�.
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					DisplayMessage();
				}
				continue;
			}
		}
	}
	return 0;
}


bool CreateListenSocket()
{
	int retval;
	// ��� ���� ����
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return false;
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
		return false;
	}
	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}


int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}

	// ����� �Ϸ� ��Ʈ ����
	HANDLE hcp = CreateIoCompletionPort(	// IOCP ��ü ����. �����ϸ� IOCP �ڵ�(hcp) ��ȯ
		INVALID_HANDLE_VALUE,				// ù �μ��� INVALID_HANDLE_VALUE ����
		NULL, 0, 0);
	if (hcp == NULL) return -1;

	// CPU ���� Ȯ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// �۾��� ������ ����
	HANDLE hThread;
	unsigned int ThreadId;
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++)
	{
		// �ý��� ������ �о�� CPU(�ھ�) ������ �� �踸ŭ �Ϸ� �۾��� ó���ϴ� WorkerThread ����.\
			�Ϸ� �۾��� ó���ϴ� �����尡 CPU�� �� ���϶� IOCP�� ������ �پ��.\
			IOCP�� �Ϸ� ��ƾ�� �ٸ��� IOCP�� �ڵ鸸 �˰� ������ � ��������� IOCP�� ����� �Ϸ� ���� ó�� ����.
		hThread = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, (void*)hcp, 0,
			&ThreadId);
		if (hThread == NULL) return -1;
		CloseHandle(hThread);
	}

	if (!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}
	
	while (1) {
		int retval;
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		SOCKET client_sock = accept(listenSock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			DisplayMessage();
			continue;
		}
		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		// ���ϰ� ����� �Ϸ� ��Ʈ ����
		HANDLE hResult = CreateIoCompletionPort((HANDLE)client_sock, hcp,
			(DWORD)client_sock, 0);
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

		// wsabuf.buf�� buffer�� �����͸� ���� �� ����. ���� buffer�� �ٷ� wsabuf.buf�� ���� �� �ִ� ������ �� �� ����.\
			char �迭 buffer�� ���� �� �� �ּҰ��� wsabuf.buf�� ������� ��.
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;


		// �񵿱� ����� ����
		DWORD recvbytes;
		DWORD flags = 0;
		// �񵿱��Լ� WSARecv
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				//���� ������ ����
				DisplayMessage();
			}
			continue;
		}
	}
	WSACleanup();
	return 0;
}

