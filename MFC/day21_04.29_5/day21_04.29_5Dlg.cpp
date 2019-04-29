
// day21_04.29_5Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "day21_04.29_5.h"
#include "day21_04.29_5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

int numberOfSelected;
int nIndex = 0;
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


// Cday2104295Dlg 대화 상자



Cday2104295Dlg::Cday2104295Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAY21_0429_5_DIALOG, pParent)
	, strNum(_T(""))
	, strName(_T(""))
	, strCell(_T(""))
	, chA(FALSE)
	, chB(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cday2104295Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, strNum);
	DDX_Text(pDX, IDC_EDIT_NAME, strName);
	DDX_Text(pDX, IDC_EDIT_CELL, strCell);
	DDX_Check(pDX, IDC_CHECK_A, chA);
	DDX_Check(pDX, IDC_CHECK_B, chB);
	DDX_Control(pDX, IDC_RADIO_ONLINE, online);
	DDX_Control(pDX, IDC_RADIO_OFFLINE, offline);
	DDX_Control(pDX, IDC_COMBO_POINT1, cbPoint1);
	DDX_Control(pDX, IDC_COMBO_POINT2, cbPoint2);
	DDX_Control(pDX, IDC_LIST_VIEW, listView);
}

BEGIN_MESSAGE_MAP(Cday2104295Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &Cday2104295Dlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &Cday2104295Dlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &Cday2104295Dlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &Cday2104295Dlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// Cday2104295Dlg 메시지 처리기

BOOL Cday2104295Dlg::OnInitDialog()
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
	for (int i = 0; i < 11; i++)
	{
		CString sIndex;
		sIndex.Format(_T("%d"), i);
		cbPoint1.AddString(sIndex);
	}
	for (int i = 0; i < 11; i++)
	{
		CString sIndex;
		sIndex.Format(_T("%d"), i);
		cbPoint2.AddString(sIndex);
	}

	TCHAR *szText[6] = { _T("학번"), _T("이름"), _T("연락처"), _T("등록방법"), _T("시험유형"), _T("총배점") };
	int nWidth[6] = { 50,70,100,70,70,70 };

	LV_COLUMN iCol;
	iCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	iCol.fmt = LVCFMT_LEFT;

	/* typedef struct _LVCOLUMN {
		UINT mask;
		int fmt;
		int cx;
		LPTSTR pszText;
		int cchTextMax;
		int iSubItem;
		}	LVCOLUMN
	
		-Mask : 각 멤버가 유효한 정보를 가지고 있는지를 명시하는 변수
			LVCF_FMT : fmt 변수가 유효한지
			LVCF_SUBITEM : iSubItem 변수가 유효한지
			LVCF_TEXT : pszText 변수가 유효한지
			LVCF_WIDTH : cx 변수가 유효한지
			LVCF_IMAGE : iImage 변수가 유효한지
			LVCF_ORDER : iOrder 변수가 유효한지
		- fmf : 컬럼 헤딩과 컬럼 안의 부 아이템의 정렬
			LVCFMT_CENTER, LVCFMT_LEFT, LVCFMT_RIGHT
			LVCFMT_BITMAP_ON_RIGHT, LVCFMT_IMAGE
		- CX : 컬럼의 너비(단위 : Pixel)
		- pszText : 컬럼 제목의 문자열
		- cchTextMax : 칼럼 제목 문자열의 버퍼 크기
		- iSubItem : 컬럼에 연관되는 부 아이템의 색인*/

	listView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	for (int i = 0; i < 6; i++)
	{
		iCol.pszText = (LPTSTR)szText[i];
		iCol.cx = nWidth[i];
		listView.InsertColumn(i, &iCol);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cday2104295Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cday2104295Dlg::OnPaint()
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
HCURSOR Cday2104295Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cday2104295Dlg::Init()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData();
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_NUM);

	strNum.Empty();
	strName.Empty();
	strCell.Empty();

	chA = chB = FALSE;

	online.SetCheck(BST_UNCHECKED);

	cbPoint1.SetCurSel(0);
	cbPoint2.SetCurSel(0);

	pEdit->SetFocus();

	UpdateData(FALSE);
}


void Cday2104295Dlg::OnBnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szText[100] = _T("");

	UpdateData();
	LVITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = nIndex;
	/*LVITEM
	- List view 에서 속성을 받는 구조체
	¨ LVITEM의 멤버 변수
	- mask : 각 멤버가 유효한 정보를 가지고 있는지를 명시하는 변수
	- iItem : 구조체를 참조하는 아이템의 제로 베이스 색인
	- iSubItem : 컬럼 정보
	- pszText : 아이템 텍스트를 명시하는 스트링의 주소*/

	item.iSubItem = 0;
	wsprintf(szText, _T("%s"), strNum);
	item.pszText = (LPTSTR)szText;
	listView.InsertItem(&item);

	item.iSubItem = 1;
	wsprintf(szText, _T("%s"), strName);
	item.pszText = (LPTSTR)szText;
	listView.SetItem(&item);

	item.iSubItem = 2;
	wsprintf(szText, _T("%s"), strCell);
	item.pszText = (LPTSTR)szText;
	listView.SetItem(&item);

	item.iSubItem = 3;
	if (online.GetCheck() == BST_CHECKED)
		wsprintf(szText, _T("%s"), _T("온라인"));
	else
		wsprintf(szText, _T("%s"), _T("방문등록"));

	item.pszText = (LPTSTR)szText;
	listView.SetItem(&item);

	CString selCombo1, selCombo2;

	if (chA == TRUE && chB == FALSE)
	{
		cbPoint1.GetLBText(cbPoint1.GetCurSel(), selCombo1);

		int cb = _ttoi(selCombo1);
		int sum = cb * 20;

		item.iSubItem = 4;
		wsprintf(szText, _T("%s"), _T("주관식"));
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);

		item.iSubItem = 5;
		wsprintf(szText, _T("%d"), sum);
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);
	}
	else if (chA == FALSE && chB == TRUE) {
		cbPoint2.GetLBText(cbPoint2.GetCurSel(), selCombo2);

		int cb = _ttoi(selCombo2);
		int sum = cb * 10;

		item.iSubItem = 4;
		wsprintf(szText, _T("%s"), _T("주관식"));
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);

		item.iSubItem = 5;
		wsprintf(szText, _T("%d"), sum);
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);
	}
	else if (chA == TRUE && chB == TRUE) {
		cbPoint1.GetLBText(cbPoint1.GetCurSel(), selCombo1);
		cbPoint2.GetLBText(cbPoint2.GetCurSel(), selCombo2);

		int cb1 = _ttoi(selCombo1);
		int cb2 = _ttoi(selCombo2);
		int sum = cb1 * 20 + cb2 * 10;

		item.iSubItem = 4;
		wsprintf(szText, _T("%s"), _T("주관식"));
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);

		item.iSubItem = 5;
		wsprintf(szText, _T("%d"), sum);
		item.pszText = (LPTSTR)szText;
		listView.SetItem(&item);
	}
	else if (chA == FALSE && chB == FALSE)
		MessageBox(_T("시험 유형을 선택하세요"), _T("입력에러"), MB_ICONSTOP | MB_OK);

	Init();
	nIndex++;
	UpdateData(FALSE);
		

}


void Cday2104295Dlg::OnBnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int nItem = 0; nItem < listView.GetItemCount();)
	{
		if (listView.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
			listView.DeleteItem(nItem);
		else
			++nItem;
	}
	UpdateData(FALSE);
	nIndex--;
}


void Cday2104295Dlg::OnBnClickedButtonInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Init();

}


void Cday2104295Dlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
