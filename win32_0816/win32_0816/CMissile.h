#pragma once
#include "CObject.h"

class CTexture;

class CMissile :
    public CObject
{
private:
    float     m_fTheta; // �� �Ʒ� ����

    Vec2     m_vDir;

    CTexture* m_pTex;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CMissile);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMissile();
    ~CMissile();
};
