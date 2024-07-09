#pragma once
#ifndef CANGLE_H
#define CANGLE_H
#include "CCharacter3.h"
#include "CInput.h"
#include "CCollider.h"
#include "CPlayer.h"

class CAngle :public CCharacter3 {
public:
	static CAngle* Instance();
	CAngle();
	CAngle(const CVector& pos, const CVector& rot
		, const CVector& scale);
	void Update();
	void Collision();
	void Collision(CCollider* m, CCollider* o);
private:
	CPlayer mPlayer;
	static CAngle* spInstance;
	CCollider mCollider;
	CInput mInput;
};
#endif