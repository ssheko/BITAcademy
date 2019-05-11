#pragma once

// CListenSocket 명령 대상

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	// 객체, 구조체의 포인터를 관리할 수 있는 컨테이너.\
		링크드리스트로 구현되어 있음.\
		생성되는 소켓을 관리하기 위함.
	CPtrList m_ptrClientSocketList;	
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);
};


