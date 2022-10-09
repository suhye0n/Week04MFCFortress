
// Week04MFCFortressView.h: CWeek04MFCFortressView 클래스의 인터페이스
//

#pragma once


class CWeek04MFCFortressView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWeek04MFCFortressView() noexcept;
	DECLARE_DYNCREATE(CWeek04MFCFortressView)

// 특성입니다.
public:
	CWeek04MFCFortressDoc* GetDocument() const;

// 작업입니다.
public:

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
	virtual ~CWeek04MFCFortressView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFire();
	void CalculateCoordinate(int angle, int power, int t, int* x, int* y);
	void DrawBackground(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // Week04MFCFortressView.cpp의 디버그 버전
inline CWeek04MFCFortressDoc* CWeek04MFCFortressView::GetDocument() const
   { return reinterpret_cast<CWeek04MFCFortressDoc*>(m_pDocument); }
#endif

