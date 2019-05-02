#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvbytes;
	int sendbytes;
};

SOCKET listenSock;	// ��� ���� �ڵ�
int nTotalSockets = 0;	// ��� ������ ����
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

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

unsigned int WINAPI WorkerThread(void *pParam)
{
	int retval;
	FD_SET rset;
	FD_SET wset;
	SOCKET clientSock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	while (1)
	{
		// ���� �� �ʱ�ȭ
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		FD_SET(listenSock, &rset);	// ��� ������ rset�� ���
		for (int i = 0; i < nTotalSockets; i++)
		{
			if (SocketInfoArray[i]->recvbytes > SocketInfoArray[i]->sendbytes)
				FD_SET(SocketInfoArray[i]->sock, &wset);
			else
				FD_SET(SocketInfoArray[i]->sock, &rset);
		}

		// select() ���
		retval = select(0, &rset, &wset, NULL, NULL);
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}

		// ��� ���Ͽ� Ŭ���̾�Ʈ ������ ��û�Ǿ���?
		if (FD_ISSET(listenSock, &rset)) {
			addrlen = sizeof(clientaddr);
			clientSock = accept(listenSock, (SOCKADDR *)&clientaddr,
				&addrlen);

			if (retval == INVALID_SOCKET)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//���� ������ ����
					DisplayMessage();
				}
			}
			else {
				printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port));

				// ���� ���� �߰�
				if (AddSocketInfo(clientSock) == FALSE)
				{
					printf("\n[TCP ����] Ŭ���̾�Ʈ ������ �����մϴ�!\n");
					closesocket(clientSock);
				}
			}
		}
		// ������ ��,���� �����Ѱ�?

		for (int i = 0; i < nTotalSockets; i++)
		{
			SOCKETINFO *ptr = SocketInfoArray[i];

			// �����Ͱ� ���� ���ۿ� �����ߴ�.
			if (FD_ISSET(ptr->sock, &rset)) {
				retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//���� ������ ����
						DisplayMessage();
						RemoveSocketInfo(i);
					}
					continue;
				}
				else if (retval == 0) {
					RemoveSocketInfo(i);
					continue;
				}

				ptr->recvbytes = retval;

				// ���� ������ ���
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
				ptr->buf[retval] = '\0';

				printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					ptr->buf);
			}

			// �۽� ���� ���� ������ ���� �����͸� ���� �غ� �Ǿ���.
			if (FD_ISSET(ptr->sock, &wset)) {
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes,
					ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//���� ������ ����
						DisplayMessage();
						RemoveSocketInfo(i);
					}
					continue;
				}
				ptr->sendbytes += retval;
				if (ptr->recvbytes == ptr->sendbytes)
				{
					ptr->recvbytes = ptr->sendbytes = 0;
				}
			}
		}
	}

	// ��� ���� �ݱ�
	closesocket(listenSock);

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
	// ��� ���� �ʱ�ȭ(socket()+bind()+listne())
	if (!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// ��� ������ ���Ḧ ��ٸ�.
	unsigned int threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}

//
//
//#include <WinSock2.h>
//#include <stdio.h>
//#include <process.h>
//#pragma warning(disable:4996)
//#define BUFFERSIZE 1024
//#pragma comment(lib, "ws2_32.lib")
//struct SOCKETINFO {
//	SOCKET sock;
//	char buf[BUFFERSIZE];
//	int recvByte;
//	int sendByte;
//};
//SOCKET listenSock;
//
//int nTotalsockets = 0;
//SOCKETINFO* SocketinfoArray[FD_SETSIZE];
//
//void DisplayMessage()
//{
//	LPVOID pMsg;
//	//�����ڵ�=>���ڿ�
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL,
//		WSAGetLastError(), //�����ڵ�ȹ��
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&pMsg, 0, NULL);
//
//	//MessageBox(0, _TEXT((LPTSTR)pMsg), TEXT("�˸�"), MB_OK);
//	printf("%s\n", pMsg);
//	LocalFree(pMsg);
//}
//
//BOOL CreateListenSocket()
//{
//	int retval;
//	// ��� ���� ����
//	listenSock = socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSock == INVALID_SOCKET)
//	{
//		DisplayMessage();
//		return FALSE;
//	}
//
//	u_long on = 1;
//	retval = ioctlsocket(listenSock, FIONBIO, &on);
//	if (retval == SOCKET_ERROR)
//	{
//		DisplayMessage();
//		return FALSE;
//	}
//	// ��� ������ ���� �ּ�, ��Ʈ ����
//	SOCKADDR_IN serveraddr;
//	ZeroMemory(&serveraddr, sizeof(serveraddr));
//	serveraddr.sin_family = AF_INET;
//	serveraddr.sin_port = htons(40100);
//	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	retval = bind(listenSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR)
//	{
//		DisplayMessage();
//		return FALSE;
//	}
//	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
//	retval = listen(listenSock, SOMAXCONN);
//	if (retval == SOCKET_ERROR)
//	{
//		DisplayMessage();
//		return FALSE;
//	}
//	return TRUE;
//}
//BOOL AddSocketInfo(SOCKET sock)
//{
//	//FD_SETSIZE - ���� ��� ����
//	if (nTotalsockets >= (FD_SETSIZE - 1)) {
//		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
//		return FALSE;
//	}
//
//	SOCKETINFO *ptr = new SOCKETINFO;
//	if (ptr == NULL) {
//		printf("[����] �޸𸮰� �����մϴ�!\n");
//		return FALSE;
//	}
//
//	ptr->sock = sock;
//	ptr->recvByte = 0;
//	ptr->sendByte = 0;
//	SocketinfoArray[nTotalsockets++] = ptr;
//
//	return TRUE;
//}
//void RemoveSocketInfo(int nindex)
//{
//	SOCKETINFO *ptr = SocketinfoArray[nindex];
//
//	//Ŭ���̾�Ʈ ���� ���
//	SOCKADDR_IN clientaddr;
//	int addrlen = sizeof(clientaddr);
//	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
//	printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
//		inet_ntoa(clientaddr.sin_addr),
//		ntohs(clientaddr.sin_port));
//
//	closesocket(ptr->sock);
//	delete ptr;
//
//	for (int i = nindex; i < nTotalsockets; i++)
//	{
//		SocketinfoArray[i] = SocketinfoArray[i + 1];
//	}
//	nTotalsockets--;
//}
//
//unsigned int WINAPI WorkerThread(void *pParam)
//{
//	int retval;
//	FD_SET rset;
//	FD_SET wset;
//	SOCKET clientSock;
//	SOCKADDR_IN clientaddr;
//	int addrlen;
//
//	while (1)
//	{
//		FD_ZERO(&rset);
//		FD_ZERO(&wset);
//		FD_SET(listenSock, &rset);
//		for (int i = 0; i < nTotalsockets; i++)
//		{
//			if (SocketinfoArray[i]->recvByte > SocketinfoArray[i]->sendByte)
//				FD_SET(SocketinfoArray[i]->sock, &wset);
//			else
//				FD_SET(SocketinfoArray[i]->sock, &rset);
//
//			//select ���
//			retval = select(0, &rset, &wset, NULL, NULL);
//			if (retval == SOCKET_ERROR)
//			{
//				DisplayMessage();
//				break;
//			}
//			//��� ���Ͽ� Ŭ���̾�Ʈ ������ ��û�Ǿ���?
//			if (FD_ISSET(listenSock, &rset)) {
//				addrlen = sizeof(clientaddr);
//				clientSock = accept(listenSock, (SOCKADDR*)&clientaddr, &addrlen);
//				if (clientSock == INVALID_SOCKET) {
//					if (WSAGetLastError() != WSAEWOULDBLOCK)
//						DisplayMessage();
//				}
//				else {
//					printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
//						inet_ntoa(clientaddr.sin_addr),
//						ntohs(clientaddr.sin_port));
//					//���� ���� �߰�
//					if (AddSocketInfo(clientSock) == FALSE) {
//						printf("[TCP ����]Ŭ���̾�Ʈ�� ������ �����մϴ�!\n");
//						closesocket(clientSock);
//					}
//				}
//			}
//}
//			//������ �� ������ �����Ѱ�?
//			for (int i = 0; i < nTotalsockets; i++)
//			{
//				SOCKETINFO *ptr = SocketinfoArray[i];
//				//�����Ͱ� ���� ���ۿ� ���� �ߴ�.
//				if (FD_ISSET(ptr->sock, &rset)) {
//					retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
//					if (retval == SOCKET_ERROR) {
//						if (WSAGetLastError() != WSAEWOULDBLOCK)
//						{
//							//���� ������ ����
//							DisplayMessage();
//							RemoveSocketInfo(i);
//						}
//						continue;
//					}
//					else if (retval == 0) {
//						RemoveSocketInfo(i);
//						continue;
//					}
//					ptr->recvByte = retval;
//					//���� ������ ���
//					addrlen = sizeof(clientaddr);
//					getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
//					ptr->buf[retval] = '\0';
//					printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
//						inet_ntoa(clientaddr.sin_addr),
//						ntohs(clientaddr.sin_port),
//						ptr->buf);
//				}
//				//�۽� ���� ���� ������ ���� �����͸� ���� �غ� �Ǿ���.
//				if (FD_ISSET(ptr->sock, &wset)) {
//					retval = send(ptr->sock, ptr->buf + ptr->sendByte, ptr->recvByte - ptr->sendByte, 0);
//					if (retval == SOCKET_ERROR)
//					{
//						if (WSAGetLastError() != WSAEWOULDBLOCK)
//						{
//							//���� ������ ����
//							DisplayMessage();
//							RemoveSocketInfo(i);
//						}
//						continue;
//					}
//					ptr->sendByte += retval;
//					if (ptr->recvByte == ptr->sendByte) {
//						ptr->recvByte = ptr->sendByte = 0;
//					}
//				}
//			}
//		
//		closesocket(listenSock);
//		return 0;
//	}
//}
////��� ������
//unsigned int WINAPI ComThread(void* pParam)
//{
//	SOCKET clientSock = (SOCKET)pParam;
//	int recvByte;
//	char buf[BUFFERSIZE];
//	SOCKADDR_IN clientaddr;
//
//	while (1)
//	{
//		// ������ �ޱ�
//		recvByte = recv(clientSock, buf, BUFFERSIZE, 0);
//
//		if (recvByte == SOCKET_ERROR) {
//			if (WSAGetLastError() != WSAEWOULDBLOCK)
//			{
//				//���� ������ ����
//				DisplayMessage();
//				break;
//			}
//		}
//		//�� ���ŷ ���� recv()�� ������ �Ϸ���� ����.
//		else if (recvByte == 0)
//		{ //���� ���� ����
//			printf("���� ���� ����");
//			//DisplayMessage();
//			break;
//		}
//		else
//		{
//			int addrlen = sizeof(clientaddr);
//			int retval = getpeername(clientSock,
//				(SOCKADDR *)&clientaddr, &addrlen);
//			if (retval == SOCKET_ERROR)
//			{
//				DisplayMessage();
//				continue;
//			}
//			// ���� ������ ���
//			buf[recvByte] = '\0';
//			printf("[TCP����] IP = %s, Port = %d�� �޽��� : %s\n",
//				inet_ntoa(clientaddr.sin_addr),
//				ntohs(clientaddr.sin_port),
//				buf);
//
//			// ��� Ŭ���̾�Ʈ�� ������ �����ϱ�
//			retval = send(clientSock, buf, recvByte, 0);
//			if (retval == SOCKET_ERROR)
//			{
//				DisplayMessage();
//				break;
//			}
//		}
//	}
//	// ��� ���� �ݱ�
//	closesocket(clientSock);
//
//	printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
//		inet_ntoa(clientaddr.sin_addr),
//		ntohs(clientaddr.sin_port));
//	return 0;
//}
//
////��� ������
//unsigned int __stdcall ListenThread(void* pParam)
//{
//	while (1)
//	{
//		SOCKET clientSock;
//		SOCKADDR_IN clientaddr;
//		int addrlen;
//		addrlen = sizeof(clientaddr);
//		// ���� ���
//		clientSock = accept(listenSock, (SOCKADDR *)&clientaddr, &addrlen);
//		if (clientSock == INVALID_SOCKET)
//		{
//			if (WSAGetLastError() != WSAEWOULDBLOCK)
//			{
//				DisplayMessage();
//				//�� ���ŷ ���� accept()�� ������ �Ϸ���� ����
//			}
//			continue;
//		}
//
//		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n",
//			inet_ntoa(clientaddr.sin_addr),
//			ntohs(clientaddr.sin_port));
//
//
//
//		// Ŭ���̾�Ʈ�� �������� ����� ���� Thread ����
//		unsigned int threadID;
//		CloseHandle((HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0,
//			&threadID));
//	}
//	// ��� ���� �ݱ�
//	closesocket(listenSock);
//}
//
//int main(int argc, char* argv[])
//{
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		printf("������ ���� �ʱ�ȭ ����\n");
//		return -1;
//	}
//	if (!CreateListenSocket())
//	{
//		printf("��� ���� ���� ����\n");
//		return -1;
//	}
//	unsigned int threadID;
//	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
//	WSACleanup();
//	return 0;
//}