#include <winsock2.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;

	// ���� ���̺귯�� �ʱ�ȭ �Լ�.\
		WSAStartup(WORD mVersionRequested, LPWSADATA lpWSAData)\
			mVersionRequested: ���α׷��� �䱸�ϴ� �ֻ��� ���� ����.\
			lpWSAData: WSADATA Ÿ�� ������ �ּ�. �ý��ۿ��� �����ϴ� ���� ������ ���� ���� ���� ���� �� ����
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����!\n");
		return -1;
	}

	printf("������ ���� �ʱ�ȭ ����!\n");

	// ���ҽ� ��ȯ �Լ�
	WSACleanup();
	return 0;
}