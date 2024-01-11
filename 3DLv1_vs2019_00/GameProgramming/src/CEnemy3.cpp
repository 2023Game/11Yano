#include "CEnemy3.h"
#include "CEffect.h"
#include "CCollisionManager.h"

#define OBJ "res\\f16.obj" //モデルのファイル
#define MTL "res\\f16.mtl" //モデルのマテリアルファイル

CModel CEnemy3::sModel;

CEnemy3::CEnemy3()
	:CCharacter3(1)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
{
	//モデルがないとき読み込む
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &sModel;
}

CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3()
{
	//位置、回転、拡縮の設定
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	CTransform::Update();//行列の更新
}

void CEnemy3::Update()
{

}

void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突していると無効
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//調整池
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//衝突市内一まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}