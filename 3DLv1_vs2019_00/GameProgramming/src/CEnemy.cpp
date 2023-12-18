#include "CEnemy.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider1(this,&mMatrix,CVector(0.0f,5.0f,0.0f),0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{
	mpModel = model;//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;//‰ñ“]‚ÌÝ’è
	mScale = scale;//Šgk‚ÌÝ’è
}

void CEnemy::Update()
{
	CTransform::Update();
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}

void CEnemy::Collision(CCollider* m, CCollider* o) {
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//Õ“Ë‚µ‚Ä‚¢‚é‚Æ–³Œø
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//’²®’r
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//Õ“ËŽs“àˆê‚Ü‚Å–ß‚·
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CEnemy::Collision()
{
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
}