#pragma once
#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CCharacter3.h"

class CBillBoard :public CCharacter3 {
public:
	CBillBoard(CVector pos, float w, float h, int priority);
	CBillBoard();
	CBillBoard(CVector pos, float w, float h);
	void Set(CVector pos, float w, float h);//位置と大きさ
	void Update();
	void Render();
	void Render(CMaterial* mpMaterial);
protected:
	CTriangle mT[2];
	CMaterial mMaterial;
};

#endif