#include "CEnemy.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
{
	mpModel = model;//ƒ‚ƒfƒ‹‚Ìİ’è
	mPosition = position;//ˆÊ’u‚Ìİ’è
	mRotation = rotation;//‰ñ“]‚Ìİ’è
	mScale = scale;//Šgk‚Ìİ’è
}

void CEnemy::Update()
{
	CTransform::Update();
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}
