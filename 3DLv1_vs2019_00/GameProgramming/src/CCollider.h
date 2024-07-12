#pragma once
#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include "CCharacter3.h"
#include "CMatrix.h"

class CCollisionManager;

class CCollider :public CTransform, public CTask {
	friend CCollisionManager;
public:
	void Matrix(CMatrix* m);
	void ChangePriority();//�D��x�̕ύX
	void ChangePriority(int priority);
	static bool CollisionTriangleSphere(CCollider* triangle, CCollider* sphere, CVector* adjust);
	//CollisionTriangleLine(�O�p�R���C�_�A�����R���C�_�A�����l)
	//�����r�F�Փ˂��Ȃ��ʒu�܂Ŗ߂��n
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//�R���C�_�^�C�v
	enum class EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE,//�����R���C�_
	};
	CCollider();
	static bool Collision(CCollider* m, CCollider* o);//�Փ˔���
	~CCollider();
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	CCharacter3* Parent();//�e�|�C���^�̎擾
	void Render();
	EType Type();
protected:
	EType mType;//�R���C�_�^�C�v
	CVector mV[3];//���_
	CCharacter3* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a
};

#endif