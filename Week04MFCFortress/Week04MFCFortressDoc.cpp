
// Week04MFCFortressDoc.cpp: CWeek04MFCFortressDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Week04MFCFortress.h"
#endif

#include "Week04MFCFortressDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWeek04MFCFortressDoc

IMPLEMENT_DYNCREATE(CWeek04MFCFortressDoc, CDocument)

BEGIN_MESSAGE_MAP(CWeek04MFCFortressDoc, CDocument)
	//ON_COMMAND(IDM_TARGET, &CWeek04MFCFortressDoc::OnTarget)
END_MESSAGE_MAP()


// CWeek04MFCFortressDoc 생성/소멸

CWeek04MFCFortressDoc::CWeek04MFCFortressDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CWeek04MFCFortressDoc::~CWeek04MFCFortressDoc()
{
}

BOOL CWeek04MFCFortressDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	Angle = 70;
	Power = 80;
	Target = 500;

	return TRUE;
}

// CWeek04MFCFortressDoc serialization

void CWeek04MFCFortressDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << Angle;
		ar << Power;
		ar << Target;
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		ar >> Angle;
		ar >> Power;
		ar >> Target;
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CWeek04MFCFortressDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CWeek04MFCFortressDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWeek04MFCFortressDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWeek04MFCFortressDoc 진단

#ifdef _DEBUG
void CWeek04MFCFortressDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWeek04MFCFortressDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWeek04MFCFortressDoc 명령
void CWeek04MFCFortressDoc::OnTarget()
{
	Target = rand() % 1500 + 100;

	SetModifiedFlag();

	UpdateAllViews(NULL);
}