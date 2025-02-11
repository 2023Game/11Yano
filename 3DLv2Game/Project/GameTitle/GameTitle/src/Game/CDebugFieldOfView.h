#pragma once
#include "CObjectBase.h"

//����͈͂�\������f�o�b�O�@�\
class CDebugFieldOfView : public CObjectBase
{
public:
	CDebugFieldOfView(CObjectBase* owner,
		float fovAngle, float fovLength);
	~CDebugFieldOfView();

	// ����͈͂�\������Ώۂ�ݒ�
	void SetOwner(CObjectBase* owner);
	// ����͈͂�ݒ�
	void Set(float angle, float length);
	void Update() override;
	void Render() override;
private:
	CObjectBase* mpOwner; // �\������Ώۂ̃|�C���^
	float mFovAngle; // ����͈͂̊p�x�i�f�B�O���[�j
	float mFovLength; // ����͈͂̋���
};