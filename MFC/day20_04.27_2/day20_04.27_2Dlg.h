
// day20_04.27_2Dlg.h: 헤더 파일
//

#pragma once


// Cday2004272Dlg 대화 상자
class Cday2004272Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cday2004272Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY20_0427_2_DIALOG };
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
	afx_msg void OnBnClickedButtontest();
	afx_msg void OnBnClickedButtonexit();
	afx_msg void OnBnClickedButtonYn();
	afx_msg void OnBnClickedButtonOc();
	CEdit e;
	afx_msg void OnDestroy();
	CString strTest;
};
