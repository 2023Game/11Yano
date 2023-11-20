#pragma once
#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter3.h"
#include "CCollider.h"

class CEnemy : public CCharacter3
{
public:
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};

#endif