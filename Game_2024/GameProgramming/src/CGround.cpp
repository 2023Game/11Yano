#include "CGround.h"
#include "CCollisionManager.h"
#define VELOCITY CVector(0.1f,0.0f,0.0f)

CGround::CGround(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
{
	mpModel = model;//ƒ‚ƒfƒ‹‚Ìİ’è
	mPosition = position;//ˆÊ’u‚Ìİ’è
	mRotation = rotation;//‰ñ“]‚Ìİ’è
	mScale = scale;//Šgk‚Ìİ’è
}

void CGround::Update()
{
	CTransform::Update();
	mPosition = mPosition + VELOCITY;
}
