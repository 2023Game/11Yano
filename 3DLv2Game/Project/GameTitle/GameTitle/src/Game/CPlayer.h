#pragma once
//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CSound.h"
#include "CColliderSphere.h"
#include "CImage.h"

class CInteractObject;
class CSceneBase;
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

	void SetScene(CSceneBase* scene) { mpScene = scene; }
	// 更新
	void Update();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	// 衝突状態管理
	void PostCollisionUpdate();
	// コライダーが離れた
	void OnCollisionExit(CCollider* col);

	// image画像切替
	int SetImage() const;

	// 描画
	void Render();

	bool IsInteract() const;
	// 死亡判定
	bool IsDie() const;
private:
	// キーの入力情報から移動ベクトルを求める
	CVector CalcMoveVec() const;

	// 待機状態
	void UpdateIdle();

	void UpdateDamage();

	void UpdateDie();

	// 移動の更新処理
	void UpdateMove();

	// アニメーションの種類
	enum class EAnimType
	{
		None = -1,

		eTPose,		// Tポーズ
		eIdle,		// 待機
		eWalk,		// 歩行
		eRun,       // 走る
		eDamage,    // ダメージ
		eDie,       // 死


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
		eDamage,
		eDie,
	};
	EState mState;	// プレイヤーの状態

	CVector mMoveSpeed;	// 前後左右の移動速度
	float mMoveSpeedY;	// 重力やジャンプによる上下の移動速度

	bool mIsDash; // ダッシュ中
	bool mIsInteract; // インタラクト可能なオブジェクトに触れているか
	

	CColliderCapsule* mpColliderCapsule; // プレイヤー自身のコライダ
	CColliderSphere* mpCollider; // インタラクト用コライダ

	bool mIsGrounded;	// 接地しているかどうかAdd commentMore actions
	CVector mGroundNormal;	// 接地している地面の法線

	CInteractObject* GetNearInteractObj() const;
	std::list<CInteractObject*> mNearInteractObjs;

	CSound* mpSE;

	int mSetImage; // イメージ画像の切替用

	std::vector<CCollider*> mColliders;
	std::vector<CCollider*> mCurrentColliders;

	CSceneBase* mpScene;

	bool mIsDie;
};
