#include <winsock2.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)
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

int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}

	// ��� ���� ����
	SOCKET listenSock;
	listenSock = socket(
		AF_INET,		// �ּ�ü��: �������ݸ��� �ּ�ü�� �ٸ�, ���ͳ� ���, IPv4
		SOCK_STREAM,	// �������� ����: TCP/IP ��� ���
		0
	);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	// ��� ������ ���� �ּ�, ��Ʈ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;	// �ּ� ü��
	serveraddr.sin_port = htons(40100);	// ���� ��Ʈ��ȣ
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);	// ���� IP�ּ�
	retval = bind(listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
	retval = listen(
		listenSock,
		SOMAXCONN	// ���Ӵ�� ť�� ũ��
	);				// TCP ���¸� LISTENING ����
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	// ������ ��ſ� ����� ����
	SOCKET clientSock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFFERSIZE];

	while (1) {
		addrlen = sizeof(clientaddr);
		// ���� ���
		// connect �� 3-way handshaking�� �Ϸ�Ǹ� accept�� return�Ǹ鼭 clientSocket ����.
		clientSock = accept(
			listenSock,
			(SOCKADDR*)&clientaddr,	// Ŭ���̾�Ʈ�� ���� out param
			&addrlen				// �ּ� ����ü ������ ũ��, in(ũ�� ����), out(�ʱ�ȭ�� ũ�� ��ȯ) param
		);			// ��ż��� ����: ���� IP, ���� ��Ʈ ����

		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}

		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr),	// ���ڿ��� IP�ּ� ��ȯ
			ntohs(clientaddr.sin_port)		// ��Ʈ��ȣ ��Ʈ��ũ ����Ʈ ������ ȣ��Ʈ ����Ʈ ���ķ� ��ȯ
		);


		// Ŭ���̾�Ʈ�� ������ ���
		while (1)
		{
			// ������ �ޱ�
			retval = recv(
				clientSock,		// ��ż����ڵ�
				buf,			// ���� ���ø����̼� ����
				BUFFERSIZE,		// ���� ������ �ִ� ũ��
				0				// ��κ� 0 or MSG_PEEK�� MSG_OOB�� ��� ����
			);

			if (retval == SOCKET_ERROR)
			{
				// ���� ������ ����
				DisplayMessage();
				break;
			}
			else if (retval == 0)
			{
				// ���� ���� ����
				DisplayMessage();
				break;
			}
			else {
				// ���� ������ ���
				buf[retval] = '\0';
				printf("[TCP ����] IP �ּ�=%s, ��Ʈ ��ȣ=%d�� ���� �޼���:%s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					buf
				);
			}
		}

		// ��� ���� �ݱ�
		closesocket(clientSock);
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d�� ���� �޼���:%s\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port),
			buf
		);
	}

	// ��� ���� �ݱ�
	closesocket(listenSock);

	WSACleanup();
	return 0;
}