#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "resource.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{
	// 마찬가지로 윈도우 핸들로 얻어은 DC는 ReleaseDC로 지우기
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기를 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WIN320816));

	m_hDC = GetDC(m_hWnd);		// DC가 그릴 목적지
								// 윈도우가 보유한 비트맵을 이 DC가 그리기 목적지로 삼는다.

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 자주 사용할 펜 및 브러쉬 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// 충돌 체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();

	//=========
	//Rendering
	//=========
	// 화면 Clear
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// ================
	// 이벤트 지연 처리
	// ================
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	// black brush
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(BS_SOLID, 1, RGB(255, 0, 0));
	// green pen
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(BS_SOLID, 1, RGB(0, 255, 0));
	// blue pen
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(BS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0 ,0, (long)_vResolution.x, (long)_vResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

