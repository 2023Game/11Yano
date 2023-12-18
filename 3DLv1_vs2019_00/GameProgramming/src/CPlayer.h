#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"

class CPlayer : public CCharacter3
{
public:
	void Collision();
	void Collision(CCollider* m, CCollider* o);//è’ìÀèàóù
	CPlayer();
	CPlayer(const CVector& pos, const CVector& rot
		, const CVector& scale);
	void Update();
private:
	CColliderLine mLine;
	CColliderLine mLine2;
	CColliderLine mLine3;
	CInput mInput;
};

#endif