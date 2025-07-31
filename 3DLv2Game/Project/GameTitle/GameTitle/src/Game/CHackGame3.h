#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>
#include "CMryotaisu.h"

class CFont;

class CHackGame3 : public CTask
{
public:
	CHackGame3();
	~CHackGame3();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool IsClear() const;

private:
	CImage* mpBackground;
	CMryotaisu* mpTaisu;
	bool mIsOpened;

	bool mIsClear;
};