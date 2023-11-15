#include "CEnemy.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
{
	mpModel = model;//���f���̐ݒ�
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
}

void CEnemy::Update()
{
	CTransform::Update();
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}
