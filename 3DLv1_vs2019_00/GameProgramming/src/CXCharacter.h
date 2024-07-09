#pragma once
#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"

class CXCharacter {
public:
	void Init(CModelX* model);//初期化処理
	void ChangeAnimation(int index, bool loop, float framesize);//アニメーションの変更
	void Update(CMatrix& m);//更新処理
	void Render();//描画処理
	//アニメーションの再生終了判定
	//true:終了　false:再生中
	bool IsAnimationFinished();
	int AnimationIndex();//アニメーション番号の取得
protected:
	CModelX* mpModel;//モデルデータ
	int mAnimationIndex;//アニメーション番号
	bool mAnimationLoopFlg;//true:アニメーションを繰り返す
	float mAnimationFrame;//アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
};
#endif