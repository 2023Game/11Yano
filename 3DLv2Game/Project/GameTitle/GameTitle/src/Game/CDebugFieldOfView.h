#pragma once
#include "CObjectBase.h"

//����͈͂�\������f�o�b�O�@�\
class CDebugFieldOfView : public CObjectBase
{
public:
	enum class EType
	{
		eSector,
		eCone,
	};
	CDebugFieldOfView(CObjectBase* owner,
		float fovAngle, float fovLength, EType type);
	~CDebugFieldOfView();

	// ����͈͂�\������Ώۂ�ݒ�
	void SetOwner(CObjectBase* owner);
	// ����͈͂�ݒ�
	void Set(float angle, float length, EType type);
	void Update() override;
	void Render() override;
private:
	
	CObjectBase* mpOwner; // �\������Ώۂ̃|�C���^
	float mFovAngle; // ����͈͂̊p�x�i�f�B�O���[�j
	float mFovLength; // ����͈͂̋���
	EType mType;
};