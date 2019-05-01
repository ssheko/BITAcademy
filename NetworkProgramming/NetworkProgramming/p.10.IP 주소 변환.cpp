#include <WinSock2.h>
#include <stdio.h>

#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}

	// ���ڿ� �ּ� ���
	const char *ipaddr = "230.200.12.5";
	printf("IP ���ڿ� �ּ� : %s\n", ipaddr);

	// ���ڿ� �ּҸ� 4byte ������ ��ȯ
	printf("IP ���ڿ� �ּ� => ���� = 0x%08x\n", inet_addr(ipaddr));

	// 4byte ������ ���ڿ� �ּҷ� ��ȯ
	IN_ADDR in_addr;
	in_addr.s_addr = inet_addr(ipaddr);
	printf("IP ���� => ���ڿ� �ּ� = %s\n", inet_ntoa(in_addr));

	WSACleanup();
	return 0;
}