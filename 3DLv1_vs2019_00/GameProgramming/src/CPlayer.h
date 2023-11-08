#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"

class CPlayer : public CCharacter3
{
public:
	CPlayer(){}
	CPlayer(const CVector& pos, const CVector& rot
		, const CVector& scale);
	void Update();
	CBullet bullet;
private:
	CInput mInput;
};

#endif