#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"
#include "CSound.h"

class CEnemy2D : public CObjectBase
{
public:
	CEnemy2D(const CVector2& pos, float bulletTime);
	~CEnemy2D();
	void Update();
	void Render();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	// ���S����
	bool Killed() const;
private:
	enum class EState
	{
		eIdle,
		eAttack,
		eDamage,
	};

	EState mState;

	CImage* mpImage;

	CSound* mpSE;

	float mTime;
	CColliderCircle2D* mpCollider;
	bool mKilled;
};