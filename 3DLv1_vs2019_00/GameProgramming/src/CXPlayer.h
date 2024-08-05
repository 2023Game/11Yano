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
	CColliderCapsule mColBody;//‘Ì
	CCollider mColSphereBody;//‘Ì
	CCollider mColSphereHead;//“ª
	CCollider mColSphereSword;//Œ•
	CInput mInput;
};
#endif