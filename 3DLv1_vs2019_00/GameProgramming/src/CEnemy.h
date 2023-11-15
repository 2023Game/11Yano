#pragma once
#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter3.h"

class CEnemy : public CCharacter3
{
public:
	//CEnemy(モデル、位置、回転、拡縮)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
};

#endif