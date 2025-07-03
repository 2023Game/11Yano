#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CSound.h"

class CTrailEffect;

// �e�ۃN���X
class CBullet : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�e�ۂ̈ʒu</param>
	/// <param name="dir">�e�ۂ̌���</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="distance">�򋗗�</param>
	CBullet(const CVector& pos, const CVector& dir,
		float speed, float distance, ELayer layer);

	// �f�X�g���N�^
	~CBullet();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CSound* mpSE; // SE�f�[�^
	CColliderLine* mpColliderLine;
	CTrailEffect* mpTrailEffect;	// �e�ۂ̋O�Ղ̃G�t�F�N�g
	float mMoveSpeed;				// �ړ����x
	float mFlyingDistance;			// �򋗗�
	float mCurrentFlyingDistance;	// ���݂̔򋗗�
	CVector mMoveDir; // ���˕���
};