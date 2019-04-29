
// day21_testDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "day21_test.h"
#include "day21_testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cday21testDlg 대화 상자



Cday21testDlg::Cday21testDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAY21_TEST_DIALOG, pParent)
	, strR(_T(""))
	, strG(_T(""))
	, strB(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cday21testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_R, ctrlSliderR);
	DDX_Control(pDX, IDC_SLIDER_g, ctrlSliderG);
	DDX_Control(pDX, IDC_SLIDER_B, ctrlSliderB);
	DDX_Text(pDX, IDC_EDIT_R, strR);
	DDX_Text(pDX, IDC_EDIT_G, strG);
	DDX_Text(pDX, IDC_EDIT_B, strB);
	DDX_Control(pDX, IDC_EDIT_R, ctrlEditR);
	DDX_Control(pDX, IDC_EDIT_G, ctrlEditG);
	DDX_Control(pDX, IDC_EDIT_B, ctrlEditB);
}

BEGIN_MESSAGE_MAP(Cday21testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &Cday21testDlg::OnBnClickedButtonExit)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_R, &Cday21testDlg::OnNMReleasedcaptureSliderR)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &Cday21testDlg::OnBnClickedButtonClear)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_g, &Cday21testDlg::OnNMReleasedcaptureSliderg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_B, &Cday21testDlg::OnNMReleasedcaptureSliderB)
	ON_WM_CTLCOLOR()
	ON_EN_UPDATE(IDC_EDIT_R, &Cday21testDlg::OnEnUpdateEditR)
	ON_EN_UPDATE(IDC_EDIT_G, &Cday21testDlg::OnEnUpdateEditG)
	ON_EN_CHANGE(IDC_EDIT_B, &Cday21testDlg::OnEnChangeEditB)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Cday21testDlg 메시지 처리기

BOOL Cday21testDlg::OnInitDialog()
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
	ctrlSliderR.SetRange(0, 255);	// slider 전체 크기
	ctrlSliderG.SetRange(0, 255);
	ctrlSliderB.SetRange(0, 255);

	ctrlSliderR.SetPos(0);	// slider 초기 위치
	ctrlSliderG.SetPos(0);	
	ctrlSliderB.SetPos(0);

	strR = _T("0");
	strG = _T("0");
	strB = _T("0");

	ctrlSliderR.SetTicFreq(10);	// slider 눈금 간격
	ctrlSliderG.SetTicFreq(10);	
	ctrlSliderB.SetTicFreq(10);	
	
	ctrlSliderR.SetSelection(40, 200);	// slider focus ragne
	ctrlSliderG.SetSelection(40, 200);	
	ctrlSliderB.SetSelection(40, 200);	
	SetImage();
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cday21testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cday21testDlg::OnPaint()
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
/*
		CPaintDC dc(this);
		HDC hDC = dc.m_hDC;

		CRect rcWindow;
		GetClientRect(rcWindow);

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		
		*/
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cday21testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cday21testDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void Cday21testDlg::OnNMReleasedcaptureSliderR(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	strR.Format(_T("%d"), ctrlSliderR.GetPos());	// 현재 슬라이더의 위치를 가져옴
	editR = ctrlSliderR.GetPos();
	SetImage();
	UpdateData(FALSE);
}



void Cday21testDlg::OnNMReleasedcaptureSliderg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	strG.Format(_T("%d"), ctrlSliderG.GetPos());	// 현재 슬라이더의 위치를 가져옴
	
	//editG = ctrlSliderG.GetPos();
	SetImage();
	UpdateData(FALSE);
}


void Cday21testDlg::OnNMReleasedcaptureSliderB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	strB.Format(_T("%d"), ctrlSliderB.GetPos());	// 현재 슬라이더의 위치를 가져옴
	//editB = ctrlSliderB.GetPos();
	SetImage();
	UpdateData(FALSE);
}


void Cday21testDlg::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ctrlSliderR.SetPos(0);	// slider 초기 위치
	ctrlSliderG.SetPos(0);
	ctrlSliderB.SetPos(0);

	strR = _T("0");
	strG = _T("0");
	strB = _T("0");
	SetImage();
	UpdateData(FALSE);
}

HBRUSH Cday21testDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void Cday21testDlg::SetImage()
{
	// TODO: 여기에 구현 코드 추가.	
	int R, G, B;

	R = ctrlSliderR.GetPos();
	G = ctrlSliderG.GetPos();
	B= ctrlSliderB.GetPos();
	//SetDlgItemInt(IDC_EDIT_R, R);
	//SetDlgItemInt(IDC_EDIT_G, G);
	//SetDlgItemInt(IDC_EDIT_B, B);

	CStatic* pImage = (CStatic*)GetDlgItem(IDC_STATIC_VIEW);
	CRect rt;
	pImage->GetClientRect(&rt);
	CClientDC dc(pImage);
	
	CBrush myBrush, *oldBrush;

	myBrush.CreateSolidBrush(RGB(R, G, B));
	oldBrush = dc.SelectObject(&myBrush);

	dc.FillRect(&rt, &myBrush);	// fillRect Rect에 myBrush로 색칠
	dc.SelectObject(&oldBrush);

	myBrush.DeleteObject();
	
}


void Cday21testDlg::OnEnUpdateEditR()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	TCHAR* tchr;
	CString str = _T("");
	int i;

	// 현재 edit control에 입력된 문자에 대해
	//for (i = 0; i < strR.GetLength(); i++)
	//{
	//	str = strR.Mid(i, 1);
	//	tchr = (TCHAR*)(LPCTSTR)str;

	//	if (!IsCharAlphaNumeric(*tchr))	// 만약 i번째 문자열이 숫자가 아니라면
	//	{
	//		// 숫자만 허용된다는 메세지 출력
	//		AfxMessageBox(_T("숫자만 입력 가능합니다."));
	//		// 해당 문자열 삭제
	//		strR.Remove(*tchr);
	//	}

	//}
	if (_ttoi(strR) > 255) {
		strR = _T("255");
		AfxMessageBox(_T("255까지만 입력 가능합니다."));
	}
	ctrlSliderR.SetPos(_ttoi(strR));
	SetImage();
	// 업데이트된 변수를 Edit Control로 전송
	UpdateData(FALSE);
	// 문자열의 문자를 모두 선택하고
	ctrlEditR.SetSel(0, -1);
	// 커서를 마지막 문자열 다음으로 이동
	ctrlEditR.SetSel(-1, -1);

}


void Cday21testDlg::OnEnUpdateEditG()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	TCHAR* tchr;
	CString str = _T("");
	int i;

	// 현재 edit control에 입력된 문자에 대해
	for (i = 0; i < strG.GetLength(); i++)
	{
		str = strG.Mid(i, 1);
		tchr = (TCHAR*)(LPCTSTR)str;

		if (!IsCharAlphaNumeric(*tchr))	// 만약 i번째 문자열이 숫자가 아니라면
		{
			// 숫자만 허용된다는 메세지 출력
			AfxMessageBox(_T("숫자만 입력 가능합니다."));
			// 해당 문자열 삭제
			strG.Remove(*tchr);
		}

	}
	if (_ttoi(strG) > 255) {
		strG = _T("255");
		AfxMessageBox(_T("255까지만 입력 가능합니다."));
	}
	ctrlSliderG.SetPos(_ttoi(strG));
	SetImage();
	// 업데이트된 변수를 Edit Control로 전송
	UpdateData(FALSE);
	// 문자열의 문자를 모두 선택하고
	ctrlEditG.SetSel(0, -1);
	// 커서를 마지막 문자열 다음으로 이동
	ctrlEditG.SetSel(-1, -1);

}


void Cday21testDlg::OnEnChangeEditB()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	TCHAR* tchr;
	CString str = _T("");
	int i;

	// 현재 edit control에 입력된 문자에 대해
	for (i = 0; i < strB.GetLength(); i++)
	{
		str = strB.Mid(i, 1);
		tchr = (TCHAR*)(LPCTSTR)str;

		if (!IsCharAlphaNumeric(*tchr))	// 만약 i번째 문자열이 숫자가 아니라면
		{
			// 숫자만 허용된다는 메세지 출력
			AfxMessageBox(_T("숫자만 입력 가능합니다."));
			// 해당 문자열 삭제
			strB.Remove(*tchr);
		}

	}
	if (_ttoi(strB) > 255) {
		strB = _T("255");
		AfxMessageBox(_T("255까지만 입력 가능합니다."));
	}
	ctrlSliderB.SetPos(_ttoi(strB));
	SetImage();
	// 업데이트된 변수를 Edit Control로 전송
	UpdateData(FALSE);
	// 문자열의 문자를 모두 선택하고
	ctrlEditB.SetSel(0, -1);
	// 커서를 마지막 문자열 다음으로 이동
	ctrlEditB.SetSel(-1, -1);

}


void Cday21testDlg::SetSliderBar()
{
	// TODO: 여기에 구현 코드 추가.

	strR.Format(_T("%d"), ctrlSliderR.GetPos());
	strG.Format(_T("%d"), ctrlSliderG.GetPos());
	strB.Format(_T("%d"), ctrlSliderB.GetPos());
}


void Cday21testDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar != NULL && pScrollBar->m_hWnd == ctrlSliderR.m_hWnd) {
		//strR.Format(_T("%d"), ctrlSliderR.GetPos());
		SetDlgItemInt(IDC_EDIT_R, ctrlSliderR.GetPos());
	}
	if (pScrollBar != NULL && pScrollBar->m_hWnd == ctrlSliderG.m_hWnd) {
		//strG.Format(_T("%d"), ctrlSliderG.GetPos());
		SetDlgItemInt(IDC_EDIT_G, ctrlSliderG.GetPos());
	}
	if (pScrollBar != NULL && pScrollBar->m_hWnd == ctrlSliderB.m_hWnd) {
		//strB.Format(_T("%d"), ctrlSliderB.GetPos());
		SetDlgItemInt(IDC_EDIT_B, ctrlSliderB.GetPos());
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
