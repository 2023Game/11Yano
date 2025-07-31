#pragma once
#include "CUIBase.h"
#include "CImage.h"

class CGameUI :public CUIBase
{
public:
	CGameUI();
	~CGameUI();
	void Update();
	void Render();
	void UpdateAlert();
private:
	CImage* mpAlert;
	CImage* mpBlack;

	CImage* mpInter;
	CImage* mpUI1;
	CImage* mpUI2;

	float mAlphaTimer;
};