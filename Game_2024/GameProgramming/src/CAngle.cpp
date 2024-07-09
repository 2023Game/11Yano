#include "CAngle.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"

CAngle::CAngle()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 5.0f), 0.2f)
{
	spInstance = this;
}

CAngle::CAngle(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//�s��̍X�V
}

void CAngle::Update()
{
	
	CTransform::Update();//�ϊ��s��̍X�V
}

void CAngle::Collision(CCollider* m, CCollider* o) {
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

void CAngle::Collision()
{
	//�R���C�_�D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

CAngle* CAngle::spInstance = nullptr;

CAngle* CAngle::Instance()
{
	return spInstance;
}