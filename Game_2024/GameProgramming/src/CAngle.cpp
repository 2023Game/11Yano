#include "CAngle.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CAngle::CAngle(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
{
	mpModel = model;//���f���̐ݒ�
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
}

void CAngle::Update()
{
	CTransform::Update();
	//mPosition = mPosition + VELOCITY * mMatrixRotate;
}