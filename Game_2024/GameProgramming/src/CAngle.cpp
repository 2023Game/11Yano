#include "CAngle.h"
#include "CCollisionManager.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//��]���x
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x

CAngle::CAngle(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.2f)
{
	mpModel = model;//���f���̐ݒ�
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
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
			//�Փ˂��Ă���Ɩ���
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//�����r
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փˎs����܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}
}