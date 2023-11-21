#pragma once
#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include "CCharacter3.h"

class CCollisionManager;

class CCollider :public CTransform, public CTask {
	friend CCollisionManager;
public:
	static bool Collision(CCollider* m, CCollider* o);//衝突判定
	~CCollider();
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	CCharacter3* Parent();//親ポインタの取得
	void Render();
protected:
	CCharacter3* mpParent;//親
	CMatrix* mpMatrix;//親行列
	float mRadius;//半径
};

#endif