#include "CXEnemy.h"

CXEnemy::CXEnemy()
    :mColSphereBody(this, nullptr, CVector(0.5f,-1.0f,0.0f), 1.0f, CCollider::ETag::EBODY)
    , mColSphereHead(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.5f)
    , mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f, CCollider::ETag::ESWORD)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f, CCollider::ETag::ESWORD)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f, CCollider::ETag::ESWORD)
{

}

void CXEnemy::Init(CModelX* model) {
    CXCharacter::Init(model);
    //�����s��̐ݒ�
    mColSphereBody.Matrix(&mpCombinedMatrix[1]);
    mColSphereHead.Matrix(&mpCombinedMatrix[1]);
    mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ESPHERE) {
			if (m->Tag() == CCollider::ETag::EBODY && o->Tag() == CCollider::ETag::ESWORD) {
				//�v���C���[�Ƃ̏Փ˔���
				if (CCollider::Collision(o, m)) {
					ChangeAnimation(11, false, 30);	
				}
			}
		}
		break;
	}
}