#include <winsock2.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)
// 소켓 함수 오류 출력
void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // 오류 메세지 저장 메모리를 내부에서 할당하라
		FORMAT_MESSAGE_FROM_SYSTEM,		// 운영체제로부터 오류 메세지를 가져온다
		NULL,
		WSAGetLastError(),				// 오류 코드
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 언어 (제어판 설정 언어)
		(LPTSTR)&pMsg,					// 오류 메세지 outparam
		0, NULL);

	printf("%s\n", pMsg);				// 오류 메세지 출력

	LocalFree(pMsg);					// 오류 메세지 저장 메모리 반환
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}
int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}

	// 클라이언트 소켓 생성
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

	// 서버에 접속 요청
	retval = connect(
		sock,	// 소켓 핸들
		(SOCKADDR *)&serveraddr,	//접속 서버 주소값
		sizeof(serveraddr)			// 주소값 크기
	);	// 통신 소켓(성공하면 자동으로 지역포트, 지역주소를 할당

	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	// 데이터 통신에 사용할 변수
	char buf[BUFFERSIZE];
	int len;

	// 서버와 데이터 통신
	while (1)
	{
		// 데이터 입력
		ZeroMemory(buf, sizeof(buf));
		printf("[문자열 입력] ");
		if (fgets(buf, BUFFERSIZE-1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';

		if (strlen(buf) == 0)
			break;

		// 서버에 데이터 보내기
		retval = send(
			sock,		//통신 소켓 핸들
			buf,		//보낼 애플리케이션 버퍼
			strlen(buf),// 보낼 데이터 크기
			0			// 대부분 0 or MSG_DONTROUTE나 MSG_OOB를 사용 가능
		);

		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}

		printf("[TCP 클라이언트] %d바이트를 전송\n", retval);

		// 데이터 받기
		retval = recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR || retval == 0)
		{
			DisplayMessage();
			break;
		}
		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받음, 데이터: %s\n", retval, buf);
	}

	// 소켓 닫기
	closesocket(sock);

	WSACleanup();
	return 0;
}