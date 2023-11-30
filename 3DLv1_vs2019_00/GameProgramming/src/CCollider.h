#pragma once
#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include "CCharacter3.h"

class CCollisionManager;

class CCollider :public CTransform, public CTask {
	friend CCollisionManager;
public:
	//�R���C�_�^�C�v
	enum class EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
	};
	CCollider();
	static bool Collision(CCollider* m, CCollider* o);//�Փ˔���
	~CCollider();
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	CCharacter3* Parent();//�e�|�C���^�̎擾
	void Render();
protected:
	EType mType;//�R���C�_�^�C�v
	CVector mV[3];//���_
	CCharacter3* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a
};

#endif