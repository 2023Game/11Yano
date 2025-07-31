#include "CDebugFieldOfView.h"
#include "Primitive.h"
#include "glut.h"
#include "CInput.h"

#define SHOW_TIME 6.0f

CDebugFieldOfView::CDebugFieldOfView(CObjectBase* owner,
	float fovAngle, float fovLength, EType type)
	: CObjectBase(ETag::eDebug, ETaskPriority::eDebugFov, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mFovAngle(fovAngle)
	, mFovLength(fovLength)
	, mType(type)
	, mIsRender(false)
	, mTime(SHOW_TIME)
{
	SetShow(false);

	mpSE = CResourceManager::Get<CSound>("View");
}

CDebugFieldOfView::~CDebugFieldOfView()
{
	// �\���Ώۂ����݂���ꍇ�͎��g���폜���ꂽ���Ƃ�\���Ώۂɓ`����
	if (mpOwner != nullptr)
	{
		mpOwner->DeleteObject(this);
	}
}

void CDebugFieldOfView::SetOwner(CObjectBase* owner)
{
	mpOwner = owner;
}

void CDebugFieldOfView::Set(float angle, float length, EType type)
{
	mFovAngle = angle;
	mFovLength = length;
	mType = type;
}

void CDebugFieldOfView::Update()
{
	if (CInput::PushKey('R'))
	{
		mpSE->Play(0.3f, true);
		mIsRender = true;
	}
	if (mIsRender)
	{
		SetShow(true);
		mTime -= Times::DeltaTime();
		if (mTime <= 0.0f)
		{
			mIsRender = false;
		}
	}
	else if(!mIsRender)
	{
		SetShow(false);
		mTime = SHOW_TIME;
	}
}

void CDebugFieldOfView::Render()
{
	switch (mType)
	{
	case EType::eSector:
		// �\���Ώۂ����Ȃ��ꍇ�͕`�揈�����s��Ȃ�
		if (mpOwner == nullptr) return;

		// �f�v�X�e�X�g���I�t
		glDisable(GL_DEPTH_TEST);

		// �����I�ɔ������ɂ���
		mColor.A(0.3f);
		// ����͈͂̐�`��`��
		Primitive::DrawSector
		(
			mpOwner->Matrix(),// �\���Ώۂ̍s��
			-mFovAngle, mFovAngle, // -����p�x�`�{����p�x�͈̔͂�ݒ�
			mFovLength, // ���싗��
			mColor // ��`�̐F
		);
		// �f�v�X�e�X�g�̏�Ԃ�߂�
		glEnable(GL_DEPTH_TEST);
		break;
	case EType::eCone:
		// �\���Ώۂ����Ȃ��ꍇ�͕`�揈�����s��Ȃ�
		if (mpOwner == nullptr) return;

		// �f�v�X�e�X�g���I�t
		glDisable(GL_DEPTH_TEST);

		// �����I�ɔ������ɂ���
		mColor.A(0.3f);
		// ����͈͂̉~����`��
		Primitive::DrawCone
		(
			mpOwner->Position() + CVector(0.0f, -25.0f, 0.0f), // �~���̒�ʒ��S��ݒ�
			mpOwner->Position(),// �~���̒��_
			mFovLength, // ��ʂ̔��a
			mColor // �F
		);
		// �f�v�X�e�X�g�̏�Ԃ�߂�
		glEnable(GL_DEPTH_TEST);
		break;
	case EType::eNone:
		break;
	}

}
