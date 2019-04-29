
// day21_04.29_6View.cpp: Cday2104296View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "day21_04.29_6.h"
#endif

#include "day21_04.29_6Doc.h"
#include "day21_04.29_6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cday2104296View

IMPLEMENT_DYNCREATE(Cday2104296View, CView)

BEGIN_MESSAGE_MAP(Cday2104296View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cday2104296View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cday2104296View 생성/소멸

Cday2104296View::Cday2104296View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cday2104296View::~Cday2104296View()
{
}

BOOL Cday2104296View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cday2104296View 그리기

void Cday2104296View::OnDraw(CDC* /*pDC*/)
{
	Cday2104296Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// Cday2104296View 인쇄


void Cday2104296View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cday2104296View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cday2104296View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cday2104296View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Cday2104296View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cday2104296View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cday2104296View 진단

#ifdef _DEBUG
void Cday2104296View::AssertValid() const
{
	CView::AssertValid();
}

void Cday2104296View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cday2104296Doc* Cday2104296View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cday2104296Doc)));
	return (Cday2104296Doc*)m_pDocument;
}
#endif //_DEBUG


// Cday2104296View 메시지 처리기
