#pragma once
#ifndef CENEMY3_H
#define CENEMY3_H
#include "CCharacter3.h"
#include "CCollider.h"

class CEnemy3 :public CCharacter3 {
public:
	CEnemy3();
	//CEnemy3(�ʒu�A��]�A�g�k)
	CEnemy3(const CVector& position, const CVector& rotation,
		const CVector& scale);
	void Update();
	//Collision(�R���C�_�P�C�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CVector mPoint;
	int mHp;
	static CModel sModel;
	CCollider mCollider;
};
#endif