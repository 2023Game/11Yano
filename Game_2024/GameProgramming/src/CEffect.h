#pragma once
#ifndef CEFFECT_H
#define CEFFECT_H
#include "CBillBoard.h"

class CEffect :public CBillBoard {
public:
	//行数。列数。フレーム数はデフォルト引数で呼び出す
	CEffect(const CVector& pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
	void Update();
	void Render();
private:
	int mRows;//行数
	int mCols;//列数
	int mFps;//1コマのフレーム数
	int mFrame;//フレームカウンタ
	static CMaterial sMaterial;
};

#endif