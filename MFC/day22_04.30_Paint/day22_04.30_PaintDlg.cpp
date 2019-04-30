
// day22_04.30_PaintDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "day22_04.30_Paint.h"
#include "day22_04.30_PaintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum Shape{ ID_FREELINE, ID_AIRBRUSH, ID_ELLIPSE, ID_LINE };
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnColorRed();
//	afx_msg void OnColorBlue();
//	afx_msg void OnColorGreen();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_COLOR_RED, &CAboutDlg::OnColorRed)
//	ON_COMMAND(ID_COLOR_BLUE, &CAboutDlg::OnColorBlue)
//	ON_COMMAND(ID_COLOR_GREEN, &CAboutDlg::OnColorGreen)
END_MESSAGE_MAP()


// Cday220430PaintDlg 대화 상자



Cday220430PaintDlg::Cday220430PaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAY22_0430_PAINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cday220430PaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cday220430PaintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EXIT, &Cday220430PaintDlg::OnExit)
	ON_COMMAND(ID_SAVEFILE, &Cday220430PaintDlg::OnSavefile)
	ON_COMMAND(ID_SAVEAS_PNG, &Cday220430PaintDlg::OnSaveasPng)
	ON_COMMAND(ID_SAVEAS_JPEG, &Cday220430PaintDlg::OnSaveasJpeg)
	ON_BN_CLICKED(IDC_BUTTON_FREELINE, &Cday220430PaintDlg::OnBnClickedButtonFreeline)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON_AIRBRUSH, &Cday220430PaintDlg::OnBnClickedButtonAirbrush)
	ON_COMMAND(ID_COLOR_RED, &Cday220430PaintDlg::OnColorRed)
	ON_COMMAND(ID_COLOR_BLUE, &Cday220430PaintDlg::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &Cday220430PaintDlg::OnColorGreen)
	ON_COMMAND(ID_NEWFILE, &Cday220430PaintDlg::OnNewfile)
END_MESSAGE_MAP()


// Cday220430PaintDlg 메시지 처리기

BOOL Cday220430PaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cday220430PaintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cday220430PaintDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cday220430PaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cday220430PaintDlg::OnExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnOK();
}


void Cday220430PaintDlg::OnSavefile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void Cday220430PaintDlg::defaultSave(LPCTSTR lpszDefExt)
{
	// TODO: 여기에 구현 코드 추가.
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	// TRUE: 파일 열기, 
	CFileDialog dlg(TRUE, lpszDefExt, _T("image"), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		CString pathName = dlg.GetPathName();
		CString fileSave;
		// edit에 있는 값을 가져와서 
		fileSave.Format(L"%s%s", pathName, lpszDefExt);

		HANDLE hFile;
		DWORD dwRead;

		// 파일 저장 시작
		hFile = CreateFile(fileSave, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		//WriteFile(hFile, )


		MessageBox(pathName);
	}
}


void Cday220430PaintDlg::OnSaveasPng()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	defaultSave(_T("*.png"));
}


void Cday220430PaintDlg::OnSaveasJpeg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	defaultSave(_T("*.jpg"));
}



void Cday220430PaintDlg::DefaultDraw()
{
	// TODO: 여기에 구현 코드 추가.
	if (draw_flag == FALSE) return;
	CClientDC dc(this);
	CPen myPen(PS_SOLID, pen_width, RGB(0, 255, 0));
	CPen *pOldPen = dc.SelectObject(&myPen);
	//switch (draw_shape)
	//{
	//case ID_FREELINE:	// 자유선그리기
	//	dc.MoveTo()
	//		break;
	//}
}


void Cday220430PaintDlg::OnBnClickedButtonFreeline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	draw_shape = ID_FREELINE;
}


void Cday220430PaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_LBUTTON) {
		if (draw_flag) {
			CClientDC dc(this);
			CPen myPen;
			switch (draw_shape) {
			case ID_FREELINE:
				myPen.CreatePen(PS_SOLID, pen_width, penColor);
				break;
			case ID_AIRBRUSH:
				myPen.CreatePen(PS_DOT, pen_width, penColor);
				break;
			}
			CPen *oldPen = dc.SelectObject(&myPen);

			dc.MoveTo(oldPoint);
			dc.LineTo(point);
			oldPoint = point;

			dc.SelectObject(oldPen);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void Cday220430PaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	oldPoint = point;

	draw_flag = TRUE;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void Cday220430PaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	draw_flag = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void Cday220430PaintDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


void Cday220430PaintDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu popup;
	CMenu *pMenu;
	
	popup.LoadMenuW(IDR_MENU_COLOR);
	pMenu = popup.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN || TPM_RIGHTBUTTON, point.x, point.y, this);
}


void Cday220430PaintDlg::OnBnClickedButtonAirbrush()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	draw_shape = ID_AIRBRUSH;
}

void Cday220430PaintDlg::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	penColor = RGB(255, 0, 0);
}


void Cday220430PaintDlg::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	penColor = RGB(0, 0, 255);
}


void Cday220430PaintDlg::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	penColor = RGB(0, 255, 0);
}


void Cday220430PaintDlg::OnNewfile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Invalidate(TRUE);
}
