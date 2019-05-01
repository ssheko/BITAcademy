//#include <winsock2.h>
//#include <process.h>
//#include <stdio.h>
//
//#define BUFFERSIZE 1024
//
//#pragma warning(disable:4996)
//
//SOCKET listenSock;
//
//// ���� �Լ� ���� ���
//void DisplayMessage()
//{
//	LPVOID pMsg;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | // ���� �޼��� ���� �޸𸮸� ���ο��� �Ҵ��϶�
//		FORMAT_MESSAGE_FROM_SYSTEM,		// �ü���κ��� ���� �޼����� �����´�
//		NULL,
//		WSAGetLastError(),				// ���� �ڵ�
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ��� (������ ���� ���)
//		(LPTSTR)&pMsg,					// ���� �޼��� outparam
//		0, NULL);
//
//	printf("%s\n", pMsg);				// ���� �޼��� ���
//
//	LocalFree(pMsg);					// ���� �޼��� ���� �޸� ��ȯ
//}
//
//bool CreateListenSocket()
//{
//
//	int retval;
//
//	// ��� ���� ����
//	listenSock = socket(
//		AF_INET,		// �ּ�ü��: �������ݸ��� �ּ�ü�� �ٸ�, ���ͳ� ���, IPv4
//		SOCK_STREAM,	// �������� ����: TCP/IP ��� ���
//		0
//	);
//	if (listenSock == INVALID_SOCKET)
//	{
//		DisplayMessage();
//		return -1;
//	}
//
//	// ��� ������ ���� �ּ�, ��Ʈ ����
//	SOCKADDR_IN serveraddr;
//	ZeroMemory(&serveraddr, sizeof(serveraddr));
//	serveraddr.sin_family = AF_INET;	// �ּ� ü��
//	serveraddr.sin_port = htons(40100);	// ���� ��Ʈ��ȣ
//	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);	// ���� IP�ּ�
//	retval = bind(listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR)
//	{
//		DisplayMessage();
//		return false;
//	}
//
//	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
//	retval = listen(
//		listenSock,
//		SOMAXCONN	// ���Ӵ�� ť�� ũ��
//	);				// TCP ���¸� LISTENING ����
//	if (retval == SOCKET_ERROR)
//	{
//		DisplayMessage();
//		return false;
//	}
//
//	return true;
//}
//
//
//unsigned int WINAPI ComThread(void* pParam)
//{
//
//	// ������ ��ſ� ����� ����
//	SOCKET clientSock = (SOCKET) pParam;
//	SOCKADDR_IN clientaddr;
//	int recvByte;
//	char buf[BUFFERSIZE];
//
//	while (1) {
//		// ������ �ޱ�
//		recvByte = recv(
//			clientSock,		// ��ż����ڵ�
//			buf,			// ���� ���ø����̼� ����
//			BUFFERSIZE,		// ���� ������ �ִ� ũ��
//			0				// ��κ� 0 or MSG_PEEK�� MSG_OOB�� ��� ����
//		);
//
//		if (recvByte == SOCKET_ERROR)
//		{
//			// ���� ������ ����
//			DisplayMessage();
//			break;
//		}
//		else if (recvByte == 0)
//		{
//			// ���� ���� ����
//			//DisplayMessage();
//			break;
//		}
//		else {
//			// ���� ������ ���
//			int addrlen = sizeof(clientaddr);
//			int retval = getpeername(clientSock, (SOCKADDR *)&clientaddr, &addrlen);
//			if (retval == SOCKET_ERROR)
//			{
//				// ���� ������ ����
//				DisplayMessage();
//				break;
//			}
//			buf[retval] = '\0';
//			printf("[TCP ����] IP=%s, Port=%d�� �޼���:%s\n",
//				inet_ntoa(clientaddr.sin_addr),
//				ntohs(clientaddr.sin_port),
//				buf
//			);
//			// Ŭ���̾�Ʈ�� ������ �����ϱ�
//			retval = send(clientSock, buf, recvByte, 0);
//			if (retval == SOCKET_ERROR)
//			{
//				// ���� ������ ����
//				DisplayMessage();
//				break;
//			}
//		}
//	}
//	// ��� ���� �ݱ�
//	closesocket(clientSock);
//	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
//		inet_ntoa(clientaddr.sin_addr),
//		ntohs(clientaddr.sin_port)
//	);
//
//	return 0;
//}
//
//unsigned int WINAPI ListenThread(void* pParam)
//{
//
//	while (1) {
//		SOCKET clientSock;
//		SOCKADDR_IN clientaddr;
//		int addrlen;
//		addrlen = sizeof(clientaddr);
//		// ���� ���
//		// connect �� 3-way handshaking�� �Ϸ�Ǹ� accept�� return�Ǹ鼭 clientSocket ����.
//		clientSock = accept(
//			listenSock,
//			(SOCKADDR*)&clientaddr,	// Ŭ���̾�Ʈ�� ���� out param
//			&addrlen				// �ּ� ����ü ������ ũ��, in(ũ�� ����), out(�ʱ�ȭ�� ũ�� ��ȯ) param
//		);			// ��ż��� ����: ���� IP, ���� ��Ʈ ����
//
//		if (clientSock == INVALID_SOCKET)
//		{
//			DisplayMessage();
//			continue;
//		}
//
//		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
//			inet_ntoa(clientaddr.sin_addr),	// ���ڿ��� IP�ּ� ��ȯ
//			ntohs(clientaddr.sin_port)		// ��Ʈ��ȣ ��Ʈ��ũ ����Ʈ ������ ȣ��Ʈ ����Ʈ ���ķ� ��ȯ
//		);
//
//		// Ŭ���̾�Ʈ�� �������� ����� ���� Thread ����
//		unsigned int threadID;
//		CloseHandle((HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0, &threadID));
//	}
//
//	// ��� ���� �ݱ�
//	closesocket(listenSock);
//}
//
//int main(int argc, char* argv[])
//{
//	WSADATA wsa;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		printf("������ ���� �ʱ�ȭ ����\n");
//		return -1;
//	}
//
//	// ��� ���� �ʱ�ȭ (socket()+bind()+listen())
//	if (!CreateListenSocket())
//	{
//		printf("������ ���� �ʱ�ȭ ����\n");
//		return -1;
//	}
//	// ��� ������ ���Ḧ ��ٸ�
//	unsigned int threadID;
//	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0, &threadID), INFINITE);
//
//	WSACleanup();
//	return 0;
//}

#include <WinSock2.h>
#include <stdio.h>
#include <process.h>
#pragma warning(disable:4996)
#define BUFFERSIZE 1024
#pragma comment(lib, "ws2_32.lib")
SOCKET listenSock;

void DisplayMessage()
{
	LPVOID pMsg;
	//�����ڵ�=>���ڿ�
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),   //�����ڵ�ȹ��
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg, 0, NULL);

	//MessageBox(0, _TEXT((LPTSTR)pMsg), TEXT("�˸�"), MB_OK);
	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

BOOL CreateListenSocket()
{
	int retval;
	// ��� ���� ����
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
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
		{ //���� ������ ����
			DisplayMessage();
			break;
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

			// ��� Ŭ���̾�Ʈ�� ������ �����ϱ�
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
			DisplayMessage();
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

