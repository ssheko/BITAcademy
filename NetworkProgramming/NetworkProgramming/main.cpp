#include <winsock2.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;

	// 윈속 라이브러리 초기화 함수.\
		WSAStartup(WORD mVersionRequested, LPWSADATA lpWSAData)\
			mVersionRequested: 프로그램이 요구하는 최상위 윈속 버전.\
			lpWSAData: WSADATA 타입 변수의 주소. 시스템에서 제공하는 윈속 구현에 대한 세부 사항 얻을 수 있음
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패!\n");
		return -1;
	}

	printf("윈도우 소켓 초기화 성공!\n");

	// 리소스 반환 함수
	WSACleanup();
	return 0;
}