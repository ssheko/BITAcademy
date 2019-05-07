#pragma once


// ConnectDlg 대화 상자

class ConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectDlg)

public:
	ConnectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConnectDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonConnects();
//	CString m_ipaddress;
	CString m_ipaddress;	// IP 컨트롤에 입력받은 서버의 IP 주소를 저장할 변수
};
