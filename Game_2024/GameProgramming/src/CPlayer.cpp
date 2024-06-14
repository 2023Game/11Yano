#include "CPlayer.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//��]���x
#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,speed)//�ړ����x
#define VELOCITY2 CVector(speed2,0.0f,0.0f)
#define GLAVITY CVector(0.0f,-9.8f,0.0f)
#define MOS_POS_X 400 //�}�E�X���W��X�␳
#define MOS_POS_Y 300 //�}�E�X���W��Y�␳

CPlayer::CPlayer() 
	 :mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.65f)
{
	spInstance = this;
}

CPlayer::CPlayer(const CVector& pos, const CVector& rot
	, const CVector& scale)
{
	CTransform::Update(pos, rot, scale);//�s��̍X�V
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
	CTransform::Update();//�ϊ��s��̍X�V

	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
	mPosition = mPosition + GLAVITY;
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust)) {
				//�ʒu�̍X�V
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		break;
	}
}

void CPlayer::Collision()
{
	//�R���C�_�D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

CPlayer* CPlayer::spInstance = nullptr;

CPlayer* CPlayer::Instance()
{
	return spInstance;
}