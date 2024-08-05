#pragma once
#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderCapsule.h"

class CXEnemy :public CXCharacter {
public:
	void Update();
	void Collision(CCollider* m, CCollider* o);
	CXEnemy();
	void Init(CModelX* model);
private:
	CColliderCapsule mColBody;//‘Ì
	CCollider mColSphereBody;//‘Ì
	CCollider mColSphereHead;//“ª
	CCollider mColSphereSword0;//Œ•
	CCollider mColSphereSword1;//Œ•
	CCollider mColSphereSword2;//Œ•
};
#endif