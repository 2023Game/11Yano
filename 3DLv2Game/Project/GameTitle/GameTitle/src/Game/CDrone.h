#ifndef CDRONE_H
#define CDRONE_H
#include "CXCharacter.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CDebugFieldOfView;
class CNavNode;

class CDrone : public CXCharacter
{
public:
	CDrone(std::vector<CVector> patrolPoints);
	~CDrone();
	void DeleteObject(CObjectBase* obj);
	void Update() override;
	void Render() override;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	void Stop();
private:
	// 敵の状態
	enum class EState
	{
		eIdle,		// 待機
		ePatrol,    //  巡回中
		eChase,     // プレイヤーを追いかける
		eLost,      // プレイヤーを見失う
		eAttack,	// 攻撃
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

	
	CColliderMesh* mpColliderMesh;

	// 状態の文字列を取得
	std::string GetStateStr(EState state) const;
	//状態の色を取得
	CColor GetStateColor(EState state) const;

	EState mState;
	int mStateStep; // 状態内のステップ管理
	float mElapsedTime; // 経過時間計測用
	CDebugFieldOfView* mpDebugFov; // 視野範囲のデバッグ表示

	CNavNode* mpLostPlayerNode; // プレイヤーを見失った位置のノード

	// 巡回ポイントのリスト
	std::vector<CNavNode*> mPatrolPoints;
	int mNextPatrolIndex; // 次に巡回するポイントの番号

	float mFovAngle; // 視野範囲の角度
	float mFovLength; // 視野範囲の距離
	float mFovHeight; // 視野範囲の高さ

	std::vector<CNavNode*> mMoveRoute;// 求めた最短経路記憶用
	int mNextMoveIndex; // 次に移動するノードのインデックス値

	CModel* mpModel;
	float mBulletTime;
	bool mStop;
};

#endif