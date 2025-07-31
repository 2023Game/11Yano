#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"
#include "CSound.h"

class CMryotaisu : public CObjectBase
{
public:
	CMryotaisu(const CVector2& pos);
	~CMryotaisu();
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
	CSound* mpSE;
	CImage* mpImage;
	CVector2 mPosition;
	CColliderCircle2D* mpCollider;

};