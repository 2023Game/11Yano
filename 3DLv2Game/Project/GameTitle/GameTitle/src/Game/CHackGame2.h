#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

class CFont;

class CHackGame2 : public CTask
{
public:
	void Start();
	CHackGame2();
	~CHackGame2();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool mIsClear;
private:
	CImage* mpBackground;
	bool mIsOpened;


	CFont* mpLogoFont;	// ロゴのフォント
	CText* mpTypeLogo;	// タイピングロゴ
	char mText; // タイピングゲームのテキスト

	int mInputNum;
};