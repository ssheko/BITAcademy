
// day21_testDlg.h: 헤더 파일
//

#pragma once


// Cday21testDlg 대화 상자
class Cday21testDlg : public CDialogEx
{
// 생성입니다.
public:
	Cday21testDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY21_TEST_DIALOG };
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
	afx_msg void OnBnClickedButtonExit();
	CSliderCtrl ctrlSliderR;
	CSliderCtrl ctrlSliderG;
	CSliderCtrl ctrlSliderB;
	afx_msg void OnNMReleasedcaptureSliderR(NMHDR *pNMHDR, LRESULT *pResult);
	CString strR;
	CString strG;
	CString strB;
	int editR;
	int editG;
	int editB;
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnNMReleasedcaptureSliderg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit ctrlEditR;
	CEdit ctrlEditG;
	CEdit ctrlEditB;
	void SetImage();
	afx_msg void OnEnUpdateEditR();
	afx_msg void OnEnUpdateEditG();
	afx_msg void OnEnChangeEditB();
	void SetSliderBar();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
