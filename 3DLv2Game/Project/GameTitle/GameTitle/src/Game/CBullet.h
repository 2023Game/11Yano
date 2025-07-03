#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CSound.h"

class CTrailEffect;

// 弾丸クラス
class CBullet : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">弾丸の位置</param>
	/// <param name="dir">弾丸の向き</param>
	/// <param name="speed">移動速度</param>
	/// <param name="distance">飛距離</param>
	CBullet(const CVector& pos, const CVector& dir,
		float speed, float distance, ELayer layer);

	// デストラクタ
	~CBullet();

	// 更新
	void Update() override;
	// 描画
	void Render() override;

private:
	CSound* mpSE; // SEデータ
	CColliderLine* mpColliderLine;
	CTrailEffect* mpTrailEffect;	// 弾丸の軌跡のエフェクト
	float mMoveSpeed;				// 移動速度
	float mFlyingDistance;			// 飛距離
	float mCurrentFlyingDistance;	// 現在の飛距離
	CVector mMoveDir; // 発射方向
};