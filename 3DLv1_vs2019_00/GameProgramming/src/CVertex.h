#pragma once
#ifndef CVERTEX_H
#define CVERTEX_H
#include "CVector.h"

class CVertex {
public:
	CVector mPosition;//位置
	CVector mNormal;//法線
	CVector mTextureCoords;//テクスチャマッピング
	float mBoneWeight[4];//スキンウェイト
	float mBoneIndex[4];//スキンインデックス

	CVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

#endif