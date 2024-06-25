#include "CPlayer.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"
#define VELOCITY CVector(speed,0.0f,0.0f)//移動速度
#define VELOCITY2 CVector(0.0f,0.0f,speed2)
#define GLAVITY CVector(0.0f,-0.1f,0.0f)
#define ROTATION_XV CVector(roll,0.0f,0.0f)//回転速度
#define ROTATION_YV CVector(0.0f,0.0f,roll2)//回転速度


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
	if (mInput.Key('W'))
	{
		speed -= 0.001f;
		roll += 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY;
	}
	else if (!mInput.Key('W') && !mInput.Key('S') && speed < 0 )
	{
		speed += 0.001f;
		roll -= 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY;
	}
	if (mInput.Key('S'))
	{
		speed += 0.001f;
		roll -= 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY;
	}
	else if (!mInput.Key('S') && !mInput.Key('W') && speed > 0)
	{
		speed -= 0.001f;
		roll += 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY;
	}
	if (mInput.Key('A'))
	{
		speed2 += 0.001f;
		roll2 -= 0.05f;
		mRotation = mRotation + ROTATION_YV;
		mPosition = mPosition + VELOCITY2;
	}
	else if (!mInput.Key('A') && !mInput.Key('D') && speed2 > 0)
	{
		speed2 -= 0.001f;
		roll2 += 0.05f;
		mRotation = mRotation + ROTATION_YV;
		mPosition = mPosition + VELOCITY2;
	}
	if (mInput.Key('D'))
	{
		speed2 -= 0.001f;
		roll2 += 0.05f;
		mRotation = mRotation + ROTATION_YV;
		mPosition = mPosition + VELOCITY2;
	}
	else if (!mInput.Key('D') && !mInput.Key('A') && speed2 < 0)
	{
		speed2 += 0.001f;
		roll2 -= 0.05f;
		mRotation = mRotation + ROTATION_YV;
		mPosition = mPosition + VELOCITY2;
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