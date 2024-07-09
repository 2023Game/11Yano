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
	CTransform::Update(pos, rot, scale);//行列の更新
}

void CAngle::Update()
{
	
	CTransform::Update();//変換行列の更新
}

void CAngle::Collision(CCollider* m, CCollider* o) {
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

void CAngle::Collision()
{
	//コライダ優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

CAngle* CAngle::spInstance = nullptr;

CAngle* CAngle::Instance()
{
	return spInstance;
}