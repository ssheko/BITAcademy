#include <WinSock2.h>
#include <stdio.h>

#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}

	// 문자열 주소 출력
	const char *ipaddr = "230.200.12.5";
	printf("IP 문자열 주소 : %s\n", ipaddr);

	// 문자열 주소를 4byte 정수로 변환
	printf("IP 문자열 주소 => 정수 = 0x%08x\n", inet_addr(ipaddr));

	// 4byte 정수를 문자열 주소로 변환
	IN_ADDR in_addr;
	in_addr.s_addr = inet_addr(ipaddr);
	printf("IP 정수 => 문자열 주소 = %s\n", inet_ntoa(in_addr));

	WSACleanup();
	return 0;
}