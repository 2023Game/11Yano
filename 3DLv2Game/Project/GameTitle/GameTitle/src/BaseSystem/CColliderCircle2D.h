#pragma once
#include "CCollider.h"

/// <summary>
/// 球コライダー
/// </summary>
class CColliderCircle2D : public CCollider
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">コライダーの持ち主</param>
	/// <param name="layer">衝突判定用レイヤー</param>
	/// <param name="radius">円の半径</param>
	/// <param name="isKinematic">trueならば、衝突時に押し戻しの影響を受けない</param>
	/// <param name="weight">コライダーの重量</param>
	CColliderCircle2D(CObjectBase* owner, ELayer layer, float radius,
		bool isKinematic = false, float weight = 1.0f);

	/// <summary>
	/// 円コライダーの設定
	/// </summary>
	/// <param name="owner">コライダーの持ち主</param>
	/// <param name="layer">衝突判定用レイヤー</param>
	/// <param name="radius">球の半径</param>
	void Set(CObjectBase* owner, ELayer layer, float radius);

	/// <summary>
	/// 円の座標と半径を取得
	/// </summary>
	/// <param name="pos">円の座標</param>
	/// <param name="rad">円の半径</param>
	void Get(CVector2* pos, float* rad) const;

	// コライダー描画
	void Render() override;

protected:
	// コライダーの情報を更新
	void UpdateCol() override;

private:
	CObjectBase* mpOwner;
	float mRadius;	// 円の半径
	float mPos;     // 円の位置
	CVector2 mWPos;	// ワールド座標
	float mWRadius;	// ワールド半径
};
