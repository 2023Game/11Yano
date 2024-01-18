#include "CEnemy3.h"
#include "CEffect.h"
#include "CPlayer.h"
#include "CCollisionManager.h"

#define OBJ "res\\f16.obj" //モデルのファイル
#define MTL "res\\f16.mtl" //モデルのマテリアルファイル
#define HP 3 //耐久値
#define VELOCITY 0.11f //速度

CModel CEnemy3::sModel;

CEnemy3::CEnemy3()
	:CCharacter3(1)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
	,mHp(HP)
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
	//目標地点の設定
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

void CEnemy3::Update()
{
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - mPosition;
		//左ベクトルとの内積を求める
		float dx = vp.Dot(mMatrixRotate.VectorX());
		//上ベクトルとの内積を求める
		float dy = vp.Dot(mMatrixRotate.VectorY());
		float dz = vp.Dot(mMatrixRotate.VectorZ());
		//X軸のずれが2.0以下
		if (-2.0f < dx && dx < 2.0f)
		{
			if (-2.0f < dy && dy < 2.0f)
			{
				if (0 < dz && dz <= 30.0f)
				{
					//弾を発射
					CBullet* bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->Position(
						CVector(0.0f, 0.0f, 10.0f) * mMatrix);
					bullet->Rotation(mRotation);
					bullet->Update();
				}
			}
		}
	}

	//HPが０いかの時撃破
	if (mHp <= 0)
	{
		mHp--;
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//下降させる
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}

	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;

	//左ベクトルとの内積
	float dx = vp.Dot(mMatrixRotate.VectorX());
	//上ベクトルとの内積
	float dy = vp.Dot(mMatrixRotate.VectorY());
	const float margin = 0.1f;
	//左右方向へ回転
	if (dx > margin)
	{
		//左へ回転
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);
	}
	else if (dx < -margin)
	{
		//右へ回転
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);
	}
	//上下方向へ回転
	if (dy > margin)
	{
		//上へ回転
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);
	}
	else if (dy < -margin)
	{
		//下へ回転
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
	}

	//期待前方へ移動する
	mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
	CTransform::Update();

	//役秒ごとに目標地点を更新
	int r = rand() % 180;//rand()は整数の乱数を返す
	if (r == 0)
	{
		if (player != nullptr)
		{
			mPoint = player->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}
}

void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			mHp--;//HP減算
			//衝突していると無効
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//調整池
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//衝突市内一まで戻す
			//mPosition = mPosition + adjust;
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}