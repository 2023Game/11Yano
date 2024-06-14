#pragma once
#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"

class CColliderTriangle :public CCollider {
public:
	void ChangePriority();//�D��x�̕ύX
	CColliderTriangle(){}
	//�R���X�g���N�^�i�O�p�R���C�_�j
	CColliderTriangle(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//�O�p�R���C�_�̐ݒ�
	void Set(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	void Render();
};

#endif