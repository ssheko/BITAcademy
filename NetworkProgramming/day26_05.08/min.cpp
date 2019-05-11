#include "min.h"

void MyServer::OnClientJoin(INT64 ClientID, Session * session)
{
	USER *new_user = new USER;
	new_user->id = ClientID;
	
	clientMap.insert(make_pair(ClientID, new_user));
}

void MyServer::OnClientLeave(INT64 ClientID)
{
	USER *del = clientMap[ClientID];
	clientMap.erase(ClientID);
	delete del;
}

bool MyServer::OnConnectionRequest(WCHAR * ClientIP, int Port)
{
	return true;
}

void MyServer::OnRecv(INT64 clientID, StreamBuffer * packet)
{
	WORD type;
	*packet >> type;	// 2byte ������
	switch (type) {
	case 0:
		// �г��� ��Ŷ
		packet->Out(clientMap[clientID]->name, SIZE);
		break;
	case 1:
	{
		// ������ ��Ŷ
		auto iterator = clientMap.begin();
		for (; iterator != clientMap.end(); ++iterator)
		{

		}
	}
		break;
	default:
		break;
	}
}

void MyServer::OnSend(INT64 clientID, int sendSize)
{
}

void MyServer::OnError(int errorCode, const WCHAR * errorMessage)
{
}
