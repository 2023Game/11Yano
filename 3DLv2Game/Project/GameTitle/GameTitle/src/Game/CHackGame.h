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
	static CHackGame* Instance();
	CHackGame();
	~CHackGame();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool IsClear() const;
	
private:
	static CHackGame* spInstance;
	std::string mCurrentWord;
	std::vector<std::string> mWordList = {
		"HACK", "CODE", "INPUT", "DEBUG", "LOGIC", "BREAK", "ARRAY", "LOOP"
	};
	CImage* mpBackground;
	bool mIsOpened;
	
	CSound* mpSE;

	CFont* mpLogoFont;	// ロゴのフォント
	CFont* mpLogoFontBg;	// ロゴのフォント
	CText* mpTypeLogo;	// タイピングロゴ
	CText* mpTypedLogo; // タイプ済みのロゴ
	char mText; // タイピングゲームのテキスト

	int mInputNum;

	bool mIsClear;
};