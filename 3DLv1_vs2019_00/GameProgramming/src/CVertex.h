#pragma once
#ifndef CVERTEX_H
#define CVERTEX_H
#include "CVector.h"

class CVertex {
public:
	CVector mPosition;//�ʒu
	CVector mNormal;//�@��
	CVector mTextureCoords;//�e�N�X�`���}�b�s���O
	float mBoneWeight[4];//�X�L���E�F�C�g
	float mBoneIndex[4];//�X�L���C���f�b�N�X

	CVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

#endif