#include "pch.h"
#include "NetServer.h"
#include "CrashDump.h"

extern bool Check_1Sec(ULONGLONG * time);
extern CrashDump cd;

/*----------------------------------------------------------*/
// NetServer::NetServer (public)
// ���� : ������
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
NetServer::NetServer()
{
	_workerThreadCount = 0;
	_activeWorkerThreadCount = 0;
	_clientSeed = 1;
	_serverPort = 0;

	_acceptCount = 0;
	_acceptTPS = 0;
	_acceptTPSTime = GetTickCount64();
}

/*----------------------------------------------------------*/
// NetServer::~NetServer (public)
// ���� : �Ҹ���
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
NetServer::~NetServer()
{
}

/*----------------------------------------------------------*/
// NetServer::WorkerThreadMain (protected)
// ���� : Worker������ �����Լ�
// ���� : (LPVOID) ������
// ���� : (unsigned int) ��������� 0
/*----------------*////////////////////////*----------------*/
unsigned int WINAPI NetServer::WorkerThreadMain(LPVOID lpParam)
{
	NetServer * _this = (NetServer *)lpParam;

	while (1)
	{
		DWORD transBytes = 0;
		LPOVERLAPPED overlapped = nullptr;
		Session * session = nullptr;
		BOOL ret = GetQueuedCompletionStatus(_this->_iocp, &transBytes, (PULONG_PTR)&session, &overlapped, INFINITE);
		if (ret && session == NULL)
		{
			//������ ����
			break;
		}
		if (overlapped == nullptr)
		{
			// ������ �����������
			int errorCode = GetLastError();
			//shutdown(session->socket, SD_SEND);
			//_this->TryDisConnect(session);
		}
		else
		{
			// ���ſϷ�
			if (&session->recvOverLapped == overlapped)
			{
				// ������ ���� ��Ȳ
				if (transBytes == 0)
				{
					if (!ret)
					{
						//_this->RecvPost(session);
						DWORD flag = 0;
						int errorCode0 = GetLastError();
						WSAGetOverlappedResult(session->socket, &session->recvOverLapped, &transBytes, TRUE, &flag);
						int errorCode = GetLastError();
						//if(errorCode == WSAETIMEDOUT)
							LOG(L"Server", LOG_ERROR, L"RECV IO FAIL : %d , OVERLAPPED %d , socket = %d", errorCode0, errorCode, session->socket);
					}
					shutdown(session->socket, SD_SEND);
				}
				// ���� ���ſϷ�
				else
				{
					session->recvQueue.MoveWritePos(transBytes);
					_this->RecvProc(session);
					_this->RecvPost(session);
				}
			}
			// �۽ſϷ�
			else if (&session->sendOverLapped == overlapped)
			{
				// ������ ���� ��Ȳ
				if (transBytes == 0)
				{
					if (!ret)
					{
						DWORD flag = 0;
						int errorCode0 = GetLastError();
						WSAGetOverlappedResult(session->socket, &session->recvOverLapped, &transBytes, FALSE, &flag);
						int errorCode = GetLastError();

						LOG(L"Server", LOG_ERROR, L"SEND IO FAIL : %d, OVERLAPPED %d, socket = %d", errorCode0, errorCode, session->socket);
						//if (errorCode == ERROR_IO_INCOMPLETE)
						//	continue;
						//if (errorCode == WSAETIMEDOUT)
					}
					shutdown(session->socket, SD_SEND);
				}
				// ���� �۽ſϷ�
				else
				{
					for (int i = 0; i < session->sendCount; i++)
					{
						PacketFree(session->sendArray[i]);
						session->sendArray[i] = nullptr;
					}
					session->sendCount = 0;
					session->sendFlag = FALSE;
					_this->OnSend(session->clientID, transBytes);
					//SendProc(session);
					_this->SendPost(session);

					if (session->disConnectFlag)
					{
						shutdown(session->socket, SD_SEND);
					}

				}
			}
			// Postť ��Ȳ
			else
			{
				INT64 clientID = (INT64)session;
				StreamBuffer * packet = (StreamBuffer *)overlapped;
				_this->SendPacket(clientID, packet, true);
				PacketFree(packet);
				continue;
				//LOG(L"Server", LOG_ERROR, L"IO FAIL");
			}
			// ���⼭ io ī��Ʈ ����
			int ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
			// �������� üũ ����
			if (ioCount == 0)
			{
				_this->TryDisConnect(session);
			}
		}
	}
	return 0;
}

/*----------------------------------------------------------*/
// NetServer::AcceptThreadMain (protected)
// ���� : Accept������ �����Լ�
// ���� : (LPVOID) ������
// ���� : (unsigned int) ��������� 0
/*----------------*////////////////////////*----------------*/
unsigned int WINAPI NetServer::AcceptThreadMain(LPVOID lpParam)
{
	NetServer * _this = (NetServer *)lpParam;

	_this->_listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	char reUseAddr = 1;
	setsockopt(_this->_listenSocket, SOL_SOCKET, SO_REUSEADDR, &reUseAddr, sizeof(reUseAddr));
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	//inet_pton(AF_INET, INADDR_ANY, &addr.sin_addr.s_addr);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr.sin_addr.s_addr = inet_addr(_this->_bindIP);
	inet_pton(AF_INET, _this->_bindIP, &addr.sin_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_this->_serverPort);
	int retval = bind(_this->_listenSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
	{
		//LOG(Logger::LOG_LEVEL_ERROR, L"bind Error\n");
		int error = GetLastError();
		LOG(L"Server", LOG_ERROR, L"FAIL BIND LISTENSOCKET");
		system("pause");
		return -1;
	}
	listen(_this->_listenSocket, SOMAXCONN);
	LOG(L"Server", LOG_ERROR, L"--SERVER OPEN--");
	while (1)
	{
		SOCKADDR_IN newAddr;
		int addrSize = sizeof(newAddr);
		SOCKET sock = accept(_this->_listenSocket, (SOCKADDR*)&newAddr, &addrSize);
		_this->_acceptCount++;
		InterlockedIncrement((LONG*)&_this->_acceptTPS);
		if (sock == INVALID_SOCKET)
		{
			int errorCode = GetLastError();
			if (errorCode == WSAEWOULDBLOCK)
			{
				Sleep(1000);
				continue;
			}
			// accept�� ���������� �ݾƼ� �������� ����
			else if (errorCode == WSAEINTR)
				break;
			else if (errorCode == WSAENOTSOCK)
				break;
			// ���� �����κκ�
			continue;
		}
		// ���� �Լ�
		WCHAR IP[16];
		InetNtop(AF_INET, &newAddr.sin_addr, IP, 16);
		if (!_this->OnConnectionRequest(IP, ntohs(newAddr.sin_port)))
		{
			closesocket(sock);
			LOG(L"Server", LOG_WARNING, L"OnConnectionRequest False");
			continue;
		}

		int index;
		if (!_this->GetBlankIndex(&index))
		{
			closesocket(sock);
			LOG(L"Server", LOG_ERROR, L"NO INDEX");
			continue;
		}
		
		INT64 clientID = (_this->_clientSeed++ << 2 * 8) | index;
		_this->_sessionArray[index].Init(sock, clientID, IP);
		Session * session = &_this->_sessionArray[index];
		int size = session->recvQueue.GetUseSize();
	
		CreateIoCompletionPort((HANDLE)sock, _this->_iocp, (ULONG_PTR)session, 0);
		// ���� �Լ�
		_this->OnClientJoin(session->clientID, session);
		_this->RecvPost(session);
		int ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
		if (ioCount == 0)
			_this->TryDisConnect(session);
	}
	return 0;
}

bool NetServer::LoadConfig()
{
	_configParser.OpenFile("NetServer.cnf");
	_configParser.GetValue_Str("BIND_IP", _bindIP, "SERVER");
	_configParser.GetValue_Int("BIND_PORT", _serverPort, "SERVER");
	_configParser.GetValue_Int("WORKER_THREAD", _workerThreadCount, "SERVER");
	_configParser.GetValue_Int("ACTIVE_WORKER_THREAD", _activeWorkerThreadCount, "SERVER");
	_configParser.GetValue_Int("CLIENT_MAX", _clientMAX, "SERVER");
	_configParser.GetValue_Int("MONITOR_NO", _monitorNo, "SERVER");


	_configParser.GetValue_BYTE("PACKET_CODE", _packetCode, "SERVER");
	_configParser.GetValue_BYTE("PACKET_KEY1", (BYTE&)_XORKey1, "SERVER");
	_configParser.GetValue_BYTE("PACKET_KEY2", (BYTE&)_XORKey2, "SERVER");

	LOGGER.SetLogDir(&wstring(L"Server_LOG"));

	char loglevel[10];
	_configParser.GetValue_Str("LOG_LEVEL", loglevel, "SERVER");
	if(strcmp(loglevel, "DEBUG") == 0)
		LOGGER.SetLogLevel(LOG_DEBUG);
	else if(strcmp(loglevel, "WARNING") == 0)
		LOGGER.SetLogLevel(LOG_WARNING);
	else if(strcmp(loglevel, "ERROR") == 0)
		LOGGER.SetLogLevel(LOG_ERROR);
	else 
		LOGGER.SetLogLevel(LOG_DEBUG);

	return true;
}

/*----------------------------------------------------------*/
// NetServer::Start (public)
// ���� : ���� �����ϴ� �Լ�
// ���� : (int) ��Ŀ������ ��<�ִ� MAXTHREADCOUNT> , (int) ��Ʈ��ȣ, (bool) nagle���� <�̱���>
// ���� : (bool) true
/*----------------*////////////////////////*----------------*/
bool NetServer::Start(bool nagle)
{
	LoadConfig();

	if (MAXTHREADCOUNT < _workerThreadCount)
		_workerThreadCount = MAXTHREADCOUNT;

	if (MAXSESSION < _clientMAX)
		_clientMAX = MAXSESSION;

	for (int i = 0; i < _clientMAX; i++)
	{
		_indexStack.Push(i);
	}

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, _activeWorkerThreadCount);
	for (int i = 0; i < _workerThreadCount; ++i)
		_workerThread[i] = (HANDLE)_beginthreadex(NULL, 0, WorkerThreadMain, this, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	_acceptThread = (HANDLE)_beginthreadex(NULL, 0, AcceptThreadMain, this, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	
	_status = SERVER_ON;

	return true;
}

/*----------------------------------------------------------*/
// NetServer::Stop (public)
// ���� : ���� ���� �Լ�
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
void NetServer::Stop()
{
	// accept������ ������
	closesocket(_listenSocket);
	WaitForSingleObject(_acceptThread, INFINITE);

	// ����� ���� ����
	for (auto & session : _sessionArray)
	{
		if(session.socket != INVALID_SOCKET)
			closesocket(session.socket);
	}

	// worker������ ������
	for (int i = 0; i < _workerThreadCount; ++i)
		PostQueuedCompletionStatus(_iocp, 0, 0, 0);
	WaitForMultipleObjects(_workerThreadCount, _workerThread, TRUE, INFINITE);

	_status = SERVER_OFF;

	WSACleanup();
}

void NetServer::GetIP(INT64 clientID, WCHAR * ipBuffer, int size)
{
	int index = FindIndex(clientID);
	StringCchCopy(ipBuffer, size, _sessionArray[index].IP);
}

/*----------------------------------------------------------*/
// NetServer::GetClientCount (public)
// ���� : ���� �������� Ŭ���̾�Ʈ ��
// ���� : 
// ���� : (int) Ŭ���̾�Ʈ ��
/*----------------*////////////////////////*----------------*/
int NetServer::GetClientCount()
{
	return (int)(_clientMAX - _indexStack.GetUseCount());
}

/*----------------------------------------------------------*/
// NetServer::TryDisConnect (protected)
// ���� : ���ο��� ���Ǵ� ���� ����õ� , ioī��Ʈ ���ҽ� ȣ��ȴ�
// ���� : (Session *) ����������
// ���� : 
/*----------------*////////////////////////*----------------*/
void NetServer::TryDisConnect(Session * session)
{
	if (session == nullptr)
		return;

	if (InterlockedCompareExchange64((LONG64 *)&session->ioCountUseFlag, (LONG64)NULL, (LONG64)TRUE) == (LONG64)TRUE)
	{
		closesocket(session->socket);
		OnClientLeave(session->clientID);

		StreamBuffer * packet = nullptr;
#ifdef BOOST
		while (session->sendQueue.pop(packet))
		{
			PacketFree(packet);
		}
#else
		int sized = (int)session->sendQueue.GetUseCount();
		while (sized--)
		{
			session->sendQueue.DeQueue(&packet);
			PacketFree(packet);
		}
#endif
		int size = session->sendCount;

		for (int i = 0; i < size; i++)
		{
			PacketFree(session->sendArray[i]);
			session->sendArray[i] = nullptr;
		}
		session->sendCount = 0; 

		session->socket = INVALID_SOCKET;
		int sessionIndex = FindIndex(session->clientID);
		session->clientID = -1;
		session->ioCountUseFlag.useFlag = false;
		_indexStack.Push(sessionIndex);
	}
}

/*----------------------------------------------------------*/
// NetServer::Disconnect (public)
// ���� : �ܺο��� ���Ǵ� Ŭ���̾�Ʈ ���� ���� ��û
// ���� : (INT64) Ŭ���̾�ƮID
// ���� : ��������
/*----------------*////////////////////////*----------------*/
bool NetServer::Disconnect(INT64 clientID)
{
	int index = FindIndex(clientID);
	Session * session = &_sessionArray[index];
	if (session->clientID != clientID)
		return false;
	shutdown(session->socket, SD_SEND);
	TryDisConnect(session);
	return true;
}

/*----------------------------------------------------------*/
// NetServer::SendPacket (public)
// ���� : �ܺο��� ���Ǵ� ��Ŷ���ۿ�û
// ���� : (INT64) Ŭ���̾�ƮID, (StreamBuffer *) ��Ŷ������
// ���� : (bool) ��������
/*----------------*////////////////////////*----------------*/
bool NetServer::SendPacket(INT64 clientID, StreamBuffer * packet, bool isWorker)
{
	if (isWorker == false)
	{
		packet->AddRef();
		PostQueuedCompletionStatus(_iocp, 0, (ULONG_PTR)clientID, (LPOVERLAPPED)packet);
		return true;
	}

	int index = FindIndex(clientID);
	Session * session = &_sessionArray[index];

	bool ret = false;
	int ioCount = InterlockedIncrement((LONG *)&session->ioCountUseFlag.ioCount);
	if (ioCount != 1)
	{
		if (session->clientID == clientID)
		{
			if (session->ioCountUseFlag.useFlag == TRUE)
			{
				//if (session->socket != INVALID_SOCKET)
				{
					packet->AddRef();
					//if (!packet->_headerFillFlag)
					if(_InterlockedCompareExchange8((char *)&packet->_headerEnterFlag, true, false) == false)
						PutHeader(packet);
					while (!packet->_encodeFlag)
						Sleep(0);
#ifdef BOOST
					session->sendQueue.push(packet);
#else
					session->sendQueue.EnQueue(packet);
#endif
					ret = SendPost(session);
					

					//if (!ret)
					//	PacketFree(packet);

					//LOGHEX(L"packet", Logger::LOG_LEVEL_DEBUG, packet->GetBuffer(), packet->GetUseSize());
				}
			}
		}
	}
	ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
	if(ioCount == 0)
		TryDisConnect(session);
	return ret;
}

bool NetServer::SendDisConnect(INT64 clientID, StreamBuffer * packet)
{
	int index = FindIndex(clientID);
	Session * session = &_sessionArray[index];
	bool ret;
	int ioCount = InterlockedIncrement((LONG *)&session->ioCountUseFlag.ioCount);
	if (ioCount != 1)
	{
		if (session->clientID == clientID)
		{
			if (session->ioCountUseFlag.useFlag == TRUE)
			{
				if (session->socket != INVALID_SOCKET)
				{
					session->disConnectFlag = true;
					packet->AddRef();
					if (!packet->_headerFillFlag)
						PutHeader(packet);
#ifdef BOOST
					session->sendQueue.push(packet);
#else
					session->sendQueue.EnQueue(packet);
#endif
					ret = SendPost(session);
				}
			}
		}
	}
	ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
	if (ioCount == 0)
		TryDisConnect(session);
	return ret;
}

/*----------------------------------------------------------*/
// NetServer::SendPost (protected)
// ���� : ������ packet�� send�õ��ϴ� �Լ�
// ���� : (Session *) ���� ������
// ���� : (bool) ���� ���� ����
/*----------------*////////////////////////*----------------*/
bool NetServer::SendPost(Session * session)
{
	// �� �����常 if������ �����Ѵ�.
	// send�� �ѹ��� �Ѵ�
	// send�� Ŀ�θ޸� ���Ǳ⶧����, ���������� �ɸ�
	if (!InterlockedCompareExchange((LONG *)&session->sendFlag, TRUE, FALSE))
	{
		if (session->sendCount != 0)
			cd.Crash();
		//sendť ��������� �ִ�.
		//send�Ϸ������ް� ���Ŀ� ���´ٸ�..Ȥ�� �װŶ����� send�� �̹� ��ų�

#ifdef BOOST
		if (session->sendQueue.empty())
		{
			session->sendFlag = FALSE;
			bool ret = true;
			if (!session->sendQueue.empty())
				ret = SendPost(session);
			return ret;
		}
		WSABUF wsaBuf[sendArraySize];
		ZeroMemory(wsaBuf, sizeof(wsaBuf));
		int bufCount = 0;
		while (bufCount < sendArraySize)
		{
			StreamBuffer * packet = nullptr;
			if (!session->sendQueue.pop(packet))
				break;
			char * buffer = packet->GetBuffer();
			int len = packet->GetUseSize();
			wsaBuf[bufCount].buf = buffer;
			wsaBuf[bufCount].len = len;
			session->sendArray[bufCount] = packet;
			bufCount++;
		}
		session->sendCount = bufCount;
#else
		int useSize = (int)session->sendQueue.GetUseCount();
		if (useSize == 0)
		{
			// �̼��� 0���� �����ؾ���
			session->sendFlag = FALSE;
			bool ret = true;
			if (session->sendQueue.GetUseCount() != 0)
				ret = SendPost(session);
			return ret;
		}
	
		WSABUF wsaBuf[sendArraySize];
		ZeroMemory(wsaBuf, sizeof(wsaBuf));
		int bufCount = min(useSize, sendArraySize);
		for(int i = 0; i < bufCount; i++)
		{
			StreamBuffer * packet = nullptr;
			session->sendQueue.DeQueue(&packet);
			wsaBuf[i].buf = packet->GetBuffer();
			wsaBuf[i].len = packet->GetUseSize();
			session->sendArray[i] = packet;
		}
		session->sendCount = bufCount;
#endif

		ZeroMemory(&session->sendOverLapped, sizeof(OVERLAPPED));

		DWORD transBytes = 0;
		DWORD flags = 0;
		InterlockedIncrement((LONG *)&session->ioCountUseFlag.ioCount);
		int retval = WSASend(session->socket, wsaBuf, bufCount, &transBytes, flags, &session->sendOverLapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			int errorCode = GetLastError();
			if (errorCode != ERROR_IO_PENDING)
			{
				if (errorCode == WSAENOBUFS)
					LOG(L"Server", LOG_ERROR, L"SessionID : %d , WSAENOBUFS", session->clientID);
				else if (errorCode == WSAECONNRESET)
					;
				else if (errorCode == WSAESHUTDOWN ||
					errorCode == WSAECONNRESET ||
					errorCode == WSAECONNABORTED)
					;//LOG(L"Server", LOG_WARNING, L"SessionID : %d , ErrorCode %d", session->clientID, errorCode);
				else
				{
					LOG(L"Server", LOG_ERROR, L"SendPost - SessionID : %d , ErrorCode %d", session->clientID, errorCode);
					//session->sendFlag = FALSE;
					//return SendPost(session);
				}
				int ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
				if (ioCount == 0)
					TryDisConnect(session);
				return false;
			}
		}
		return true;
	}
	return true;
}

/*----------------------------------------------------------*/
// NetServer::GetBlankIndex (protected)
// ���� : ���ÿ��� �ε��� ��ȣ ��������
// ���� : (int *) �ε����� ����� ����
// ���� : (bool) ���� pop ��������
/*----------------*////////////////////////*----------------*/
bool NetServer::GetBlankIndex(int * index)
{
	if (_indexStack.Pop(index))
		return true;
	return false;
}

/*----------------------------------------------------------*/
// NetServer::FindIndex (protected)
// ���� : clientID�� ���� �迭�� �ε����� ��ȯ���ִ� �Լ�
// ���� : (INT64) Ŭ���̾�ƮID
// ���� : (int) ��ȯ�� �ε���
/*----------------*////////////////////////*----------------*/
int NetServer::FindIndex(INT64 clientID)
{
	INT64 mask = 0xffff;
	return (int)(clientID & mask);
}

/*----------------------------------------------------------*/
// NetServer::FindIndex (protected)
// ���� : ���� ��Ŷ�� ����� ���δ�.
// ���� : 
// ���� : 
/*----------------*////////////////////////*----------------*/
void NetServer::PutHeader(StreamBuffer * packet)
{
	PACKET_HEADER header;
	int headerSize = sizeof(PACKET_HEADER);

	header.code = _packetCode;
	header.len = packet->GetUseSize() - headerSize;
	header.randXORKey = rand() % 256;
	header.checkSum = GetCheckSum(packet->GetBuffer() + headerSize, header.len);

	packet->FillHeader((char *)&header, sizeof(header));
	Encode(packet);
	packet->_encodeFlag = true;
}

BYTE NetServer::GetCheckSum(char * buffer, int size)
{
	BYTE checkSum = 0;
	while (size--)
	{
		checkSum += *(buffer++);
	}
	return checkSum;
}

void NetServer::XOR(char * buffer, int size, char key)
{
	while (size--)
	{
		*(buffer++) ^= key;
	}
}

void NetServer::Encode(StreamBuffer * packet)
{
	PACKET_HEADER * bufferPointer = (PACKET_HEADER *)packet->GetBuffer();

	XOR((char *)&bufferPointer->checkSum, bufferPointer->len + 1, bufferPointer->randXORKey);
	XOR((char *)&bufferPointer->randXORKey, bufferPointer->len + 2, _XORKey1);
	XOR((char *)&bufferPointer->randXORKey, bufferPointer->len + 2, _XORKey2);
}

bool NetServer::Decode(PACKET_HEADER * header, StreamBuffer * payloadPacket)
{
	char key1 = _XORKey1;
	char key2 = _XORKey2;
	char * payloadPointer = payloadPacket->GetBuffer();
	int payloadSize = payloadPacket->GetUseSize();

	XOR(payloadPointer, payloadSize, key2);
	XOR((char *)&(header->randXORKey), 2, key2);

	XOR(payloadPointer, payloadSize, key1);
	XOR((char *)&(header->randXORKey), 2, key1);

	XOR(payloadPointer, payloadSize, header->randXORKey);
	XOR((char *)&header->checkSum, 1, header->randXORKey);

	BYTE checkSum = GetCheckSum(payloadPointer, payloadSize);
	if (checkSum != header->checkSum)
	{
		LOG(L"Server", LOG_ERROR, L"Decode CheckSum Error");
		return false;
	}
	return true;
}

/*----------------------------------------------------------*/
// NetServer::RecvProc (protected)
// ���� : recv�� �Ϸ�Ǿ����� ȣ��� �Լ�
// ���� : (Session *) ���� ������
// ���� :
/*----------------*////////////////////////*----------------*/
void NetServer::RecvProc(Session * session)
{
	while (1)
	{
		PACKET_HEADER header;
		int headerSize = sizeof(header);
		int useSize = session->recvQueue.GetUseSize();
		if (useSize < headerSize)
			break;
		int ret = session->recvQueue.Peek((char *)&header, headerSize);

		if (header.code != _packetCode)
		{
			LOG(L"Server", LOG_ERROR, L"Packet Code is Wrong");
			shutdown(session->socket, SD_SEND);
			break;
		}

		if (PacketSIZE < header.len)
		{
			LOG(L"Server", LOG_ERROR, L"Packet Len is Over %d", PacketSIZE);
			shutdown(session->socket, SD_SEND);
			break;
		}

		if (useSize < header.len + headerSize)
			break;

		session->recvQueue.RemoveData(headerSize);
		// ��Ŷ�� �ϳ��� ������
		StreamBuffer * packet = PacketAlloc(NetServer);
		ret = session->recvQueue.Dequeue(packet->GetBuffer(), header.len);
		packet->MoveEndIndex(header.len);
		if(Decode(&header, packet))
			OnRecv(session->clientID, packet);
		PacketFree(packet);
	}
}

/*----------------------------------------------------------*/
// NetServer::RecvPost (protected)
// ���� : recv�� iocp�� ���
// ���� : (Session *) ���� ������
// ���� :
/*----------------*////////////////////////*----------------*/
void NetServer::RecvPost(Session * session)
{
	//���ú� ť�� �� á���� üũ
	int fullSize = session->recvQueue.GetBufferSize();
	int freeSize = session->recvQueue.GetFreeSize();
	// ���ú�ť 5% �̸� ����
	if (fullSize / 100 * 95 > freeSize)
	{
		// ����
		LOG(L"Server", LOG_ERROR, L"SessionID : %d , RecvQueue Full", session->clientID);
		shutdown(session->socket, SD_SEND);
		return;
	}
	// wsabuf ����
	WSABUF wsaBuf[2];
	wsaBuf[0].buf = session->recvQueue.GetWriteBufferPtr();
	wsaBuf[0].len = session->recvQueue.GetNotBrokenPutSize();
	wsaBuf[1].buf = session->recvQueue.GetBufferPtr();
	wsaBuf[1].len = freeSize - wsaBuf[0].len;
	//overlapped �ʱ�ȭ
	ZeroMemory(&session->recvOverLapped, sizeof(OVERLAPPED));
	//iocount++
	InterlockedIncrement((LONG *)&session->ioCountUseFlag.ioCount);
	//wsaRecv()
	DWORD transBytes = 0;
	DWORD flags = MSG_PUSH_IMMEDIATE;
	int check = 1;
	(freeSize == wsaBuf[0].len) ? (check = 1) : (check = 2);
	int retval = WSARecv(session->socket, wsaBuf, 2, &transBytes, &flags, &session->recvOverLapped, NULL);
	//����ó��
	if (retval == SOCKET_ERROR)
	{
		int errorCode = GetLastError();
		if (errorCode != ERROR_IO_PENDING)
		{
			if (errorCode == WSAENOBUFS)
				LOG(L"Server", LOG_ERROR, L"SessionID : %d , WSAENOBUFS", session->clientID);
			else if (errorCode == WSAESHUTDOWN ||
				errorCode == WSAECONNRESET ||
				errorCode == WSAECONNABORTED)
				LOG(L"Server", LOG_ERROR, L"RecvPost - SessionID : %d , ErrorCode %d", session->clientID, errorCode);
			else
			{
				LOG(L"Server", LOG_ERROR, L"RecvPost - SessionID : %d , ErrorCode %d", session->clientID, errorCode);
			}
			// ���� ��� ����, �����ڵ�
			// LOG
			int ioCount = InterlockedDecrement((LONG *)&session->ioCountUseFlag.ioCount);
			if (ioCount == 0)
				TryDisConnect(session);
		}
	}
}