
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "day21_04.29_3.h"
#include "ChildView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FIG_CIR, &CChildView::OnFigCir)
	ON_COMMAND(ID_FIG_RECT, &CChildView::OnFigRect)
	ON_COMMAND(ID_FIG_CROSS, &CChildView::OnFigCross)
	ON_COMMAND(ID_FIG_APPLE, &CChildView::OnFigApple)
	ON_COMMAND(ID_FIG_LINE, &CChildView::OnFigLine)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CFont font, *pOldFont;
	font.CreatePointFont(300, _T("Broadway"));
	pOldFont = (CFont *)dc.SelectObject(&font);
	CString strInput1 = _T(" < < Input Data > > ");
	CString strInput2 = pMainFrame->GetText();
	dc.SetTextColor(RGB(0, 0, 0));
	dc.TextOutW(0, 20, strInput1);
	// 추가 시작
	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetTextColor(pMainFrame->ColorGet());

	dc.TextOutW(50,100, strInput2);

	
	switch (option)
	{
	case 1:
	{
		CBrush brush(RGB(0, 255, 0));
		dc.SelectObject(&brush);
		dc.Ellipse(200, 200, 400, 400);
		brush.DeleteObject();
		break;
	}
	case 2:
	{
		CBrush brush(RGB(150, 0, 150));
		dc.SelectObject(&brush);
		dc.Rectangle(200, 200, 400, 400);
		brush.DeleteObject();
		break;
	}
	case 3:
	{
		int nPenType[] = { PS_SOLID, PS_DOT, PS_DASHDOT, PS_DASH, PS_DASHDOT };

		for (int i = 0; i < sizeof(nPenType) / sizeof(nPenType[0]); i++)
		{
			CPen pen(nPenType[i], 1, RGB(0, 0, 255));
			dc.SelectObject(&pen);
			
			dc.MoveTo(100, 200 + i * 50);
			dc.LineTo(500, 200 + i * 50);

			pen.DeleteObject();
		}
		break;
	}
	case 4:
	{
		CBrush brush(HS_DIAGCROSS, RGB(255, 90, 0));
		dc.SelectObject(&brush);
		dc.RoundRect(200, 200, 400, 400, 50, 50);
		brush.DeleteObject();
		break;
	}
	case 5:
	{
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP1);
		CBrush brush(&bitmap);
		dc.SelectObject(&brush);
		dc.SetBkColor(TRANSPARENT);
		dc.RoundRect(200, 200, 400, 400, 50, 50);
		brush.DeleteObject();
		break;
	}
	}
}

void CChildView::OnFigCir()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	option = 1;
	Invalidate();
}


void CChildView::OnFigRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	option = 2;
	Invalidate();
}


void CChildView::OnFigLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	option = 3;
	Invalidate();
}


void CChildView::OnFigCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	option = 4;
	Invalidate();
}


void CChildView::OnFigApple()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	option = 5;
	Invalidate();
}
