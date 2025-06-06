#pragma once
#include "CFont.h"
/*
* CUi
* ユーザーインタフェースクラス
*/
class CUi
{
public:
	void PosY(float f);//高度の設定
	void RotX(float f);//ピッチの設定
	void RotY(float f);
	//ゲームクリア表示
	void Clear();
	//ゲームオーバー表示
	void Over();
	//スタート表示
	void Start();
	//Enemy(敵の数)
	void Enemy(int enemy);
	CUi();
	void Hp(int hp);
	//Time(時間)
	void Time(int time);
	void Render();
private:
	float mPosY;//高度ｙ座標
	float mRotX;//ピッチＸ回転地
	float mRotY;
	int mEnemy;	//敵の数
	int mHp;
	int mTime;	//経過時間
	CFont mFont;
};
