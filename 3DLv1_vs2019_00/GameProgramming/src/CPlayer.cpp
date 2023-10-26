#include "CPlayer.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度

CPlayer::CPlayer(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//行列の更新
}

void CPlayer::Update()
{
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
	CTransform::Update();//変換行列の更新
}