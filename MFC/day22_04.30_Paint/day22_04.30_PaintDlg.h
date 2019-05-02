
// day22_04.30_PaintDlg.h: 헤더 파일
//

#pragma once


// Cday220430PaintDlg 대화 상자
class Cday220430PaintDlg : public CDialogEx
{
// 생성입니다.
public:
	Cday220430PaintDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY22_0430_PAINT_DIALOG };
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
	afx_msg void OnExit();
	afx_msg void OnSavefile();
	void defaultSave(LPCTSTR lpszDefExt);
	afx_msg void OnSaveasPng();
	afx_msg void OnSaveasJpeg();
	void DefaultDraw();
	bool draw_flag;
	int pen_width;
	int draw_shape;
	afx_msg void OnBnClickedButtonFreeline();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	CPen oldPen;
	CPoint oldPoint;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedButtonAirbrush();
	COLORREF penColor;
	afx_msg void OnColorRed();
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnNewfile();
	afx_msg void OnSaveasBmp();
};
