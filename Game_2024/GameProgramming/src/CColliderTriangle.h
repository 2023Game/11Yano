#pragma once
#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"

class CColliderTriangle :public CCollider {
public:
	void ChangePriority();//優先度の変更
	CColliderTriangle(){}
	//コンストラクタ（三角コライダ）
	CColliderTriangle(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//三角コライダの設定
	void Set(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	void Render();
};

#endif