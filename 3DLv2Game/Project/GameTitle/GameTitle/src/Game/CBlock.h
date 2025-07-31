#pragma once
#include "CCharaBase.h"
#include "CImage.h"
#include "CColliderTriangle2D.h"

class CBlock : public CCharaBase
{
public:
	CBlock(float x, float y);
	void Update() {}
	void Render();
private:
	CImage* mpImage;
	CColliderTriangle2D* mpCollider;
	CColliderTriangle2D* mpCollider2;
};