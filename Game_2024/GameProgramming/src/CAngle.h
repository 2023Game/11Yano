#ifndef CANGLE_H
#define CANGLE_H
#include "CCharacter3.h"
#include "CCollider.h"
#include "CInput.h"
#include "CPlayer.h"

class CAngle : public CCharacter3
{
public:
	CAngle(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
private:
	CCollider mCollider;
	CInput mInput;
	CPlayer mPlayer;
};

#endif