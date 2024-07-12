#pragma once
#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CInput.h"
#include "CCollider.h"

class CXPlayer :public CXCharacter {
public:
	void Init(CModelX* model);
	CXPlayer();
	void Update();
private:
	CCollider mColSphereBody;//‘Ì
	CCollider mColSphereHead;//“ª
	CCollider mColSphereSword;//Œ•
	CInput mInput;
};
#endif