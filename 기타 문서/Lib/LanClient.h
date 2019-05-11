#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <process.h>
#include "Parser.h"
#include "struct.h"
#include "LockFreeStack.h"
#include "LockFreeQueue.h"
#include "StreamBuffer.h"
#include "Clock.h"
#include "Logger.h"


#define MAXTHREADCOUNT 16

//////////////////////////////////////////////////////////////
// LanClient :
// ���� : ���� Ŭ����
//////////////////////////////////////////////////////////////
class LanClient
{
public:
#pragma pack(push, 1)   
	struct PACKET_HEADER
	{
		WORD len;
	};
#pragma pack(pop)   
	enum SERVER_STATUS
	{
		SERVER_OFF,
		SERVER_ON
	};
private:
	Parser			_configParser;						// ���Ǳ� ���� �ļ�
	Session			_sessionArray[1];			// ������ ���� �迭
	LF_Stack<int>	_indexStack;						// ���� ��������� ���� �迭 �ε����� ���� ����
	HANDLE			_iocp;								// iocp �ڵ�
	HANDLE			_acceptThread;						// accept������ �ڵ�
	HANDLE			_workerThread[MAXTHREADCOUNT];		// worker������ �ڵ� �迭
	SOCKET			_listenSocket;						// listen ����
	SERVER_STATUS	_status;							// ���� on off ���� ���
	int				_clientMAX;
	int				_monitorNo;
	int				_workerThreadCount;					// ����� worker������ ��
	INT64			_clientSeed;						// �����ϴ� client���� �� seed ��
	char			_bindIP[20];
	int				_serverPort;						// ���� ��Ʈ��ȣ
	BYTE			_packetCode;
	char			_XORKey1;
	char			_XORKey2;

	

	
	void RecvProc(Session * session);			// recv ���ν���
	void RecvPost(Session * session);			// recv ���
	bool SendPost(Session * session);			// send ���

	void TryDisConnect(Session * session);		// ������ session ����õ�
	bool GetBlankIndex(int * index);			// ���ÿ��� �ε��� ������
	int FindIndex(INT64 clientID);			// clientID�� �ε����� ��ȯ
	void PutHeader(StreamBuffer * packet);		// ��� ���̱�
	BYTE GetCheckSum(char * buffer, int size);
	void XOR(char * buffer, int size, char key);// XOR
	//void Encode(StreamBuffer * packet);			// ��ȣȭ
	//bool Decode(PACKET_HEADER * header, StreamBuffer * packet);			// ��ȣȭ

	static unsigned int WINAPI WorkerThreadMain(LPVOID lpParam); // worker������ ����
	static unsigned int WINAPI ConnectThreadMain(LPVOID lpParam); // connect������ ����
	
protected:
public:
	//����� ����
	INT64			_acceptCount;
	int				_acceptTPS;
	ULONGLONG		_acceptTPSTime;

	LanClient();
	LanClient(const char * configFile);
	virtual ~LanClient();

	bool LoadConfig(const char * configFile);
	bool Start(bool nagle = true); //���� IP / ��Ʈ / ��Ŀ������ �� / ���ۿɼ� / �ִ������� ��
	void Stop();											// ���� ����
	int GetClientCount();									// client �� ����

	bool Disconnect(INT64 clientID); // SESSION_ID		// �ܺο��� DisConnect��û
	bool SendPacket(INT64 clientID, StreamBuffer * packet); // SESSION_ID
	void Reconnect();

	virtual void OnClientJoin(INT64 ClientID, Session * session) = 0;  // < Accept �� ����ó�� �Ϸ� �� ȣ��.
	virtual void OnClientLeave(INT64 ClientID) = 0;   	           // < Disconnect �� ȣ��
	virtual bool OnConnectionRequest(char * ClientIP, int Port) = 0;        //< accept ����

	virtual void OnRecv(INT64 clientID, StreamBuffer * packet) = 0;             // < ��Ŷ ���� �Ϸ� ��
	virtual void OnSend(INT64 clientID, int sendSize) = 0;          // < ��Ŷ �۽� �Ϸ� ��

	//virtual void OnWorkerThreadBegin() = 0;                   // < ��Ŀ������ GQCS �ٷ� �ϴܿ��� ȣ��
	//virtual void OnWorkerThreadEnd() = 0;                     // < ��Ŀ������ 1���� ���� ��

	virtual void OnError(int errorCode, const WCHAR * errorMessage) = 0;
	
	virtual void OnConnect(INT64 ClientID) = 0;
};

