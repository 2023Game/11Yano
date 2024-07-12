#include "CXEnemy.h"

CXEnemy::CXEnemy()
    :mColSphereBody(this, nullptr, CVector(), 0.5f, CCollider::ETag::EBODY)
    , mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
    , mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f, CCollider::ETag::ESWORD)
{

}

void CXEnemy::Init(CModelX* model) {
    CXCharacter::Init(model);
    //�����s��̐ݒ�
    mColSphereBody.Matrix(&mpCombinedMatrix[8]);
    mColSphereHead.Matrix(&mpCombinedMatrix[11]);
    mColSphereSword.Matrix(&mpCombinedMatrix[21]);
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