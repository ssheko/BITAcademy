#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)
SOCKET listenSock;

// ���� �Լ� ���� ���
void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // ���� �޼��� ���� �޸𸮸� ���ο��� �Ҵ��϶�
		FORMAT_MESSAGE_FROM_SYSTEM,		// �ü���κ��� ���� �޼����� �����´�
		NULL,
		WSAGetLastError(),				// ���� �ڵ�
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ��� (������ ���� ���)
		(LPTSTR)&pMsg,					// ���� �޼��� outparam
		0, NULL);

	printf("%s\n", pMsg);				// ���� �޼��� ���

	LocalFree(pMsg);					// ���� �޼��� ���� �޸� ��ȯ
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

	// �ͺ��ŷ �������� �ٲ۴�.
	u_long on = 1;
	retval = ioctlsocket(listenSock, FIONBIO, &on);
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

//��� ������
unsigned int WINAPI ComThread(void* pParam)
{
	SOCKET clientSock = (SOCKET)pParam;
	int recvByte;
	char buf[BUFFERSIZE];
	SOCKADDR_IN clientaddr;

	while (1)
	{
		// ������ �ޱ�
		recvByte = recv(clientSock, buf, BUFFERSIZE, 0);
		if (recvByte == SOCKET_ERROR)
		{ 
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				//���� ������ ����
				DisplayMessage();
				break;
			}
			// �ͺ��ŷ ���� recv()�� ������ �Ϸ���� ����.
		}
		else if (recvByte == 0)
		{ //���� ���� ����
			printf("���� ���� ����");
			//DisplayMessage();
			break;
		}
		else
		{
			int addrlen = sizeof(clientaddr);
			int retval = getpeername(clientSock,
				(SOCKADDR *)&clientaddr, &addrlen);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				continue;
			}
			// ���� ������ ���
			buf[recvByte] = '\0';
			printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port),
				buf);

			// Ŭ���̾�Ʈ�� ������ �����ϱ�
			retval = send(clientSock, buf, recvByte, 0);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
		}
	}
	// ��� ���� �ݱ�
	closesocket(clientSock);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port));
	return 0;
}

//��� ������
unsigned int __stdcall ListenThread(void* pParam)
{
	while (1)
	{
		SOCKET clientSock;
		SOCKADDR_IN clientaddr;
		int addrlen;
		addrlen = sizeof(clientaddr);

		// ���� ���
		clientSock = accept(listenSock, (SOCKADDR *)&clientaddr, &addrlen);
		if (clientSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				DisplayMessage();
			}
			// �ͺ��ŷ ���� accept()�� ������ �Ϸ���� ����.
			continue;
		}

		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));



		// Ŭ���̾�Ʈ�� �������� ����� ���� Thread ����
		// ���� ���� Ŭ���̾�Ʈ ����ŭ ������ ����
		// ������ ����, ���� ��� ������� �߻�. ���� ���� ������ ���� ���ٸ� �̸� ����ϸ� �ȵ�.
		unsigned int threadID;
		// ������ ���� �� �� �ڵ��� �ݾ��ְڴ�. �ڵ� ������ �ݾ��ֱ�.
		CloseHandle((HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0,
			&threadID));
	}
	// ��� ���� �ݱ�
	closesocket(listenSock);
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
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}