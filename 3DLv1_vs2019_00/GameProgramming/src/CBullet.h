#pragma once
#ifndef CBULLET_H
#define CBULLET_H
#include "CCharacter3.h"
#include "CTriangle.h"
#include "CCollider.h"

class CBullet : public CCharacter3
{
public:
	CBullet();
	void Set(float w, float d);
	void Update();
	void Render();
private:
	CCollider mCollider;
	int mLife;
	CTriangle mT;
};

#endif