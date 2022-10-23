#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{}

CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��� Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);

}

void CTimeMgr::update()		// �� �����ӿ� �ɸ� �ð� ��
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���� ���� ���� ������ ���� ī���� ���̸� ���Ѵ�.	
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ���� ���� ī��Ʈ������ ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif // _DEBUG
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT;	// DT ����

	if (m_dAcc > 1.)
	{
		m_iFPS = m_iCallCount;

		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}