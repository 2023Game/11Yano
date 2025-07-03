#pragma once
#ifndef CINTERACTROBOT_H
#define CINTERACTROBOT_H
#include "CInteractObject.h"
#include "CColliderCapsule.h"
#include "CImage.h"
#include "CColliderSphere.h"
#include "CCollider.h"

// 視野範囲のデバッグ表示クラスの前宣言
class CDebugFieldOfView;
class CNavNode;
class CHackGame2;
class CSceneBase;

/*
エネミークラス
キャラクタクラスを継承
*/
class CInteractRobot : public CInteractObject
{
public:
	// コンストラクタ
	CInteractRobot();
	~CInteractRobot();
	void DeleteObject(CObjectBase* obj);
	// 更新処理
	void Update() override;
	void Render() override;
	void Interact() override;
	bool IsClear() const;
	void SetScene(CSceneBase* scene) { mpScene = scene; }

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	// キーの入力情報から移動ベクトルを求める
	CVector CalcMoveVec() const;

	// 移動の更新処理
	void UpdateMove();

	enum class EAnimType
	{
		None = -1,

		eTpose,
		eIdle,
		eWalk,
		eRun,
		eAttack,
		eDown,
		eWait,

		Num
	};
	void ChangeAnimation(EAnimType type);

	// アニメーションデータ
	struct AnimData
	{
		std::string path;	// アニメーションデータのパス
		bool loop;			// ループするかどうか
		float frameLength;	// アニメーションのフレーム数
	};
	// アニメーションデータのテーブル
	static const AnimData ANIM_DATA[];

	// 敵の状態
	enum class EState
	{
		eWait,       // 待機中
		ePlay,   // 操作中
	};
	// 状態切り替え
	void ChangeState(EState state);

	// 指定した位置まで移動する
	bool MoveTo(const CVector& targetPos, float speed);
	// 次に巡回するポイントを変更
	void CHangePatrolPoint();

	// 待機状態時の更新処理
	void UpdateIdle();
	// 巡回中の更新処理
	void UpdatePatrol();
	// 追跡中の更新処理
	void UpdateChase();
	// 見失った時の更新処理
	void UpdateLost();
	// 攻撃時の更新処理
	void UpdateAttack();

	// 状態の文字列を取得
	std::string GetStateStr(EState state) const;
	//状態の色を取得
	CColor GetStateColor(EState state) const;

	CVector mMoveSpeed;	// 前後左右の移動速度
	float mMoveSpeedY;	// 重力やジャンプによる上下の移動速度

	bool mIsGrounded;	// 接地しているかどうか
	CVector mGroundNormal;	// 接地している地面の法線

	EState mState;	// 敵の状態
	int mStateStep; // 状態内のステップ管理
	float mElapsedTime; // 経過時間計測用

	float mFovAngle; // 視野範囲の角度
	float mFovLength; // 視野範囲の距離
	CDebugFieldOfView* mpDebugFov; // 視野範囲のデバッグ表示

	CNavNode* mpLostPlayerNode; // プレイヤーを見失った位置のノード

	// 巡回ポイントのリスト
	std::vector<CNavNode*> mPatrolPoints;
	int mNextPatrolIndex; // 次に巡回するポイントの番号

	CColliderCapsule* mpColliderCapsule;
	CColliderSphere* mpColliderSphere;
	CVector mpTargetPos;
	bool mIsTarget;
	CObjectBase* mpTarget;

	std::vector<CNavNode*> mMoveRoute;// 求めた最短経路記憶用
	int mNextMoveIndex; // 次に移動するノードのインデックス値

	CHackGame2* mpHackGame;
	bool mIsHack;
	bool mIsClear;

	float mBulletTime;

	CSceneBase* mpScene;
	CImage* mpImage;
};

#endif
