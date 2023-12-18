#pragma once
#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"

class CColliderLine :public CCollider {
public:
	void ChangePriority();//優先度の変更
	CColliderLine(){}
	//コンストラクタ（線分コライダ）
	CColliderLine(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//Set（親、親行列、頂点1、頂点2）
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	void Render();
};

#endif