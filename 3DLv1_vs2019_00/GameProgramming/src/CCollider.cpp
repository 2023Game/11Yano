#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) {
	mpParent = parent;//�e�ݒ�
	mpMatrix = matrix;//�e�s��ݒ�
	mPosition = position;//�ʒu
	mRadius = radius;//���a�ݒ�
	CCollisionManager::Instance()->Add(this);
}

CCharacter3* CCollider::Parent() {
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	CVector pos = mPosition * *mpMatrix;//�R���C�_�̒��S���W�v�Z
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());//���S���W�ֈړ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };//DIFFUSE�ԐF�ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glutWireSphere(mRadius, 16, 16);//���`��
	glPopMatrix();
}

CCollider::~CCollider() {
	CCollisionManager::Instance()->Remove(this);
}