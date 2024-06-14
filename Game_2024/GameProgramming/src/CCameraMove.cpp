#include "CCameraMove.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CCameraMove::CCameraMove(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, -5.0f), 0.3f)
{
	mpModel = model;//���f���̐ݒ�
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
}

void CCameraMove::Update()
{
	CTransform::Update();
	mPosition = mPlayer.Position();
}

void CCameraMove::Collision(CCollider* m, CCollider* o)
{
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust)) {
				//�ʒu�̍X�V
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		break;
	}
}
