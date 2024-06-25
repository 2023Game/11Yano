#include "CGround.h"
#include "CCollisionManager.h"
#define VELOCITY CVector(0.1f,0.0f,0.0f)

CGround::CGround(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
{
	mpModel = model;//���f���̐ݒ�
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
}

void CGround::Update()
{
	CTransform::Update();
	mPosition = mPosition + VELOCITY;
}
