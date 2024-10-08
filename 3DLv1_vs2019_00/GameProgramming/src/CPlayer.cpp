#include "CPlayer.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度

CPlayer::CPlayer() 
	//:mLine(this, &mMatrix,CVector(0.0f,0.0f,-14.0f),CVector(0.0f,0.0f,17.0f))
	//, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
	//, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
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
	if (mInput.Key('S'))
	{
		mRotation = mRotation - ROTATION_XV;
	}
	if (mInput.Key('W'))
	{
		mRotation = mRotation + ROTATION_XV;
	}
	if (mInput.Key('D'))
	{
		mRotation = mRotation - ROTATION_YV;
	}
	if (mInput.Key('A'))
	{
		mRotation = mRotation + ROTATION_YV;
	}
	if (mInput.Key(VK_UP))
	{
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (mInput.Key(VK_SPACE))
	{
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
	}
	CTransform::Update();//変換行列の更新

	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ELINE:
		if (o->Type() == CCollider::EType::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
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
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
}

CPlayer* CPlayer::spInstance = nullptr;

CPlayer* CPlayer::Instance()
{
	return spInstance;
}