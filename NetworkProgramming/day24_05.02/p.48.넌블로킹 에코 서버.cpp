#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)
SOCKET listenSock;

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


bool CreateListenSocket()
{
	int retval;
	// 대기 소켓 생성
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return FALSE;
	}

	// 넌블로킹 소켓으로 바꾼다.
	u_long on = 1;
	retval = ioctlsocket(listenSock, FIONBIO, &on);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return FALSE;
	}

	// 대기 소켓의 로컬 주소, 포트 설정
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
	// 대기 소켓의 접속 대기 큐 생성 및 클라이언트 접속 대기
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return FALSE;
	}
	return TRUE;
}

//통신 스레드
unsigned int WINAPI ComThread(void* pParam)
{
	SOCKET clientSock = (SOCKET)pParam;
	int recvByte;
	char buf[BUFFERSIZE];
	SOCKADDR_IN clientaddr;

	while (1)
	{
		// 데이터 받기
		recvByte = recv(clientSock, buf, BUFFERSIZE, 0);
		if (recvByte == SOCKET_ERROR)
		{ 
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				//소켓 비정상 종료
				DisplayMessage();
				break;
			}
			// 넌블로킹 소켓 recv()의 목적이 완료되지 않음.
		}
		else if (recvByte == 0)
		{ //소켓 정상 종료
			printf("소켓 정상 종료");
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
			// 받은 데이터 출력
			buf[recvByte] = '\0';
			printf("[TCP서버] IP = %s, Port = %d의 메시지 : %s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port),
				buf);

			// 클라이언트로 데이터 에코하기
			retval = send(clientSock, buf, recvByte, 0);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
		}
	}
	// 통신 소켓 닫기
	closesocket(clientSock);

	printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port));
	return 0;
}

//대기 스레드
unsigned int __stdcall ListenThread(void* pParam)
{
	while (1)
	{
		SOCKET clientSock;
		SOCKADDR_IN clientaddr;
		int addrlen;
		addrlen = sizeof(clientaddr);

		// 접속 대기
		clientSock = accept(listenSock, (SOCKADDR *)&clientaddr, &addrlen);
		if (clientSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				DisplayMessage();
			}
			// 넌블로킹 소켓 accept()의 목적이 완료되지 않음.
			continue;
		}

		printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));



		// 클라이언트와 독립적인 통신을 위한 Thread 생성
		// 동시 접속 클라이언트 수만큼 스레드 생성
		// 스레드 생성, 유지 모두 오버헤드 발생. 따라서 동시 접속자 수가 많다면 이를 사용하면 안됨.
		unsigned int threadID;
		// 스레드 생성 후 그 핸들을 닫아주겠다. 핸들 포인터 닫아주기.
		CloseHandle((HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0,
			&threadID));
	}
	// 대기 소켓 닫기
	closesocket(listenSock);
}


int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}
	if (!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}
	unsigned int threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}