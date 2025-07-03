#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"

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
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	// プレイヤーのインスタンス
	static CPlayer2D* spInstance;
	enum class EState
	{
		eIdle,
		eAttack,
		eDamage,
	};

	EState mState;
	ETag mTag;
	CImage* mpImage;

	float mTime;
	CVector2 mPosition;
	CColliderCircle2D* mpCollider;

	int mHp;
};