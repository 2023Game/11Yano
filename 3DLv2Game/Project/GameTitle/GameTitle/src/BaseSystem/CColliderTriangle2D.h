#pragma once
#include "CCollider.h"

/// <summary>
/// 三角形コライダー
/// </summary>
class CColliderTriangle2D : public CCollider
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">コライダーの持ち主</param>
	/// <param name="layer">衝突判定用レイヤー</param>
	/// <param name="v0">三角形の頂点 0</param>
	/// <param name="v1">三角形の頂点 1</param>
	/// <param name="v2">三角形の頂点 2</param>
	/// <param name="isKinematic">trueならば、衝突時に押し戻しの影響を受けない</param>
	/// <param name="weight">コライダーの重量</param>
	CColliderTriangle2D(CObjectBase* owner, ELayer layer,
		const CVector2& v0, const CVector2& v1, const CVector2& v2,
		bool isKinematic = false, float weight = 1.0f);

	/// <summary>
	/// 三角形コライダーの設定
	/// </summary>
	/// <param name="owner">コライダーの持ち主</param>
	/// <param name="layer">衝突判定用レイヤー</param>
	/// <param name="v0">三角形の頂点 0</param>
	/// <param name="v1">三角形の頂点 1</param>
	/// <param name="v2">三角形の頂点 2</param>
	void Set(CObjectBase* owner, ELayer layer,
		const CVector2& v0, const CVector2& v1, const CVector2& v2);

	/// <summary>
	/// 三角形の頂点を取得
	/// </summary>
	/// <param name="v0">頂点1格納用</param>
	/// <param name="v1">頂点2格納用</param>
	/// <param name="v2">頂点3格納用</param>
	void Get(CVector2* v0, CVector2* v1, CVector2* v2) const;

	// コライダー描画
	void Render() override;

protected:
	// コライダーの情報を更新
	void UpdateCol() override;

private:
	CVector2 mV[3];	// 三角形の頂点の配列
	CVector2 mWV[3];	// 三角形の頂点のワールド座標
};
