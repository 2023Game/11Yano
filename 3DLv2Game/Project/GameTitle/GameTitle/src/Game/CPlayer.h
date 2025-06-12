#pragma once
//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CRideableObject.h"
#include "CSound.h"
#include "CColliderSphere.h"
#include "CImage.h"

class CInteractObject;
class CGameScene;
/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CXCharacter
{
public:
	//インスタンスのポインタの取得
	static CPlayer* Instance();

	// コンストラクタ
	CPlayer();
	// デストラクタ
	~CPlayer();

	void SetScene(CGameScene* scene) { mpScene = scene; }
	// 更新
	void Update();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// 描画
	void Render();

	bool IsPlaying() const;

private:
	// キーの入力情報から移動ベクトルを求める
	CVector CalcMoveVec() const;

	// 待機状態
	void UpdateIdle();


	// 移動の更新処理
	void UpdateMove();

	// アニメーションの種類
	enum class EAnimType
	{
		None = -1,

		eTPose,		// Tポーズ
		eIdle,		// 待機
		eWalk,		// 歩行
		eSneak,     // しゃがみ


		Num
	};
	// アニメーション切り替え
	void ChangeAnimation(EAnimType type);

	// プレイヤーのインスタンス
	static CPlayer* spInstance;

	// アニメーションデータ
	struct AnimData
	{
		std::string path;	// アニメーションデータのパス
		bool loop;			// ループするかどうか
		float frameLength;	// アニメーションのフレーム数
	};
	// アニメーションデータのテーブル
	static const AnimData ANIM_DATA[];

	// プレイヤーの状態
	enum class EState
	{
		eIdle,		// 待機
		eSneak,     // しゃがみ
	};
	EState mState;	// プレイヤーの状態

	CVector mMoveSpeed;	// 前後左右の移動速度
	float mMoveSpeedY;	// 重力やジャンプによる上下の移動速度

	bool mIsDash;
	

	CColliderCapsule* mpColliderCapsule; // プレイヤーのコライダ
	CColliderSphere* mpCollider;
	CTransform* mpRideObject;

	CInteractObject* GetNearInteractObj() const;
	std::list<CInteractObject*> mNearInteractObjs;

	CSound* mpSlashSE;
	bool mIsPlayedSlashSE;
	bool mIsSpawnedSlashEffect;

	CImage* mpUIHack;

	bool mIsPlaying;

	CGameScene* mpScene;

};
