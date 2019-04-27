
// day20_04.27View.h: Cday200427View 클래스의 인터페이스
//

#pragma once


class Cday200427View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cday200427View() noexcept;
	DECLARE_DYNCREATE(Cday200427View)

// 특성입니다.
public:
	Cday200427Doc* GetDocument() const;

// 작업입니다.
public:
	// 추가된 부분
	CPoint pos;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~Cday200427View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // day20_04.27View.cpp의 디버그 버전
inline Cday200427Doc* Cday200427View::GetDocument() const
   { return reinterpret_cast<Cday200427Doc*>(m_pDocument); }
#endif

