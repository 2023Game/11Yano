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
	CColliderCapsule mColBody;//��
	CCollider mColSphereBody;//��
	CCollider mColSphereHead;//��
	CCollider mColSphereSword0;//��
	CCollider mColSphereSword1;//��
	CCollider mColSphereSword2;//��
};
#endif