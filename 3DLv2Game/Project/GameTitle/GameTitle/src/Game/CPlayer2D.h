#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"
#include "CSound.h"

class CPlayer2D : public CObjectBase
{
public:
	static CPlayer2D* Instance();
	CPlayer2D(const CVector2& pos);
	~CPlayer2D();
	void Update();
	void Render();

	void UpdateIdle();
	void UpdateAttack();
	void UpdateDamage();

	bool IsAttack() const;

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
	// �v���C���[�̃C���X�^���X
	static CPlayer2D* spInstance;
	enum class EState
	{
		eIdle,
		eAttack,
		eDamage,
	};
	CSound* mpSE;
	EState mState;
	ETag mTag;
	CImage* mpImage;
	CImage* mpHp1;
	CImage* mpHp2;
	CImage* mpHp3;
	int mHp;

	float mTime;
	CVector2 mPosition;
	CColliderCircle2D* mpCollider;
	bool mKilled;
};