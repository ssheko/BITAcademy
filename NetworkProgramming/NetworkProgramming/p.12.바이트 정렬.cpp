#include <WinSock2.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}

	unsigned short us = 0x1234;
	unsigned long ul = 0x12345678;

	// ȣ��Ʈ ����Ʈ�� ��Ʈ��ũ ����Ʈ�� ��ȯ
	printf("0x%09x = > 0x%08x\n", us, htons(us));	// host to network, short type
	printf("0x%09x = > 0x%08x\n", ul, htonl(ul));	// host to network, long type

	unsigned short n_us = htons(us);
	unsigned long n_ul = htonl(ul);

	// ��Ʈ��ũ ����Ʈ�� ȣ��Ʈ ����Ʈ�� ��ȯ
	printf("0x%09x = > 0x%08x\n", n_us, htons(n_us));	// host to network, short type
	printf("0x%09x = > 0x%08x\n", n_ul, htonl(n_ul));	// host to network, long type

	WSACleanup();
	return 0;
}