#include "CPlayer.h"
#include "CTaskManager.h"
#include "CApplication.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度

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
}