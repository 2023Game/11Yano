#pragma once
#include "CImage.h"
#include "CInput.h"

class CPlayer2D : public CImage
{
public:
	CPlayer2D(float x, float y, float w, float h, CTexture* pt);
	void Update();
private:
	CInput mInput;
};