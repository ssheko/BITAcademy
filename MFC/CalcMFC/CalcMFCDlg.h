
// CalcMFCDlg.h: 헤더 파일
//

#pragma once


// CCalcMFCDlg 대화 상자
class CCalcMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CCalcMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCMFC_DIALOG };
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
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonEq();
	afx_msg void OnBnClickedButtonInit();
	CString strFirst;
	CString strSecond;
	CString strResult;
	CString strOp;
	CEdit editFirst;
	CEdit editSecond;
	//int WINAPI Calculate2(int fir, int sec, CString &op);
};
