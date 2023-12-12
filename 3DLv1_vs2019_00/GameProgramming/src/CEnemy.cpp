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

void CEnemy::Collision(CCollider* m, CCollider* o) {
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
