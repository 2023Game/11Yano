#include "CCameraMove.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#define VELOCITY CVector(0.0f,0.0f,0.09f)

CCameraMove::CCameraMove(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, -5.0f), 0.3f)
{
	mpModel = model;//モデルの設定
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
}

void CCameraMove::Update()
{
	CTransform::Update();
	mPosition = mPlayer.Position();
}

void CCameraMove::Collision(CCollider* m, CCollider* o)
{
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleSphere(o, m, &adjust)) {
				//位置の更新
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		break;
	}
}
