
// Week04MFCFortressView.cpp: CWeek04MFCFortressView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Week04MFCFortress.h"
#endif

#include "Week04MFCFortressDoc.h"
#include "Week04MFCFortressView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeek04MFCFortressView

IMPLEMENT_DYNCREATE(CWeek04MFCFortressView, CView)

BEGIN_MESSAGE_MAP(CWeek04MFCFortressView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_FIRE, &CWeek04MFCFortressView::OnFire)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CWeek04MFCFortressView 생성/소멸

CWeek04MFCFortressView::CWeek04MFCFortressView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWeek04MFCFortressView::~CWeek04MFCFortressView()
{
}

BOOL CWeek04MFCFortressView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWeek04MFCFortressView 그리기
#define GROUND	50
#define TARGET_SIZE	100

void CWeek04MFCFortressView::OnDraw(CDC* pDC)
{
	CWeek04MFCFortressDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawBackground(pDC);
}

// CMFC03FortressView 메시지 처리기


// CWeek04MFCFortressView 인쇄

BOOL CWeek04MFCFortressView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWeek04MFCFortressView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWeek04MFCFortressView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWeek04MFCFortressView 진단

#ifdef _DEBUG
void CWeek04MFCFortressView::AssertValid() const
{
	CView::AssertValid();
}

void CWeek04MFCFortressView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWeek04MFCFortressDoc* CWeek04MFCFortressView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWeek04MFCFortressDoc)));
	return (CWeek04MFCFortressDoc*)m_pDocument;
}
#endif //_DEBUG


// CWeek04MFCFortressView 메시지 처리기


void CWeek04MFCFortressView::OnFire()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//MessageBox(L"발사");
	int x = 0, y = 0;
	CWeek04MFCFortressDoc* pDoc = GetDocument();

	int a = pDoc->GetAngle();
	int p = pDoc->GetPower();
	int target = pDoc->GetTarget();

	CRect rect;
	GetClientRect(&rect);

	CClientDC dc(this);

	//dc.Ellipse(100, 100, 300, 300);

	for (int t = 0; t < 100; t++) {
		CalculateCoordinate(a, p, t, &x, &y);
		y = rect.bottom - y - GROUND;
		if (y > rect.bottom - GROUND)
			break;

		dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
		Sleep(50);

		if ((abs(x - target) < (TARGET_SIZE / 2))
			&& (y > rect.bottom - GROUND - TARGET_SIZE)) {
			MessageBox(L"명중!");
			break;
		}

		dc.FillSolidRect(rect, RGB(255, 255, 255));
		DrawBackground(&dc);
	}

	Invalidate();
}

void CWeek04MFCFortressView::CalculateCoordinate(int angle, int power, int t, int* x, int* y)
{
	const double g = 9.8;
	const double pi = 3.141592;

	double theta = angle * pi / 180.;
	double v0 = (double)power;

	*x = v0 * t * cos(theta);
	*y = v0 * t * sin(theta) - g * t * t / 2.;
}

void CWeek04MFCFortressView::DrawBackground(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->MoveTo(rect.left, rect.bottom - GROUND);
	pDC->LineTo(rect.right, rect.bottom - GROUND);

	CWeek04MFCFortressDoc* pDoc = GetDocument();

	CString str;
	str.Format(L"Angle = %d, Power = %d", pDoc->GetAngle(), pDoc->GetPower());
	pDC->TextOutW(10, 10, str);

	// Target
	int target = pDoc->GetTarget();
	pDC->Rectangle(target - TARGET_SIZE / 2, rect.bottom - GROUND - TARGET_SIZE,
		target + TARGET_SIZE / 2, rect.bottom - GROUND);
}

void CWeek04MFCFortressView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CWeek04MFCFortressDoc* pDoc = GetDocument();

	//MessageBox(L"키가 눌렸습니다");
	switch (nChar)
	{
	case VK_UP: pDoc->SetAngle(pDoc->GetAngle() + 1); break;
	case VK_DOWN: pDoc->SetAngle(pDoc->GetAngle() - 1); break;
	case VK_LEFT: pDoc->SetPower(pDoc->GetPower() - 1); break;
	case VK_RIGHT: pDoc->SetPower(pDoc->GetPower() + 1); break;
	default:
		break;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}