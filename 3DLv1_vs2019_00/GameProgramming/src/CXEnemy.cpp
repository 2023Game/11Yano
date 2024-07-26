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
    //合成行列の設定
    mColSphereBody.Matrix(&mpCombinedMatrix[1]);
    mColSphereHead.Matrix(&mpCombinedMatrix[1]);
    mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ESPHERE) {
			if (m->Tag() == CCollider::ETag::EBODY && o->Tag() == CCollider::ETag::ESWORD) {
				//プレイヤーとの衝突判定
				if (CCollider::Collision(o, m)) {
					ChangeAnimation(11, false, 30);	
				}
			}
		}
		break;
	}
}