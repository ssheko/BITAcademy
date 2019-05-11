#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	// overlapped ����ü�� �ּҸ� ����ü�� ������ ���.\
		�񵿱� ����� �Լ��� ������ �μ��� overlapped ����ü�� �ּҰ� �����Ǹ�\
		�Ϸ� ��ƾ�� ȣ��� �� ����� �Լ��� �����ߴ� overlapped ����ü�� �ּҰ� �Ϸ� ��ƾ �ݹ� �Լ��� �� ��° �μ��ε� ���޵ǹǷ�\
		�� �ּҸ� �̿��� ����ü ������ �Ϸ� ��ƾ���� ��� ����Ѵ�.\
		overlapped ����ü�� �ּҸ� ����� �Լ��� �����ϸ� overlapped ����� �ּҴ� �� SOCKETINFO ����ü�� ���� �ּ��̹Ƿ�\
		�Ϸ� ��ƾ���� SOCKETINFO ����ü�� ���� ��ȯ�Ͽ� ��� ����� ������ �� �ִ�.
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

SOCKET listenSock;
SOCKET clientSock;
HANDLE hEvent;

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

// �Ϸ� ��ƾ
void CALLBACK CompletionRoutine(
	DWORD dwError, DWORD cbTransferred,	// ���� ������ byte �� = cbTransferred
	LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	int retval;

	// Ŭ���̾�Ʈ ���� ���
	SOCKETINFO *ptr = (SOCKETINFO*)lpOverlapped;	// heap ������ �ִ� socket info
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

	// �񵿱� ����� ��� Ȯ��
	if (dwError != 0 || cbTransferred == 0) {	// �������� ���� (cbTransferred == 0)
		if (dwError != 0) DisplayMessage();
		closesocket(ptr->sock);
		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
		delete ptr;
		return;
	}

	// ������ ���۷� ����
	if (ptr->recvbytes == 0) {	// �����͸� �����ߴٸ�
		ptr->recvbytes = cbTransferred;
		ptr->sendbytes = 0;
		// ���� ������ ���
		ptr->buf[ptr->recvbytes] = '\0';

		printf("[TCP/%s:%d] %s\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), ptr->buf);
	}
	else {
		// ���� ������ ���
		ptr->sendbytes += cbTransferred;
	}

	if (ptr->recvbytes > ptr->sendbytes) {
		// ������ ������
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf + ptr->sendbytes;
		ptr->wsabuf.len = ptr->recvbytes - ptr->sendbytes;

		DWORD sendbytes;
		// ����� ��ü ���Ͽ� �������� ����
		retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
			0, &(ptr->overlapped), CompletionRoutine);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return;
			}
		}
	}
	else {
		// ���� �����͸� ��� ���´ٸ� recvbytes�� �ʱ�ȭ�ϰ�\
			�ٽ� ������ ������ ���� �񵿱� ����� �Լ� ����
		ptr->recvbytes = 0;

		// ������ �ޱ�
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), CompletionRoutine);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return;
			}
		}
	}
}

// �۾� ������
unsigned int WINAPI WorkerThread(void* pParam)
{
	HANDLE hEvent = (HANDLE)pParam;
	int retval;

	while (1) {
		while (1) {
			// alertable wait\
				�ӽ� Ŀ�� �̺�Ʈ�� ��ȣ ���°� �Ǵ����� (Ŭ���̾�Ʈ ����) �Ǵ��ϰ� �����带 �˸� ���� ���·� ����� �ڵ�� �Ϸ� ��ƾ�� ����Ǹ� ��ȯ�ǰ�\
				WAIT_IO_COMPLETION ���̸� �ٽ� �����带 �˸� ���� ���·� �����.\
				���� WAIT_OBJECT_0�̸� Ŭ���̾�Ʈ�� ���������Ƿ� ������ ���� �ڵ带 �����Ѵ�.
			DWORD result = WaitForSingleObjectEx(hEvent, INFINITE, 
				TRUE);	// alertable state TRUE. �ݹ� �Լ��� ���� �� �ִ� ����.
			if (result == WAIT_OBJECT_0) break;				// Ŭ���̾�Ʈ ����.
			if (result != WAIT_IO_COMPLETION) return -1;	// �����带 �˸� ���� ���·� ����
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(clientSock, (SOCKADDR*)&clientaddr, &addrlen);

		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		// ���� ���� ����ü �Ҵ�� �ʱ�ȭ
		SOCKETINFO *ptr = new SOCKETINFO;
		if (ptr == NULL) {
			printf("[����] �޸𸮰� �����մϴ�!\n");
			return -1;
		}

		// Ŭ���̾�Ʈ�� ���ӵǾ����Ƿ� ������ ���� �޸𸮸� ����
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->sock = clientSock;
		ptr->recvbytes = 0;
		ptr->sendbytes = 0;

		// wsabuf.buf�� buffer�� �����͸� ���� �� ����. ���� buffer�� �ٷ� wsabuf.buf�� ���� �� �ִ� ������ �� �� ����.\
			char �迭 buffer�� ���� �� �� �ּҰ��� wsabuf.buf�� ������� ��.
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		// �񵿱� ����� ���� (������ ������ ����)
		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), 
			CompletionRoutine);	// ����� �۾��� �Ϸ��ϸ� ������ �Ϸ� ��ƾ�� �ݹ� �Լ� �ּ�
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return -1;
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

	// �ӽ� �̺�Ʈ ��ü ����\
		�ӽ� Ŀ�� �̺�Ʈ ��ü�� ������ Ŭ���̾�Ʈ ������ �߻����� �˸��µ� ���
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEvent == NULL) false;

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
	if (!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// ��� ������ ���Ḧ ��ٸ�
	unsigned int threadID;
	CloseHandle((HANDLE)_beginthreadex(0, 0, WorkerThread, (void*)hEvent, 0,
		&threadID));

	// Ŭ���̾�Ʈ ������ ó���ϱ� ���� �ڵ�\
		���� �����忡�� ������ �̿��� accept()�� ó���ϰ�\
		SetEvent(hEvent)�� Ŭ���̾�Ʈ ������ WorkerThread�� �˷� Ŭ���̾�Ʈ ���� ó�� ����.
	while (1) {
		// accept()
		clientSock = accept(listenSock, NULL, NULL);
		if (clientSock == INVALID_SOCKET) {
			DisplayMessage();
			continue;
		}
		if(!SetEvent(hEvent)) break;
	}
	// ���� ����
	WSACleanup();
	return 0;
}

