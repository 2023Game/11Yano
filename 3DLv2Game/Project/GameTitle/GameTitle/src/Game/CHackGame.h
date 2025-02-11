#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

class CFont;

class CHackGame : public CTask
{
public:
	CHackGame();
	~CHackGame();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool mIsClear;
private:
	CImage* mpBackground;
	bool mIsOpened;
	

	CFont* mpLogoFont;	// ���S�̃t�H���g
	CText* mpTypeLogo;	// �^�C�s���O���S

	int mInputNum;
};