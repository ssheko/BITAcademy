
// day21_04.29_5Dlg.h: 헤더 파일
//

#pragma once


// Cday2104295Dlg 대화 상자
class Cday2104295Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cday2104295Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY21_0429_5_DIALOG };
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
	CString strNum;
	CString strName;
	CString strCell;
	BOOL chB;
	BOOL chA;
	CButton online;
	CButton offline;
	CComboBox cbPoint1;
	CComboBox cbPoint2;
	CListCtrl listView;
	void Init();
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonExit();
};
