#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
};

SOCKET listenSock;	// ��� ���� �ڵ�
int nTotalSockets = 0;	// ��� ������ ����

// ���� ������ Ŀ�� �̺�Ʈ ������ �����ϱ� ���� �迭�� '���̺� ����' ����� ����� ������ ���� Ȯ��.\
	���̺� ������ ���� �ϳ��� ����ü�� ���� �� �ִ� �������� ���� ���������� ��� ������ ������ �� ���Ǵ� ������� �迭�� �ε��� ��ȣ�� ����� ���� ��ġ�� �ε����� ���ü� �ִ� ������ ��Ÿ����.
// ���� ���� ���� �迭
SOCKETINFO *SocketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
// ���� ������ ����Ǵ� Ŀ�� �̺�Ʈ �迭
WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];

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


// ���� ������ �߰��Ѵ�.
BOOL AddSocketInfo(SOCKET sock)
{
	// FD_SETSIZE - ���� ��� ����
	if (nTotalSockets >= (WSA_MAXIMUM_WAIT_EVENTS))
	{
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		return FALSE;
	}

	// ��� ���� ���� ��� ���� ���� ����ü(SOCKETINFO)�� ���� ���� �ڵ鸸 �����ϴ� �뵵�� ���ȴ�.
	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		DisplayMessage();
		return FALSE;
	}


	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets] = ptr;
	EventArray[nTotalSockets] = hEvent;
	nTotalSockets++;

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

	// ������ �ݰ� ���� ���� ��ü�� �����ϰ� Ŀ�� �̺�Ʈ ����.
	closesocket(ptr->sock);
	delete ptr;

	// ���� ���Ͽ� �ش��ϴ� ���� ���� �迭�� Ŀ�� �̺�Ʈ �迭�� ���� ����.
	for (int i = nIndex; i < nTotalSockets; i++) {
		SocketInfoArray[i] = SocketInfoArray[i + 1];
		EventArray[i] = EventArray[i + 1];
	}

	nTotalSockets--;
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
	// ��� ������ SocketInfoArray�� �߰�
	if (AddSocketInfo(listenSock) == FALSE)
		return false;

	// ��� ���ϰ� Ŀ�� �̺�Ʈ ��ü�� �����Ѵ�.
	// FD_ACCEPT�� FD_CLOSE ��Ʈ��ũ �̺�Ʈ�� �߻��ϸ� Ŀ�� �̺�Ʈ ��ü�� ��ȣ���°� �ȴ�.
	retval = WSAEventSelect(listenSock, EventArray[nTotalSockets - 1], FD_ACCEPT | FD_CLOSE);
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

unsigned int WINAPI WorkerThread(void* pParam)
{
	int retval;
	int index;
	WSANETWORKEVENTS NetworkEvents;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	while (1) {
		// �̺�Ʈ ��ü�� ��ȣ���°� �� ������ ���
		// EventArray �迭�� �̺�Ʈ�� nTotalSockets ������ŭ ����ϸ� �� �ϳ��� �̺�Ʈ�� ��ȣ���°� �Ǿ �Լ� ��ȯ.
		index = WSAWaitForMultipleEvents(nTotalSockets, EventArray, 
			FALSE,	// �̺�Ʈ �迭 ���� �ϳ��� �̺�Ʈ�� �߻��ϸ� return���� ��.
			WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			DisplayMessage();
			continue;
		}
		// ��ȯ���� WSA_WAIT_EVENT_0�� ���� �̺�Ʈ�� �߻��� �迭�� �ε��� ��ȣ�� ã�Ƴ�.
		index -= WSA_WAIT_EVENT_0;

		// ��Ʈ��ũ �̺�Ʈ�� �߻��� ������ ������ Ȯ���Ѵ�.
		// ��ȣ ������ ���� �̺�Ʈ�� ���ȣ ���·� �����Ѵ�.
		// �̺�Ʈ �ĺ��ϴ� �Լ�. ���� �̺�Ʈ�� clear����.
		retval = WSAEnumNetworkEvents(SocketInfoArray[index]->sock,
			EventArray[index], // �� ��° �μ��� ������ Ŀ�� �̺�Ʈ�� ���ȣ ���·� �ǵ���.
			&NetworkEvents);	// ���� �߻��� ��� �� ����ü�� ��Ƶ�.
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			return FALSE;
		}

		// FD_ACCEPT �̺�Ʈ ó���� ó���Ѵ�.
		// NetworkEvents.lNetworkEvents & FD_ACCEPT == FD_ACCEPT �ǹ�
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT) {	// NetworkEvents.lNetworkEvents: 4byte long type
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0) {
				DisplayMessage();
				return FALSE;
			}
			addrlen = sizeof(clientaddr);
			client_sock = accept(SocketInfoArray[index]->sock, (SOCKADDR *)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET)
			{
				DisplayMessage();
				return FALSE;
			}


			printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));

			if (nTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
				printf("[����] �� �̻� ������ �޾Ƶ��� �� �����ϴ�!\n");
				closesocket(client_sock);
				continue;
			}

			if (AddSocketInfo(client_sock) == FALSE)
				continue;
			retval = WSAEventSelect(client_sock,
				EventArray[nTotalSockets - 1],
				FD_READ | FD_WRITE | FD_CLOSE);
			if (retval == SOCKET_ERROR) {
				DisplayMessage();
				break;
			}
		}

		// FD_READ, FD_WRITE �̺�Ʈ ó���� ó���Ѵ�.
		if (NetworkEvents.lNetworkEvents & FD_READ
			|| NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			if (NetworkEvents.lNetworkEvents & FD_READ
				&& NetworkEvents.iErrorCode[FD_READ_BIT] != 0) {
				DisplayMessage();
				break;
			}
			if (NetworkEvents.lNetworkEvents & FD_WRITE
				&& NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0) {
				DisplayMessage();
				break;
			}
			SOCKETINFO *ptr = SocketInfoArray[index];

			if (ptr->recvbytes == 0) {
				// ������ �ޱ�
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);

				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//���� ������ ����
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->recvbytes = retval;

				// ���� ������ ���
				ptr->buf[retval] = '\0';
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

				printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					ptr->buf);
			}
			if (ptr->recvbytes > ptr->sendbytes) {
				// ������ ������
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//���� ������ ����
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->sendbytes += retval;

				// ���� �����͸� ��� ���´��� üũ
				if (ptr->recvbytes == ptr->sendbytes)
					ptr->recvbytes = ptr->sendbytes = 0;
			}
		}

		// FD_CLOSE �̺�Ʈ ó��
		if (NetworkEvents.lNetworkEvents & FD_CLOSE) {
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
				DisplayMessage();
			RemoveSocketInfo(index);

		}
	}
	return 0;
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
	unsigned int threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}

