#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			// ������ ������ �ð���
	double			m_dAcc;			// 1�� üũ�� ���� ������
	UINT			m_iCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS;			// �ʴ� ȣ�� Ƚ��

	// FPS (Frame Per Sec)
	// 1 �����Ӵ� �ð� (Delta Time)
	
public:
	void init();
	void update();		// �� ������ ���� ȣ���ϴ� �Լ�
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};
