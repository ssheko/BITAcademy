
// day21_04.29_4Dlg.h: 헤더 파일
//

#pragma once


// Cday2104294Dlg 대화 상자
class Cday2104294Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cday2104294Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	HINSTANCE hInstance;

	int width;
	int height;
	int menuID;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY21_0429_4_DIALOG };
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
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnBnClickedButtonExit();
};
