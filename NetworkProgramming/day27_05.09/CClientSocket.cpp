﻿// CClientSocket.cpp: 구현 파일
//

#include "stdafx.h"
#include "day27_05.09.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include "day27_05.09Dlg.h"
// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: 여기에 구현 코드 추가.
	m_pListenSocket = pSocket;
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);

	// 클라이언트 소켓을 완전히 close한 다음에 서버쪽에서 close하기 위함.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTmp = _T("");
	CString strIpAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	GetPeerName(strIpAddress, uPortNumber);
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		Cday270509Dlg* pMain = (Cday270509Dlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s:%d] : %s"), strIpAddress, uPortNumber, szBuffer);
		pMain->m_List.AddString(strTmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer);
	}
	CSocket::OnReceive(nErrorCode);
}
