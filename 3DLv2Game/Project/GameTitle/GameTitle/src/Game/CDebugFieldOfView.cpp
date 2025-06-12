#include "CDebugFieldOfView.h"
#include "Primitive.h"
#include "glut.h"

CDebugFieldOfView::CDebugFieldOfView(CObjectBase* owner,
	float fovAngle, float fovLength, EType type)
	: CObjectBase(ETag::eDebug, ETaskPriority::eDebugFov, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mFovAngle(fovAngle)
	, mFovLength(fovLength)
	, mType(type)
{
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
			mpOwner->Position() + CVector(0.0f, -30.0f, 0.0f), // �~���̒�ʒ��S��ݒ�
			mpOwner->Position(),// �~���̒��_
			mFovLength, // ��ʂ̔��a
			mColor // �F
		);
		// �f�v�X�e�X�g�̏�Ԃ�߂�
		glEnable(GL_DEPTH_TEST);
		break;
	}
}
