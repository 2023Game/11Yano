#pragma once
#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"

class CColliderLine :public CCollider {
public:
	void ChangePriority();//�D��x�̕ύX
	CColliderLine(){}
	//�R���X�g���N�^�i�����R���C�_�j
	CColliderLine(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//Set�i�e�A�e�s��A���_1�A���_2�j
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	void Render();
};

#endif