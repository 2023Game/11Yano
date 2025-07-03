#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>
#include "CSound.h"

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

	bool IsClear() const;
	
private:
	std::string mCurrentWord;
	std::vector<std::string> mWordList = {
		"HACK", "CODE", "INPUT", "DEBUG", "LOGIC", "VIRUS", "ARRAY", "LOOP"
	};
	CImage* mpBackground;
	bool mIsOpened;
	
	CSound* mpSE;

	CFont* mpLogoFont;	// ���S�̃t�H���g
	CFont* mpLogoFontBg;	// ���S�̃t�H���g
	CText* mpTypeLogo;	// �^�C�s���O���S
	CText* mpTypedLogo; // �^�C�v�ς݂̃��S
	char mText; // �^�C�s���O�Q�[���̃e�L�X�g

	int mInputNum;

	bool mIsClear;
};