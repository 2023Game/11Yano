#include "CPlayer.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,0.1f)//�ړ����x

CPlayer::CPlayer(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//�s��̍X�V
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
	CTransform::Update();//�ϊ��s��̍X�V
}