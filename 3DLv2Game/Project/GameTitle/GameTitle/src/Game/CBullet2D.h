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
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	float mMoveSpeed;				// 移動速度
	float mFlyingDistance;			// 飛距離
	float mCurrentFlyingDistance;	// 現在の飛距離
	CVector2 mMoveDir; // 発射方向
	CImage* mpImage;
	CColliderCircle2D* mpCollider;
	CObjectBase* mpOwner;

	CSound* mpSE;
};