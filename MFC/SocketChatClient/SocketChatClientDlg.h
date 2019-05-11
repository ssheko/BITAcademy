
// SocketChatClientDlg.h: 헤더 파일
//

#pragma once
#include<WinSock2.h>
#include <process.h>

#pragma warning(disable:4996)
#define BUFFERSIZE 1024

// CSocketChatClientDlg 대화 상자
class CSocketChatClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CSocketChatClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETCHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int ReceiveMessage(SOCKET s);
	void DisplayMessage();
	int InitSocket(CString IPAddress);
	afx_msg void OnBnClickedButtonConnect();
	CIPAddressCtrl ctrlIPAddr;
	SOCKET sock;
//	int SendMessage();
	CEdit ctrlEditMsg;
	CListBox ctrlListMsg;
	afx_msg void OnBnClickedButtonSend();
	int SendMessageToServer();
	CButton ctrlButtonConnect;
	afx_msg void OnBnClickedOk();
	CString strEditMsg;
	CString strEditNickname;
};
