#pragma once
#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CColliderCapsule.h"

class CXPlayer :public CXCharacter {
public:
	void Collision(CCollider* m, CCollider* o);
	void Init(CModelX* model);
	CXPlayer();
	void Update();
private:
	CColliderCapsule mColBody;//��
	CCollider mColSphereBody;//��
	CCollider mColSphereHead;//��
	CCollider mColSphereSword;//��
	CInput mInput;
};
#endif