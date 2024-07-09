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
	void PosX(float f);//ピッチの設定
	void PosZ(float f);
	void RotY(float f);//高度の設定
	void RotX(float f);//ピッチの設定
	void RotZ(float f);
	//ゲームクリア表示
	void Clear();
	//ゲームオーバー表示
	void Over();
	//スタート表示
	void Start();
	CUi();
	//Time(時間)
	void Time(int time);
	void Render();
private:
	float mPosY;//高度ｙ座標
	float mPosX;
	float mPosZ;
	float mRotY;//高度ｙ座標
	float mRotX;
	float mRotZ;
	int mTime;	//経過時間
	CFont mFont;
};
