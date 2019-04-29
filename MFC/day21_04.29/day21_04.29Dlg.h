
// day21_04.29Dlg.h: 헤더 파일
//

#pragma once
#include "CInputDlg.h"

// Cday210429Dlg 대화 상자
class Cday210429Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cday210429Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CInputDlg inputDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY21_0429_DIALOG };
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
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonOutput();
};
