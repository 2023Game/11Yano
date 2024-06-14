#pragma once
#ifndef CANGLE_H
#define CANGLE_H
#include "CCharacter3.h"
#include "CCollider.h"

class CAngle : public CCharacter3
{
public:
	CAngle(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:

};

#endif