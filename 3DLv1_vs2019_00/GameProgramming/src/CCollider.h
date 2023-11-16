#pragma once
#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include "CCharacter3.h"

class CCollider :public CTransform {
public:
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	CCharacter3* Parent();//�e�|�C���^�̎擾
	void Render();
protected:
	CCharacter3* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a
};

#endif