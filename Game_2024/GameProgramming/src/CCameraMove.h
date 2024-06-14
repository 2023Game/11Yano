#pragma once
#ifndef CCAMERAMOVE_H
#define CCAMERAMOVE_H
#include "CCharacter3.h"
#include "CCollider.h"
#include "CPlayer.h"

class CCameraMove : public CCharacter3
{
public:
	void Collision();
	void Collision(CCollider* m, CCollider* o);
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CCameraMove(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:
	CPlayer mPlayer;
	CCollider mCollider;
};

#endif
