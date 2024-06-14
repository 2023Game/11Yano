#include "CPlayer.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,speed)//移動速度
#define VELOCITY2 CVector(speed2,0.0f,0.0f)
#define GLAVITY CVector(0.0f,-9.8f,0.0f)
#define MOS_POS_X 400 //マウス座標のX補正
#define MOS_POS_Y 300 //マウス座標のY補正

CPlayer::CPlayer() 
	 :mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.65f)
{
	spInstance = this;
}

CPlayer::CPlayer(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//行列の更新
}

void CPlayer::Update()
{
	if (mInput.Key(VK_DOWN))
	{
		mRotation = mRotation - ROTATION_XV;
	}
	if (mInput.Key(VK_UP))
	{
		mRotation = mRotation + ROTATION_XV;
	}
	if (mInput.Key(VK_RIGHT))
	{
		mRotation = mRotation - ROTATION_YV;
	}
	if (mInput.Key(VK_LEFT))
	{
		mRotation = mRotation + ROTATION_YV;
	}
	if (mInput.Key('W'))
	{
		speed += 0.001f;
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	else if (!mInput.Key('W') && speed > 0)
	{
		speed -= 0.001f;
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (mInput.Key('S'))
	{
		speed -= 0.001f;
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	else if (!mInput.Key('S') && speed < 0)
	{
		speed += 0.001f;
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (mInput.Key('A'))
	{
		speed2 += 0.001f;
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	else if (!mInput.Key('A') && speed2 > 0)
	{
		speed2 -= 0.001f;
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	if (mInput.Key('D'))
	{
		speed2 -= 0.001f;
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	else if (!mInput.Key('D') && speed2 < 0)
	{
		speed2 += 0.001f;
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	CTransform::Update();//変換行列の更新

	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
	mPosition = mPosition + GLAVITY;
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
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

void CPlayer::Collision()
{
	//コライダ優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

CPlayer* CPlayer::spInstance = nullptr;

CPlayer* CPlayer::Instance()
{
	return spInstance;
}