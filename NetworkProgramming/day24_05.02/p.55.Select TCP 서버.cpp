#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE 1024

#pragma warning(disable:4996)

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvbytes;
	int sendbytes;
};

SOCKET listenSock;	// 대기 소켓 핸들
int nTotalSockets = 0;	// 통신 소켓의 개수
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

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

// 소켓 정보를 추가한다.
BOOL AddSocketInfo(SOCKET sock)
{
	// FD_SETSIZE - 연결 대기 소켓
	if (nTotalSockets >= (FD_SETSIZE - 1))
	{
		printf("[오류] 소켓 정보를 추가할 수 없습니다!\n");
		return FALSE;
	}

	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[오류] 메모리가 부족합니다!\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets++] = ptr;

	return TRUE;
}

// 소켓 정보를 삭제한다
void RemoveSocketInfo(int nIndex)
{
	SOCKETINFO *ptr = SocketInfoArray[nIndex];

	// 클라이언트 정보 얻기
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
	printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
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
		// 소켓 셋 초기화
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		FD_SET(listenSock, &rset);	// 대기 소켓을 rset에 등록
		for (int i = 0; i < nTotalSockets; i++)
		{
			if (SocketInfoArray[i]->recvbytes > SocketInfoArray[i]->sendbytes)
				FD_SET(SocketInfoArray[i]->sock, &wset);
			else
				FD_SET(SocketInfoArray[i]->sock, &rset);
		}

		// select() 대기
		retval = select(0, &rset, &wset, NULL, NULL);
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}

		// 대기 소켓에 클라이언트 접속이 요청되었나?
		if (FD_ISSET(listenSock, &rset)) {
			addrlen = sizeof(clientaddr);
			clientSock = accept(listenSock, (SOCKADDR *)&clientaddr,
				&addrlen);

			if (retval == INVALID_SOCKET)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//소켓 비정상 종료
					DisplayMessage();
				}
			}
			else {
				printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port));

				// 소켓 정보 추가
				if (AddSocketInfo(clientSock) == FALSE)
				{
					printf("\n[TCP 서버] 클라이언트 접속을 해제합니다!\n");
					closesocket(clientSock);
				}
			}
		}
		// 데이터 송,수신 가능한가?

		for (int i = 0; i < nTotalSockets; i++)
		{
			SOCKETINFO *ptr = SocketInfoArray[i];

			// 데이터가 수신 버퍼에 도착했다.
			if (FD_ISSET(ptr->sock, &rset)) {
				retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//소켓 비정상 종료
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

				// 받은 데이터 출력
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
				ptr->buf[retval] = '\0';

				printf("[TCP서버] IP = %s, Port = %d의 메시지 : %s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					ptr->buf);
			}

			// 송신 버퍼 여기 공간이 남아 데이터를 보낼 준비가 되었다.
			if (FD_ISSET(ptr->sock, &wset)) {
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes,
					ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//소켓 비정상 종료
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

	// 대기 소켓 닫기
	closesocket(listenSock);

	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}
	// 대기 소켓 초기화(socket()+bind()+listne())
	if (!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}

	// 대기 쓰레드 종료를 기다림.
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
//	//에러코드=>문자열
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL,
//		WSAGetLastError(), //에러코드획득
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&pMsg, 0, NULL);
//
//	//MessageBox(0, _TEXT((LPTSTR)pMsg), TEXT("알림"), MB_OK);
//	printf("%s\n", pMsg);
//	LocalFree(pMsg);
//}
//
//BOOL CreateListenSocket()
//{
//	int retval;
//	// 대기 소켓 생성
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
//	// 대기 소켓의 로컬 주소, 포트 설정
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
//	// 대기 소켓의 접속 대기 큐 생성 및 클라이언트 접속 대기
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
//	//FD_SETSIZE - 연결 대기 소켓
//	if (nTotalsockets >= (FD_SETSIZE - 1)) {
//		printf("[오류] 소켓 정보를 추가할 수 없습니다!\n");
//		return FALSE;
//	}
//
//	SOCKETINFO *ptr = new SOCKETINFO;
//	if (ptr == NULL) {
//		printf("[오류] 메모리가 부족합니다!\n");
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
//	//클라이언트 정보 얻기
//	SOCKADDR_IN clientaddr;
//	int addrlen = sizeof(clientaddr);
//	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
//	printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
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
//			//select 대기
//			retval = select(0, &rset, &wset, NULL, NULL);
//			if (retval == SOCKET_ERROR)
//			{
//				DisplayMessage();
//				break;
//			}
//			//대기 소켓에 클라이언트 접속이 요청되었나?
//			if (FD_ISSET(listenSock, &rset)) {
//				addrlen = sizeof(clientaddr);
//				clientSock = accept(listenSock, (SOCKADDR*)&clientaddr, &addrlen);
//				if (clientSock == INVALID_SOCKET) {
//					if (WSAGetLastError() != WSAEWOULDBLOCK)
//						DisplayMessage();
//				}
//				else {
//					printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
//						inet_ntoa(clientaddr.sin_addr),
//						ntohs(clientaddr.sin_port));
//					//소켓 정보 추가
//					if (AddSocketInfo(clientSock) == FALSE) {
//						printf("[TCP 서버]클라이언트의 접속을 해제합니다!\n");
//						closesocket(clientSock);
//					}
//				}
//			}
//}
//			//데이터 송 수신이 가능한가?
//			for (int i = 0; i < nTotalsockets; i++)
//			{
//				SOCKETINFO *ptr = SocketinfoArray[i];
//				//데이터가 수신 버퍼에 도착 했다.
//				if (FD_ISSET(ptr->sock, &rset)) {
//					retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
//					if (retval == SOCKET_ERROR) {
//						if (WSAGetLastError() != WSAEWOULDBLOCK)
//						{
//							//소켓 비정상 종료
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
//					//받은 데이터 출력
//					addrlen = sizeof(clientaddr);
//					getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
//					ptr->buf[retval] = '\0';
//					printf("[TCP서버] IP = %s, Port = %d의 메시지 : %s\n",
//						inet_ntoa(clientaddr.sin_addr),
//						ntohs(clientaddr.sin_port),
//						ptr->buf);
//				}
//				//송신 버퍼 여기 공간이 남아 데이터를 보낼 준비가 되었다.
//				if (FD_ISSET(ptr->sock, &wset)) {
//					retval = send(ptr->sock, ptr->buf + ptr->sendByte, ptr->recvByte - ptr->sendByte, 0);
//					if (retval == SOCKET_ERROR)
//					{
//						if (WSAGetLastError() != WSAEWOULDBLOCK)
//						{
//							//소켓 비정상 종료
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
////통신 스레드
//unsigned int WINAPI ComThread(void* pParam)
//{
//	SOCKET clientSock = (SOCKET)pParam;
//	int recvByte;
//	char buf[BUFFERSIZE];
//	SOCKADDR_IN clientaddr;
//
//	while (1)
//	{
//		// 데이터 받기
//		recvByte = recv(clientSock, buf, BUFFERSIZE, 0);
//
//		if (recvByte == SOCKET_ERROR) {
//			if (WSAGetLastError() != WSAEWOULDBLOCK)
//			{
//				//소켓 비정상 종료
//				DisplayMessage();
//				break;
//			}
//		}
//		//넌 블로킹 소켓 recv()의 목적이 완료되지 않음.
//		else if (recvByte == 0)
//		{ //소켓 정상 종료
//			printf("소켓 정상 종료");
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
//			// 받은 데이터 출력
//			buf[recvByte] = '\0';
//			printf("[TCP서버] IP = %s, Port = %d의 메시지 : %s\n",
//				inet_ntoa(clientaddr.sin_addr),
//				ntohs(clientaddr.sin_port),
//				buf);
//
//			// 모든 클라이언트로 데이터 에코하기
//			retval = send(clientSock, buf, recvByte, 0);
//			if (retval == SOCKET_ERROR)
//			{
//				DisplayMessage();
//				break;
//			}
//		}
//	}
//	// 통신 소켓 닫기
//	closesocket(clientSock);
//
//	printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
//		inet_ntoa(clientaddr.sin_addr),
//		ntohs(clientaddr.sin_port));
//	return 0;
//}
//
////대기 스레드
//unsigned int __stdcall ListenThread(void* pParam)
//{
//	while (1)
//	{
//		SOCKET clientSock;
//		SOCKADDR_IN clientaddr;
//		int addrlen;
//		addrlen = sizeof(clientaddr);
//		// 접속 대기
//		clientSock = accept(listenSock, (SOCKADDR *)&clientaddr, &addrlen);
//		if (clientSock == INVALID_SOCKET)
//		{
//			if (WSAGetLastError() != WSAEWOULDBLOCK)
//			{
//				DisplayMessage();
//				//넌 블로킹 소켓 accept()의 목적이 완료되지 않음
//			}
//			continue;
//		}
//
//		printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
//			inet_ntoa(clientaddr.sin_addr),
//			ntohs(clientaddr.sin_port));
//
//
//
//		// 클라이언트와 독립적인 통신을 위한 Thread 생성
//		unsigned int threadID;
//		CloseHandle((HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0,
//			&threadID));
//	}
//	// 대기 소켓 닫기
//	closesocket(listenSock);
//}
//
//int main(int argc, char* argv[])
//{
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		printf("윈도우 소켓 초기화 실패\n");
//		return -1;
//	}
//	if (!CreateListenSocket())
//	{
//		printf("대기 소켓 생성 실패\n");
//		return -1;
//	}
//	unsigned int threadID;
//	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
//	WSACleanup();
//	return 0;
//}