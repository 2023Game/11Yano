#pragma once
#include "CCharaBase.h"
#include "CImage.h"

class CBlock : public CCharaBase
{
public:
	CBlock(float x, float y);
	void Update() {}
private:
	CImage* mpImage;
};