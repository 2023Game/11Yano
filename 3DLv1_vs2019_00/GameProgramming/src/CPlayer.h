#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter3.h"
#include "CInput.h"

class CPlayer : public CCharacter3
{
public:
	CPlayer(){}
	CPlayer(const CVector& pos, const CVector& rot
		, const CVector& scale);
	void Update();
private:
	CInput mInput;
};

#endif