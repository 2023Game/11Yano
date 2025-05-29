#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

class CFont;

class CHackGame : public CTask
{
public:
	void Start();
	CHackGame();
	~CHackGame();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool IsClear() const;
	
private:
	CImage* mpBackground;
	bool mIsOpened;
	

	CFont* mpLogoFont;	// ロゴのフォント
	CText* mpTypeLogo;	// タイピングロゴ
	char mText; // タイピングゲームのテキスト

	int mInputNum;

	bool mIsClear;
	CImage* mpPlayer;//後で消す
};