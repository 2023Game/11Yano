#include "CPlayer.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CApplication.h"
#define VELOCITY CVector(speed,0.0f,0.0f)//�ړ����x
#define VELOCITY2 CVector(0.0f,0.0f,speed2)
#define GLAVITY CVector(0.0f,-0.1f,0.0f)
#define ROTATION CVector(0.0f,0.0f,roll)//��]���x
#define ROTATION_XV CVector(roll2,0.0f,0.0f)//��]���x
//#define ROTATION_YV CVector(0.0f,roll,0.0f)//��]���x


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
	
	if (mInput.Key('W'))
	{
		speed -= 0.001f;
		roll += 0.05f;
		mRotation = mRotation + ROTATION;
		mPosition = mPosition + VELOCITY;
	}
	else if (!mInput.Key('W') && !mInput.Key('S') && speed < 0 )
	{
		speed += 0.001f;
		roll -= 0.05f;
		mRotation = mRotation + ROTATION;
		mPosition = mPosition + VELOCITY;
	}
	if (mInput.Key('S'))
	{
		speed += 0.001f;
		roll -= 0.05f;
		mRotation = mRotation + ROTATION;
		mPosition = mPosition + VELOCITY;
	}
	else if (!mInput.Key('S') && !mInput.Key('W') && speed > 0)
	{
		speed -= 0.001f;
		roll += 0.05f;
		mRotation = mRotation + ROTATION;
		mPosition = mPosition + VELOCITY;
	}
	if (mInput.Key('A'))
	{
		speed2 += 0.001f;
		roll2 += 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY2;
	}
	else if (!mInput.Key('A') && !mInput.Key('D') && speed2 > 0)
	{
		speed2 -= 0.001f;
		roll2 -= 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY2;
	}
	if (mInput.Key('D'))
	{
		speed2 -= 0.001f;
		roll2 -= 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY2;
	}
	else if (!mInput.Key('D') && !mInput.Key('A') && speed2 < 0)
	{
		speed2 += 0.001f;
		roll2 += 0.05f;
		mRotation = mRotation + ROTATION_XV;
		mPosition = mPosition + VELOCITY2;
	}
	CTransform::Update();//�ϊ��s��̍X�V

	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->PosX(mPosition.X());
	CApplication::Ui()->PosZ(mPosition.Z());
	CApplication::Ui()->RotY(mRotation.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotZ(mRotation.Z());
	if (Ground == false)
	{
		mPosition = mPosition + GLAVITY;
	}
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
				Ground = true;
			}
			else {
				Ground = false;
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