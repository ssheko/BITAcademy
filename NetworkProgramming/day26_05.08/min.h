#pragma once
#pragma comment(lib, "MinLib")
#include "LanServer.h"
#include <map>

#define SIZE 100

struct USER {
	INT64 id;
	TCHAR name[SIZE];
};

class MyServer : public LanServer {
	map<INT64, USER*> clientMap;

	// LanServer을(를) 통해 상속됨
	virtual void OnClientJoin(INT64 ClientID, Session * session) override;
	virtual void OnClientLeave(INT64 ClientID) override;
	virtual bool OnConnectionRequest(WCHAR * ClientIP, int Port) override;
	virtual void OnRecv(INT64 clientID, StreamBuffer * packet) override;
	virtual void OnSend(INT64 clientID, int sendSize) override;
	virtual void OnError(int errorCode, const WCHAR * errorMessage) override;
};