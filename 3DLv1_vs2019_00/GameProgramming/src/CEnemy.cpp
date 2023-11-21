#include "CEnemy.h"
#include "CCollisionManager.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider1(this,&mMatrix,CVector(0.0f,5.0f,0.0f),0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
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

void CEnemy::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		mEnabled = false;
	}
}
