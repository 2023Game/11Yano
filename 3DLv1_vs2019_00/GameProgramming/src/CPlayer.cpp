#include "CPlayer.h"
#include "CTaskManager.h"
#include "CApplication.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//��]���x
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,0.1f)//�ړ����x

CPlayer::CPlayer() 
	:mLine(this, &mMatrix,CVector(0.0f,0.0f,-14.0f),CVector(0.0f,0.0f,17.0f))
	, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
	, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
{

}

CPlayer::CPlayer(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//�s��̍X�V
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
	CTransform::Update();//�ϊ��s��̍X�V
}