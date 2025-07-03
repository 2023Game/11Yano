#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"
#include "CSound.h"

class CBullet2D : public CObjectBase
{
public:
	CBullet2D(CObjectBase* owner, const CVector2& pos, const CVector2& dir,
		float speed, float distance, ETag tag);
	~CBullet2D();
	void Update();
	void Render();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	float mMoveSpeed;				// �ړ����x
	float mFlyingDistance;			// �򋗗�
	float mCurrentFlyingDistance;	// ���݂̔򋗗�
	CVector2 mMoveDir; // ���˕���
	CImage* mpImage;
	CColliderCircle2D* mpCollider;
	CObjectBase* mpOwner;

	CSound* mpSE;
};