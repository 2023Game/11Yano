#pragma once
#ifndef CENEMY3_H
#define CENEMY3_H
#include "CCharacter3.h"
#include "CCollider.h"

class CEnemy3 :public CCharacter3 {
public:
	CEnemy3();
	//CEnemy3(位置、回転、拡縮)
	CEnemy3(const CVector& position, const CVector& rotation,
		const CVector& scale);
	void Update();
	//Collision(コライダ１，コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CVector mPoint;
	int mHp;
	static CModel sModel;
	CCollider mCollider;
};
#endif