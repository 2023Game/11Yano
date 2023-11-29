#pragma once
#ifndef CEFFECT_H
#define CEFFECT_H
#include "CBillBoard.h"

class CEffect :public CBillBoard {
public:
	//�s���B�񐔁B�t���[�����̓f�t�H���g�����ŌĂяo��
	CEffect(const CVector& pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
	void Update();
	void Render();
private:
	int mRows;//�s��
	int mCols;//��
	int mFps;//1�R�}�̃t���[����
	int mFrame;//�t���[���J�E���^
	static CMaterial sMaterial;
};

#endif