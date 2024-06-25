#include "CAngle.h"
#include "CCollisionManager.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//‰ñ“]‘¬“x
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//‰ñ“]‘¬“x

CAngle::CAngle(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.2f)
{
	mpModel = model;//ƒ‚ƒfƒ‹‚Ìİ’è
	mPosition = position;//ˆÊ’u‚Ìİ’è
	mRotation = rotation;//‰ñ“]‚Ìİ’è
	mScale = scale;//Šgk‚Ìİ’è
}

void CAngle::Update()
{
	
	CTransform::Update();
	//mPosition = mPlayer.Position();
}

void CAngle::Collision(CCollider* m, CCollider* o) {
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			//Õ“Ë‚µ‚Ä‚¢‚é‚Æ–³Œø
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//’²®’r
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//Õ“Ës“àˆê‚Ü‚Å–ß‚·
			mPosition = mPosition + adjust;
		}
		break;
	}
}