#pragma once
#ifndef CGROUND_H
#define CGROUND_H
#include "CCharacter3.h"
#include "CCollider.h"

class CGround : public CCharacter3
{
public:
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CGround(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:

};

#endif