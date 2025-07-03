#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

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
	bool mIsOpened;

	bool mIsClear;
};