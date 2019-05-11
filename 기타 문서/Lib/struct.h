#pragma once
#include <strsafe.h>
#include <Mstcpip.h>
#include "StreamBuffer.h"
#include "StreamQueue.h"
#include "LockFreeQueue.h"
//#include "boost/lockfree/queue.hpp"

//#define BOOST
constexpr int sendArraySize = 200;

struct IOCOUNT_USEFLAG
{
	BOOL useFlag;
	int ioCount;								
};

struct Session
{
	WCHAR IP[16];
	SOCKET socket;								// ����
	INT64 clientID;							// Ŭ���̾�Ʈ ID
#ifdef BOOST
	boost::lockfree::queue<StreamBuffer *> sendQueue;
#else
	LF_Queue<StreamBuffer *> sendQueue;			// send�� ��Ŷ�� ���� ť
#endif
	StreamQueue recvQueue;						// recv ������
												
	OVERLAPPED sendOverLapped;					// sendoverlapped
	OVERLAPPED recvOverLapped;					// recvoverlapped
	BOOL sendFlag;								// ������ ���� �÷���
	int sendCount;								// ������ ��Ŷ ��
	LF_Queue<StreamBuffer *> sendQ;				// send�� ��Ŷ�� ��� ���� ť
	StreamBuffer * sendArray[sendArraySize];
	IOCOUNT_USEFLAG ioCountUseFlag;				// ioCount�� ����� �÷���
	bool disConnectFlag;
	Session() 
	{ 
	};
	Session(SOCKET socket, INT64 clientID)
	{
		this->socket = socket;
		this->clientID = clientID;
		ZeroMemory(&recvOverLapped, sizeof(OVERLAPPED));
		ZeroMemory(&sendOverLapped, sizeof(OVERLAPPED));
		sendFlag = FALSE;
		sendCount = 0;

		ioCountUseFlag.ioCount = 0;
		ioCountUseFlag.useFlag = FALSE;
		

		linger ling;
		ling.l_onoff = 1;
		ling.l_linger = 0;
		setsockopt(this->socket, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof(ling));

		//char opt = 0;
		//setsockopt(this->socket, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt));
	}
	~Session()
	{
	}
	void Init(SOCKET socket, INT64 clientID, WCHAR IP[16] = nullptr)
	{
		if(IP != nullptr)
			StringCchCopy(this->IP, 16, IP);
		this->clientID = clientID;
		this->socket = socket;
		ZeroMemory(&recvOverLapped, sizeof(OVERLAPPED));
		ZeroMemory(&sendOverLapped, sizeof(OVERLAPPED));
		
		for (int i = 0; i < sendCount; i++)
		{
			PacketFree(sendArray[i]);
		}
		sendCount = 0;

		recvQueue.Clear();
		disConnectFlag = false;

		linger ling;
		ling.l_onoff = 1;
		ling.l_linger = 0;
		setsockopt(this->socket, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof(ling));

		//char opt = 0;
		//setsockopt(this->socket, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt));

		char opt_val = true;
		//setsockopt(this->socket, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));

		tcp_keepalive tcpkl;

		tcpkl.onoff = 1;
		tcpkl.keepalivetime = 30000;
		tcpkl.keepaliveinterval = 2000;

		DWORD dwReturnByte;
		WSAIoctl(this->socket, SIO_KEEPALIVE_VALS, &tcpkl, sizeof(tcp_keepalive),
			0, 0, &dwReturnByte, NULL, NULL);

		DWORD opt;
		//setsockopt(this->socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&opt, sizeof(opt));
		sendFlag = FALSE;

		InterlockedIncrement((LONG *)&ioCountUseFlag.ioCount); // ��Ƽ������ ȯ�濡�� �������ڸ��� ���εǼ� ����ɼ� ����
		ioCountUseFlag.useFlag = TRUE; // TRUE�� �ٲٱ����� 1�� �÷����Ѵ�
	}
};