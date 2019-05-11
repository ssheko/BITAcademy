// CListenSocket.cpp: 구현 파일
//

#include "stdafx.h"
#include "day27_05.09.h"
#include "CListenSocket.h"
#include "CClientSocket.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	}
	else {
		delete pClient;
		AfxMessageBox(_T("ERROR: Failed to accept new client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;	// 어떤 구조체여도 포인터를 받을 수 있음. POSITION의 내부가 비어있기 때문에.
	pos = m_ptrClientSocketList.Find(pClient);
	if (pos != NULL)
	{
		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}
		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}


void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		// Head 다음 첫 번째 값을 받아오고, pos는 그 다음(방금 가져온 첫 번째 값의 위치)으로 자동으로 이동.
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			// 유니코드는 글자의 길이. 실제 byte는 글자 길이 *2 \
				ex) 가나다 -> 유니코드 = 3, 실제 byte = 6
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);	// 유니코드 사용
		}
	}
}
