#ifndef CROBOT_H
#define CROBOT_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"

// 視野範囲のデバッグ表示クラスの前宣言
class CDebugFieldOfView;
class CNavNode;

/*
エネミークラス
キャラクタクラスを継承
*/
class CRobot : public CXCharacter
{
public:
	// コンストラクタ
	CRobot(std::vector<CVector> patrolPoints);
	~CRobot();
	void DeleteObject(CObjectBase* obj);
	// 更新処理
	void Update() override;
	void Render() override;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	
	enum class EAnimType
	{
		None = -1,

		eTpose,
		eIdle,
		eWalk,
		eRun,
		eAttack,
		eDie,

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
		eIdle,		// 待機
		ePatrol,    //  巡回中
		eChase,     // プレイヤーを追いかける
		eLost,      // プレイヤーを見失う
		eAttack,	// 攻撃
		eDie,       // 死
	};
	// 状態切り替え
	void ChangeState(EState state);

	// プレイヤーが視野範囲内に入ったかどうか
	bool IsFoundPlayer() const;
	// プレイヤーが見えているか
	bool IsLookPlayer() const;
	// プレイヤーを攻撃できるか
	bool CanAttackPlayer() const;
	
	// 指定した位置まで移動する
	bool MoveTo(const CVector& targetPos, float speed);
	// 次に巡回するポイントを変更
	void ChangePatrolPoint();

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

	CColliderCapsule* mpColliderCapsule; // 縦方向の線分コライダ
	//CColliderLine* mpColliderLineX; // 横方向(X)の線分コライダ
	//CColliderLine* mpColliderLineZ; // 横方向(Z)の線分コライダ

	std::vector<CNavNode*> mMoveRoute;// 求めた最短経路記憶用
	int mNextMoveIndex; // 次に移動するノードのインデックス値

	float mBulletTime;

	bool mDie;
};

#endif
