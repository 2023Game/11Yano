#pragma once
#include "CTask.h"
#include "CImage.h"
#include "CPlayer2D.h"
#include "CEnemy2D.h"
#include <vector>
#include <string>
#include "CSound.h"

class CFont;

class CHackGame2 : public CTask
{
public:
	CHackGame2();
	~CHackGame2();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool IsClear() const;
private:
	CImage* mpBackground;
	bool mIsOpened;

	CPlayer2D* mpPlayer;
	CEnemy2D* mpEnemy;
	CEnemy2D* mpEnemy2;
	CEnemy2D* mpEnemy3;

	CFont* mpFont;	// フォント
	CText* mpLogos;	// テキスト

	CSound* mpSE;

	int mInputNum;

	bool mIsClear;
};