#include "CDebugFieldOfView.h"
#include "Primitive.h"
#include "glut.h"

CDebugFieldOfView::CDebugFieldOfView(CObjectBase* owner,
	float fovAngle, float fovLength)
	: CObjectBase(ETag::eDebug, ETaskPriority::eDebugFov, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mFovAngle(fovAngle)
	, mFovLength(fovLength)
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

void CDebugFieldOfView::Set(float angle, float length)
{
	mFovAngle = angle;
	mFovLength = length;
}

void CDebugFieldOfView::Update()
{
}

void CDebugFieldOfView::Render()
{
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
}
