
// Week04MFCFortressDoc.h: CWeek04MFCFortressDoc 클래스의 인터페이스
//


#pragma once


class CWeek04MFCFortressDoc : public CDocument
{
protected:
	int Angle = 70;
	int Power = 80;
	int Target = 500;

public:
	int GetAngle() { return Angle; }
	int GetPower() { return Power; }
	int GetTarget() { return Target; }

	void SetAngle(int a) {
		if (a < 90 && a > 0) {
			Angle = a;
			SetModifiedFlag();
		}
	}

	void SetPower(int a) {
		if (a < 150 && a > 0) {
			Power = a;
			SetModifiedFlag();
		}
	}

	void UpdateTarget() {
		Target = rand() % 1500 + 100;
		SetModifiedFlag();
	}

protected: // serialization에서만 만들어집니다.
	CWeek04MFCFortressDoc() noexcept;
	DECLARE_DYNCREATE(CWeek04MFCFortressDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CWeek04MFCFortressDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnTarget();
};
