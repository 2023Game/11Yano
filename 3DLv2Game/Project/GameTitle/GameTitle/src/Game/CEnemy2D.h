#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"

class CEnemy2D : public CObjectBase
{
public:
	CEnemy2D(const CVector2& pos, float bulletTime);
	~CEnemy2D();
	void Update();
	void Render();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	enum class EState
	{
		eIdle,
		eAttack,
		eDamage,
	};

	EState mState;

	CImage* mpImage;

	float mTime;
	CColliderCircle2D* mpCollider;
};