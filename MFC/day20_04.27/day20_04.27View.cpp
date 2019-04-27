
// day20_04.27View.cpp: Cday200427View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "day20_04.27.h"
#endif

#include "day20_04.27Doc.h"
#include "day20_04.27View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* View: 화면 담당 */
// Cday200427View

IMPLEMENT_DYNCREATE(Cday200427View, CView)

BEGIN_MESSAGE_MAP(Cday200427View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cday200427View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// Cday200427View 생성/소멸

Cday200427View::Cday200427View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cday200427View::~Cday200427View()
{
}

BOOL Cday200427View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cday200427View 그리기

void Cday200427View::OnDraw(CDC* /*pDC*/)
{
	Cday200427Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CString strPoint;	// 문자열
	strPoint.Format(_T("마우스 좌표 (%4d, %4d)"), pos.x, pos.y);	// _T = TEXT
	dc.TextOutW(0, 0, strPoint);	// 클라이언트 좌표 0,0에 strPoint 출력
}


// Cday200427View 인쇄


void Cday200427View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cday200427View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cday200427View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cday200427View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Cday200427View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cday200427View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cday200427View 진단

#ifdef _DEBUG
void Cday200427View::AssertValid() const
{
	CView::AssertValid();
}

void Cday200427View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cday200427Doc* Cday200427View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cday200427Doc)));
	return (Cday200427Doc*)m_pDocument;
}
#endif //_DEBUG


// Cday200427View 메시지 처리기


void Cday200427View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pos = point;
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}
