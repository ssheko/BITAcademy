#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	// 에코 서버는 수신과 송신이 동시에 일어나지 않기 때문에 하나의 WSAOVERLAPPED 구조체를 사용할 수 있다.\
		만약 송, 수신을 독립적으로 수행해야 한다면 독립적으로 동작하는 비동기 입출력이 두 개이므로\
		송, 수신 각각의 WSAOVERLAPPED 구조체를 사용해야 한다.
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

CRITICAL_SECTION cs;
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
	// 세 개의 스레드(main thread, listen thread, worker thread)에서 접근하므로 임계영역 설정.
	EnterCriticalSection(&cs);

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

	ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
	ptr->overlapped.hEvent = hEvent;
	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;

	// wsabuf.buf는 buffer의 포인터만 받을 수 있음. 따라서 buffer를 바로 wsabuf.buf로 받을 수 있는 구조가 될 수 없다.\
		char 배열 buffer를 만든 후 그 주소값을 wsabuf.buf로 보내줘야 함.
	ptr->wsabuf.buf = ptr->buf;
	ptr->wsabuf.len = BUFSIZE;
	SocketInfoArray[nTotalSockets] = ptr;
	EventArray[nTotalSockets] = hEvent;
	nTotalSockets++;

	LeaveCriticalSection(&cs);
	return TRUE;
}

// 소켓 정보를 삭제한다
void RemoveSocketInfo(int nIndex)
{
	EnterCriticalSection(&cs);

	SOCKETINFO *ptr = SocketInfoArray[nIndex];	
	// 소켓을 닫고 소켓 정보 객체를 삭제하고 커널 이벤트 닫음.
	closesocket(ptr->sock);
	delete ptr;
	WSACloseEvent(EventArray[nIndex]);

	// 닫은 소켓에 해당하는 소켓 정보 배열과 커널 이벤트 배열의 원소 제거.
	for (int i = nIndex; i < nTotalSockets; i++) {
		SocketInfoArray[i] = SocketInfoArray[i + 1];
		EventArray[i] = EventArray[i + 1];
	}

	nTotalSockets--;

	LeaveCriticalSection(&cs);
}

bool CreateListenSocket()
{
	int retval;
	// 대기 소켓 생성
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return false;
	}
	// 대기 소켓을 SocketInfoArray에 추가
	if (AddSocketInfo(listenSock) == FALSE)
		return false;

	// 통신 소켓이 생성될 때까지 WorkerThread 임시 대기를 위한 임시 이벤트 객체 생성
	//WSAEVENT hEvent = WSACreateEvent();
	//if (hEvent == WSA_INVALID_EVENT) {
	//	DisplayMessage();
	//	return false;
	//}
	//EventArray[nTotalSockets++] = hEvent;

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
		return false;
	}
	// 대기 소켓의 접속 대기 큐 생성 및 클라이언트 접속 대기
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}

unsigned int WINAPI WorkerThread(void* pParam)
{
	int retval;
	while (1) {
		// 이벤트 객체 관찰
		DWORD index = WSAWaitForMultipleEvents(nTotalSockets,
			EventArray, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			DisplayMessage();
			continue;
		}
		index -= WSA_WAIT_EVENT_0;
		WSAResetEvent(EventArray[index]);
		if (index == 0)	continue;
		// index != 0일 경우 client에서 이벤트 발생한 것.
		// 클라이언트 정보 얻기
		SOCKETINFO  *ptr = SocketInfoArray[index];
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

		// 비동기 입출력 결과 확인
		DWORD cbTransferred, flags;
		retval = WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped),
			&cbTransferred, FALSE, &flags);
		if (retval == FALSE || cbTransferred == 0) {
			if(retval == FALSE)
				DisplayMessage();
			RemoveSocketInfo(index);
			printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			continue;
		}

		// 데이터 전송량 갱신
		if (ptr->recvbytes == 0) {
			ptr->recvbytes = cbTransferred;
			ptr->sendbytes = 0;

			// 받은 데이터 출력
			ptr->buf[ptr->recvbytes] = '\0';
			printf("[TCP/%s:%d] %s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port), ptr->buf);
		}
		else {
			ptr->sendbytes += cbTransferred;
		}

		if (ptr->recvbytes > ptr->sendbytes) {
			// 데이터 보내기
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = EventArray[index];
			ptr->wsabuf.buf = ptr->buf + ptr->sendbytes;
			ptr->wsabuf.len = ptr->recvbytes - ptr->sendbytes;

			DWORD sendbytes;
			retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
				0, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					DisplayMessage();
				}
				continue;
			}
		}
		else {
			ptr->recvbytes = 0;

			// 데이터 받기
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = EventArray[index];
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFSIZE;

			DWORD recvbytes;
			flags = 0;
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
				&flags, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					DisplayMessage();
				}
				continue;
			}
		}
	}
	return 0;
}

unsigned int WINAPI ListenThread(void* pParam) {
	while (1) {
		// accept()
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		// accept 요청 대기
		SOCKET client_sock = accept(listenSock, (SOCKADDR *)&clientaddr,
			&addrlen);
		if (client_sock == INVALID_SOCKET) {
			DisplayMessage();
			continue;
		}


		printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		// 소켓 정보 추가
		if (AddSocketInfo(client_sock) == FALSE) {
			closesocket(client_sock);

			printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			continue;
		}

		// 비동기 입출력 시작
		SOCKETINFO *ptr = SocketInfoArray[nTotalSockets - 1];
		DWORD recvbytes;
		DWORD flags = 0;
		// 비동기함수 WSARecv
		int retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				//소켓 비정상 종료
				DisplayMessage();
				RemoveSocketInfo(nTotalSockets-1);
				continue;
			}
		}

		// 소켓의 개수(nTotalSockets) 변화를 알림
		// 수동으로 event set. Worker Thread의 WSAWaitForMultipleEvents() 활성화.
		if (WSASetEvent(EventArray[0]) == FALSE) {
			DisplayMessage();
			break;
		}
	}

	// 대기 소켓 닫기
	closesocket(listenSock);
	
	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	InitializeCriticalSection(&cs);
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
	// 총 3개의 스레드. main thread, listen thread, worker thread
	HANDLE threadArray[2];
	threadArray[0] = (HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0,
		&threadID);
	threadArray[1] = (HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0,
		&threadID);
	// 두 스레드가 모두 종료되어야 끝남.
	WaitForMultipleObjects(2, threadArray, TRUE, INFINITE);

	WSACleanup();
	DeleteCriticalSection(&cs);
	return 0;
}

