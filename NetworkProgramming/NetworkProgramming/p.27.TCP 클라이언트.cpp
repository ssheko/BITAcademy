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

	// Ŭ���̾�Ʈ ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// ������ ���� ��û
	retval = connect(
		sock,	// ���� �ڵ�
		(SOCKADDR *)&serveraddr,	//���� ���� �ּҰ�
		sizeof(serveraddr)			// �ּҰ� ũ��
	);	// ��� ����(�����ϸ� �ڵ����� ������Ʈ, �����ּҸ� �Ҵ�

	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	// ������ ��ſ� ����� ����
	char buf[BUFFERSIZE];
	int len;

	// ������ ������ ���
	while (1)
	{
		// ������ �Է�
		ZeroMemory(buf, sizeof(buf));
		printf("[���ڿ� �Է�] ");
		if (fgets(buf, BUFFERSIZE, stdin) == NULL)
			break;

		// '\n' ���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';

		if (strlen(buf) == 0)
			break;

		// ������ ������ ������
		retval = send(
			sock,		//��� ���� �ڵ�
			buf,		//���� ���ø����̼� ����
			strlen(buf),// ���� ������ ũ��
			0			// ��κ� 0 or MSG_DONTROUTE�� MSG_OOB�� ��� ����
		);

		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}

		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ����\n", retval);
	}

	// ���� �ݱ�
	closesocket(sock);

	WSACleanup();
	return 0;
}