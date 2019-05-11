#include <winsock2.h>
#include <process.h>
#include <stdio.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	// overlapped 구조체의 주소를 구조체와 연결해 사용.\
		비동기 입출력 함수의 마지막 인수로 overlapped 구조체의 주소가 지정되며\
		완료 루틴이 호출될 때 입출력 함수의 지정했던 overlapped 구조체의 주소가 완료 루틴 콜백 함수의 세 번째 인수로도 전달되므로\
		이 주소를 이용해 구조체 정보를 완료 루틴에서 얻어 사용한다.\
		overlapped 구조체의 주소를 입출력 함수에 지정하면 overlapped 멤버의 주소는 곧 SOCKETINFO 구조체의 시작 주소이므로\
		완료 루틴에서 SOCKETINFO 구조체로 형식 변환하여 모든 멤버를 접근할 수 있다.
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

SOCKET listenSock;
SOCKET clientSock;
HANDLE hEvent;

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

// 완료 루틴
void CALLBACK CompletionRoutine(
	DWORD dwError, DWORD cbTransferred,	// 실제 수행한 byte 수 = cbTransferred
	LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	int retval;

	// 클라이언트 정보 얻기
	SOCKETINFO *ptr = (SOCKETINFO*)lpOverlapped;	// heap 영역에 있는 socket info
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);

	// 비동기 입출력 결과 확인
	if (dwError != 0 || cbTransferred == 0) {	// 정상적인 종료 (cbTransferred == 0)
		if (dwError != 0) DisplayMessage();
		closesocket(ptr->sock);
		printf("\n[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
		delete ptr;
		return;
	}

	// 데이터 전송량 갱신
	if (ptr->recvbytes == 0) {	// 데이터를 수신했다면
		ptr->recvbytes = cbTransferred;
		ptr->sendbytes = 0;
		// 받은 데이터 출력
		ptr->buf[ptr->recvbytes] = '\0';

		printf("[TCP/%s:%d] %s\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), ptr->buf);
	}
	else {
		// 보낸 데이터 계산
		ptr->sendbytes += cbTransferred;
	}

	if (ptr->recvbytes > ptr->sendbytes) {
		// 데이터 보내기
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf + ptr->sendbytes;
		ptr->wsabuf.len = ptr->recvbytes - ptr->sendbytes;

		DWORD sendbytes;
		// 연결된 전체 소켓에 보내도록 변경
		retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
			0, &(ptr->overlapped), CompletionRoutine);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return;
			}
		}
	}
	else {
		// 받은 데이터를 모두 보냈다면 recvbytes를 초기화하고\
			다시 데이터 수신을 위한 비동기 입출력 함수 시작
		ptr->recvbytes = 0;

		// 데이터 받기
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), CompletionRoutine);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return;
			}
		}
	}
}

// 작업 쓰레드
unsigned int WINAPI WorkerThread(void* pParam)
{
	HANDLE hEvent = (HANDLE)pParam;
	int retval;

	while (1) {
		while (1) {
			// alertable wait\
				임시 커널 이벤트가 신호 상태가 되는지를 (클라이언트 접속) 판단하고 쓰레드를 알림 가능 상태로 만드는 코드로 완료 루틴이 실행되면 반환되고\
				WAIT_IO_COMPLETION 값이면 다시 쓰레드를 알림 가능 상태로 만든다.\
				만약 WAIT_OBJECT_0이면 클라이언트가 접속했으므로 접속을 위한 코드를 수행한다.
			DWORD result = WaitForSingleObjectEx(hEvent, INFINITE, 
				TRUE);	// alertable state TRUE. 콜백 함수를 받을 수 있는 상태.
			if (result == WAIT_OBJECT_0) break;				// 클라이언트 접속.
			if (result != WAIT_IO_COMPLETION) return -1;	// 쓰레드를 알림 가능 상태로 만듬
		}

		// 접속한 클라이언트 정보 출력
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(clientSock, (SOCKADDR*)&clientaddr, &addrlen);

		printf("\n[TCP 서버] 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		// 소켓 정보 구조체 할당과 초기화
		SOCKETINFO *ptr = new SOCKETINFO;
		if (ptr == NULL) {
			printf("[오류] 메모리가 부족합니다!\n");
			return -1;
		}

		// 클라이언트가 접속되었으므로 소켓의 정보 메모리를 생성
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->sock = clientSock;
		ptr->recvbytes = 0;
		ptr->sendbytes = 0;

		// wsabuf.buf는 buffer의 포인터만 받을 수 있음. 따라서 buffer를 바로 wsabuf.buf로 받을 수 있는 구조가 될 수 없다.\
			char 배열 buffer를 만든 후 그 주소값을 wsabuf.buf로 보내줘야 함.
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		// 비동기 입출력 시작 (데이터 수신을 위한)
		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvbytes,
			&flags, &(ptr->overlapped), 
			CompletionRoutine);	// 입출력 작업이 완료하면 실행할 완료 루틴의 콜백 함수 주소
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				DisplayMessage();
				return -1;
			}
		}
	}
	return 0;
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

	// 임시 이벤트 객체 생성\
		임시 커널 이벤트 객체를 생성해 클라이언트 접속이 발생함을 알리는데 사용
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEvent == NULL) false;

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

	// 대기 쓰레드 종료를 기다림
	unsigned int threadID;
	CloseHandle((HANDLE)_beginthreadex(0, 0, WorkerThread, (void*)hEvent, 0,
		&threadID));

	// 클라이언트 접속을 처리하기 위한 코드\
		메인 쓰레드에서 루프를 이용해 accept()를 처리하고\
		SetEvent(hEvent)로 클라이언트 접속을 WorkerThread에 알려 클라이언트 접속 처리 수행.
	while (1) {
		// accept()
		clientSock = accept(listenSock, NULL, NULL);
		if (clientSock == INVALID_SOCKET) {
			DisplayMessage();
			continue;
		}
		if(!SetEvent(hEvent)) break;
	}
	// 윈속 종료
	WSACleanup();
	return 0;
}

