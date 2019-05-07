#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
};

SOCKET listenSock;	// 대기 소켓 핸들
int nTotalSockets = 0;	// 통신 소켓의 개수

// 소켓 정보와 커널 이벤트 정보를 보관하기 위한 배열로 '테이블 매핑' 방법을 사용해 서로의 관계 확인.\
	테이블 매핑은 보통 하나의 구조체에 묶일 수 있는 정보지만 각각 독립적으로 멤버 정보를 유지할 때 사용되는 방법으로 배열의 인덱스 번호를 사용해 같은 위치의 인덱스는 관련성 있는 정보를 나타낸다.
// 소켓 정보 저장 배열
SOCKETINFO *SocketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
// 소켓 정보와 연결되는 커널 이벤트 배열
WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];

// 소켓 함수 오류 출석
void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg,
		0, NULL
	);

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}


// 소켓 정보를 추가한다.
BOOL AddSocketInfo(SOCKET sock)
{
	// FD_SETSIZE - 연결 대기 소켓
	if (nTotalSockets >= (WSA_MAXIMUM_WAIT_EVENTS))
	{
		printf("[오류] 소켓 정보를 추가할 수 없습니다!\n");
		return FALSE;
	}

	// 대기 소켓 같은 경우 소켓 정보 구조체(SOCKETINFO)는 단지 소켓 핸들만 저장하는 용도로 사용된다.
	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[오류] 메모리가 부족합니다!\n");
		return FALSE;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		DisplayMessage();
		return FALSE;
	}


	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets] = ptr;
	EventArray[nTotalSockets] = hEvent;
	nTotalSockets++;

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

	// 소켓을 닫고 소켓 정보 객체를 삭제하고 커널 이벤트 닫음.
	closesocket(ptr->sock);
	delete ptr;

	// 닫은 소켓에 해당하는 소켓 정보 배열과 커널 이벤트 배열의 원소 제거.
	for (int i = nIndex; i < nTotalSockets; i++) {
		SocketInfoArray[i] = SocketInfoArray[i + 1];
		EventArray[i] = EventArray[i + 1];
	}

	nTotalSockets--;
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
	// 대기 소켓을 SocketInfoArray에 추가
	if (AddSocketInfo(listenSock) == FALSE)
		return false;

	// 대기 소켓과 커널 이벤트 객체를 연결한다.
	// FD_ACCEPT나 FD_CLOSE 네트워크 이벤트가 발생하면 커널 이벤트 객체가 신호상태가 된다.
	retval = WSAEventSelect(listenSock, EventArray[nTotalSockets - 1], FD_ACCEPT | FD_CLOSE);
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

unsigned int WINAPI WorkerThread(void* pParam)
{
	int retval;
	int index;
	WSANETWORKEVENTS NetworkEvents;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	while (1) {
		// 이벤트 객체가 신호상태가 될 때까지 대기
		// EventArray 배열의 이벤트를 nTotalSockets 개수만큼 대기하며 단 하나의 이벤트가 신호상태가 되어도 함수 반환.
		index = WSAWaitForMultipleEvents(nTotalSockets, EventArray, 
			FALSE,	// 이벤트 배열 안의 하나라도 이벤트가 발생하면 return해줄 것.
			WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			DisplayMessage();
			continue;
		}
		// 반환값에 WSA_WAIT_EVENT_0을 빼서 이벤트가 발생한 배열의 인덱스 번호를 찾아냄.
		index -= WSA_WAIT_EVENT_0;

		// 네트워크 이벤트가 발생한 소켓의 정보를 확인한다.
		// 신호 상태의 수동 이벤트를 비신호 상태로 변경한다.
		// 이벤트 식별하는 함수. 또한 이벤트를 clear해줌.
		retval = WSAEnumNetworkEvents(SocketInfoArray[index]->sock,
			EventArray[index], // 두 번째 인수로 전달한 커널 이벤트를 비신호 상태로 되돌림.
			&NetworkEvents);	// 오류 발생할 경우 이 구조체에 담아둠.
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			return FALSE;
		}

		// FD_ACCEPT 이벤트 처리를 처리한다.
		// NetworkEvents.lNetworkEvents & FD_ACCEPT == FD_ACCEPT 의미
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT) {	// NetworkEvents.lNetworkEvents: 4byte long type
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0) {
				DisplayMessage();
				return FALSE;
			}
			addrlen = sizeof(clientaddr);
			client_sock = accept(SocketInfoArray[index]->sock, (SOCKADDR *)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET)
			{
				DisplayMessage();
				return FALSE;
			}


			printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));

			if (nTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
				printf("[오류] 더 이상 접속을 받아들일 수 없습니다!\n");
				closesocket(client_sock);
				continue;
			}

			if (AddSocketInfo(client_sock) == FALSE)
				continue;
			retval = WSAEventSelect(client_sock,
				EventArray[nTotalSockets - 1],
				FD_READ | FD_WRITE | FD_CLOSE);
			if (retval == SOCKET_ERROR) {
				DisplayMessage();
				break;
			}
		}

		// FD_READ, FD_WRITE 이벤트 처리를 처리한다.
		if (NetworkEvents.lNetworkEvents & FD_READ
			|| NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			if (NetworkEvents.lNetworkEvents & FD_READ
				&& NetworkEvents.iErrorCode[FD_READ_BIT] != 0) {
				DisplayMessage();
				break;
			}
			if (NetworkEvents.lNetworkEvents & FD_WRITE
				&& NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0) {
				DisplayMessage();
				break;
			}
			SOCKETINFO *ptr = SocketInfoArray[index];

			if (ptr->recvbytes == 0) {
				// 데이터 받기
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);

				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//소켓 비정상 종료
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->recvbytes = retval;

				// 받은 데이터 출력
				ptr->buf[retval] = '\0';
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

				printf("[TCP서버] IP = %s, Port = %d의 메시지 : %s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					ptr->buf);
			}
			if (ptr->recvbytes > ptr->sendbytes) {
				// 데이터 보내기
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						//소켓 비정상 종료
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->sendbytes += retval;

				// 받은 데이터를 모두 보냈는지 체크
				if (ptr->recvbytes == ptr->sendbytes)
					ptr->recvbytes = ptr->sendbytes = 0;
			}
		}

		// FD_CLOSE 이벤트 처리
		if (NetworkEvents.lNetworkEvents & FD_CLOSE) {
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
				DisplayMessage();
			RemoveSocketInfo(index);

		}
	}
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
	if (!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}
	unsigned int threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}

