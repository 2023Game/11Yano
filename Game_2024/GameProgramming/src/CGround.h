#pragma once
#ifndef CGROUND_H
#define CGROUND_H
#include "CCharacter3.h"
#include "CColliderTriangle.h"

class CGround : public CCharacter3
{
public:
	CGround(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:
	CColliderTriangle mCollider;
};

#endif