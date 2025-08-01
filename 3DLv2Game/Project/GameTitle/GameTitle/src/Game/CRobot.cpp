#include "CRobot.h"
#include "CInput.h"
#include "CDebugFieldOfView.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Primitive.h"
#include "CFieldBase.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CBullet.h"
#include "CColliderCapsule.h"
#include "CBlackOut.h"
#include "CTaskManager.h"

#define ROBOT_HEIGHT		13.0f
#define ROBOT_WIDTH			10.0f
#define FOV_ANGLE			45.0f // 視野範囲の角度
#define FOV_LENGTH			40.0f // 視野範囲の距離
#define EYE_HEIGHT			10.0f // 視点の高さ
#define WALK_SPEED			10.0f // 歩行速度
#define RUN_SPEED			20.0f // 走行速度
#define ROTATE_SPEED		 6.0f // 回転速度
#define ATTACK_LANGE		35.0f // 攻撃範囲
#define PATROL_INTERVAL		 3.0f // 次の巡回ポイントに移動開始するまでの時間
#define PATROL_NEAR_DIST	10.0f // 巡回開始時に選択される巡回ポイントの最短距離
#define IDLE_TIME			 5.0f // 待機状態の時間
#define BULLET_TIME			 0.5f // 弾の発射間隔


// プレイヤーのアニメーションデータのテーブル
const CRobot::AnimData CRobot::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// Tポーズ
	{ "Character\\Robot\\anim\\idle.x",			true,	110.0f	},	// 待機
	{ "Character\\Robot\\anim\\walk.x",			true,	78.0f	},	// 歩行
	{ "Character\\Robot\\anim\\run.x",			true,	44.0f	},	// 走行
	{ "Character\\Robot\\anim\\attack.x",		true,	86.0f	},	// 攻撃
	{ "Character\\Robot\\anim\\down.x",			false,	59.0f	},	// 死
	{ "Character\\Robot\\anim\\sit.x",			true,	0.0f	},	// 座る
	{ "Character\\Robot\\anim\\around.x",		true,	221.0f	},	// 見渡す

};

// コンストラクタ
CRobot::CRobot(std::vector<CVector> patrolPoints, CVector& rotate)
	: CXCharacter(ETag::eEnemy, ETaskPriority::eDefault)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mFovAngle(FOV_ANGLE)
	, mFovLength(FOV_LENGTH)
	, mpDebugFov(nullptr)
	, mNextPatrolIndex(-1)
	, mNextMoveIndex(0)
	, mBulletTime(0.0f)
{
	Rotate(rotate);
	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Robot");

	// テーブル内のアニメーションデータを読み込み
	int size = ARRAY_SIZE(ANIM_DATA);
	for (int i = 0; i < size; i++)
	{
		const AnimData& data = ANIM_DATA[i];
		if (data.path.empty()) continue;
		model->AddAnimationSet(data.path.c_str());
	}
	// CXCharacterの初期化
	Init(model);

	// 最初は待機アニメーションを再生
	ChangeAnimation(EAnimType::eIdle);

	mpColliderCapsule = new CColliderCapsule
	(
		this, ELayer::eEnemy,
		CVector(0.0f, 3.0f, 0.0f),
		CVector(0.0f, ROBOT_HEIGHT, 0.0f),
		3.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eRange, ELayer::ePlayer });

	// 視野範囲のデバッグ表示クラスを作成
	mpDebugFov = new CDebugFieldOfView(this, mFovAngle, mFovLength, CDebugFieldOfView::EType::eSector);

	// 経路探索用ノードを作成
	mpNavNode = new CNavNode(Position(), true);
	mpNavNode->SetColor(CColor::blue);

	mpLostPlayerNode = new CNavNode(CVector::zero, true);

	// 巡回ポイントに経路探索用のノードを配置
	for (CVector point : patrolPoints)
	{
		CNavNode* node = new CNavNode(point, true);
		mPatrolPoints.push_back(node);
	}
}

CRobot::~CRobot()
{
	SAFE_DELETE(mpColliderCapsule);


	// 視野範囲のデバッグ表示が存在したら一緒に削除
	if (mpDebugFov != nullptr)
	{
		mpDebugFov->SetOwner(nullptr);
		mpDebugFov->Kill();
	}

	// 経路探索用ノードの破棄
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		mpNavNode = nullptr;
		mpLostPlayerNode = nullptr;

		mPatrolPoints.clear();
	}
}

void CRobot::DeleteObject(CObjectBase* obj)
{
	// 削除されたオブジェクトが視野範囲のデバッグ表示であればポインタを空にする
	if (obj == mpDebugFov)
	{
		mpDebugFov = nullptr;
	}
}

//更新処理
void CRobot::Update()
{
	if (IsKill())
	{
		return;
	}

	// 現在の状態に合わせて更新処理を切替
	switch (mState)
	{
	case EState::eIdle: UpdateIdle(); break;
	case EState::ePatrol: UpdatePatrol(); break;
	case EState::eChase: UpdateChase(); break;
	case EState::eLost: UpdateLost(); break;
	case EState::eAttack: UpdateAttack(); break;
	case EState::eAround: UpdateAround(); break;
	case EState::eDie: UpdateDie(); break;
	}

	CXCharacter::Update();

	// 経路探索用ノードが存在したら座標更新
	if (mpNavNode != nullptr)
	{
		mpNavNode->SetPos(Position());
	}

	if (mpDebugFov != nullptr)
	{
		//現在の状態に合わせて視野範囲の色を変更
		mpDebugFov->SetColor(GetStateColor(mState));
	}

	CBlackOut* black = CBlackOut::Instance();
	if (black->IsBlack())
	{
		ChangeAnimation(EAnimType::eAround);
		mState = EState::eAround;
	}
	//CDebugPrint::Print("状態 : %s\n", GetStateStr(mState).c_str());
}

void CRobot::Render()
{
	CXCharacter::Render();

	//if (mState == EState::ePatrol)
	//{
	//	float rad = 1.0f;
	//	// 巡回ポイントを描画
	//	int size = mPatrolPoints.size();
	//	for (int i = 0; i < size; i++)
	//	{
	//		CMatrix m;
	//		m.Translate(mPatrolPoints[i]->GetPos() + CVector(0.0f, rad * 2.0f, 0.0f));
	//		CColor c = i == mNextPatrolIndex ? CColor::red : CColor::cyan;
	//		Primitive::DrawSphere(m, rad, c);
	//	}
	//}

	//// プレイヤーを見失った位置にデバッグ表示
	//if (mState == EState::eLost)
	//{
	//	// プレイヤーを見失った位置にデバッグ表示
	//	float rad = 2.0f;
	//	CMatrix m;
	//	m.Translate(mpLostPlayerNode->GetPos() + CVector(0.0f, rad, 0.0f));
	//	Primitive::DrawWireSphere(m, rad, CColor::blue);
	//}

	//CPlayer* player = CPlayer::Instance();
	//CFieldBase* field = CFieldBase::Instance();
	//if (player != nullptr && field != nullptr)
	//{
	//	CVector offsetPos = CVector(0.0f, EYE_HEIGHT, 0.0f);
	//	CVector playerPos = player->Position() + offsetPos;
	//	CVector selfPos = Position() + offsetPos;

	//	// プレイヤーとの間に遮蔽物が存在する場合
	//	CHitInfo hit;
	//	if (field->CollisionRay(selfPos, playerPos, &hit))
	//	{
	//		// 衝突した位置まで赤線描画
	//		Primitive::DrawLine
	//		(
	//			selfPos, hit.cross,
	//			CColor::red,
	//			2.0f
	//		);
	//	}
	//	else
	//	{
	//		Primitive::DrawLine
	//		(
	//			selfPos, playerPos,
	//			CColor::green,
	//			2.0f
	//		);
	//	}
	//}
}

void CRobot::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eField)
		{
			// 坂道で滑らないように、押し戻しベクトルのXとZの値を0にする
			CVector adjust = hit.adjust;
			adjust.X(0.0f);
			adjust.Z(0.0f);

			Position(Position() + adjust * hit.weight);
		}
		if (other->Layer() == ELayer::eAttackCol)
		{
			ChangeAnimation(EAnimType::eDie);
			mState = EState::eDie;

		}
	}
}

bool CRobot::IsPlayerChase() const
{
	if (mState == EState::eChase || mState == EState::eAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CRobot::IsPlayerLost() const
{
	if (mState == EState::eLost)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//
//std::list<CRobot*> CRobot::GetRobots() const
//{
//	return mRobots;
//}

void CRobot::ChangeAnimation(EAnimType type)
{
	int index = (int)type;
	if (!(0 <= index && index < (int)EAnimType::Num)) return;
	const AnimData& data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

void CRobot::ChangeState(EState state)
{
	//すでに同じ状態であれば処理しない
	if (state == mState) return;

	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

bool CRobot::IsFoundPlayer() const
{
	// プレイヤーが存在しない場合は視野範囲外とする
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;

	// プレイヤー座標取得
	CVector playerPos = player->Position();
	// 自分自身の座標を取得
	CVector pos = Position();
	// 自身からプレイヤーまでのベクトルを求める
	CVector vec = playerPos - pos;
	vec.Y(0.0f); // プレイヤーとの高さの差を考慮しない

	// �@視野角度内か求める
	// ベクトルを正規化して長さを1にする
	CVector dir = vec.Normalized();
	// 自身の正面方向ベクトルを取得
	CVector forward = VectorZ();
	// プレイヤーまでのベクトルと自身の正面方向ベクトルの内積を求めて角度を出す
	float dot = CVector::Dot(dir, forward);
	// 視野角度のラジアンを求める
	float angleR = Math::DegreeToRadian(mFovAngle);
	// 求めた内積と視野角度で視野範囲内か判断する
	if (dot < cosf(angleR)) return false;

	// �A視野距離内か求める
	// プレイヤーまでの距離と視野距離で視野範囲内か判断する
	float dist = vec.Length();
	if (dist > mFovLength) return false;

	// プレイヤーとの間に遮蔽物がないか確認
	if (!IsLookPlayer()) return false;

	//すべての条件をクリアしているので視野範囲内である
	return true;
}

bool CRobot::IsLookPlayer() const
{
	// プレイヤーが存在しない場合は見えない
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;
	// フィールドが存在しない場合(遮蔽物がない)は見える
	CFieldBase* field = CFieldBase::Instance();
	if (field == nullptr) return true;

	CVector offsetPos = CVector(0.0f, EYE_HEIGHT, 0.0f);
	// プレイヤー座標取得
	CVector playerPos = player->Position() + offsetPos;
	// 自分の座標取得
	CVector selfPos = Position() + offsetPos;

	CHitInfo hit;
	// 遮蔽物が存在した場合プレイヤーが見えない
	if (field->CollisionRay(selfPos, playerPos, &hit)) return false;

	return true;
}

bool CRobot::CanAttackPlayer() const
{
	// プレイヤーがいない場合はfalse
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;

	// プレイヤーまでの距離が攻撃範囲外であればfalse
	CVector playerPos = player->Position();
	CVector vec = playerPos - Position();
	vec.Y(0.0f);
	float dist = vec.Length();
	if (dist > ATTACK_LANGE) return false;


	return true;
}

bool CRobot::MoveTo(const CVector& targetPos, float speed)
{
	// 目的地までのベクトルを求める
	CVector pos = Position();
	CVector vec = targetPos - pos;
	vec.Y(0.0f);
	// 移動方向ベクトルを求める
	CVector moveDir = vec.Normalized();

	// ジョジョに移動方向へ向ける
	CVector forward = CVector::Slerp
	(
		VectorZ(),
		moveDir,
		ROTATE_SPEED * Times::DeltaTime()
	);
	Rotation(CQuaternion::LookRotation(moveDir));

	// 今回の移動距離を求める
	float moveDist = speed * Times::DeltaTime();
	//目的地までの残り距離を求める
	float remainDist = vec.Length();
	// 残りの距離が移動距離より短い
	if (remainDist <= moveDist)
	{
		// 目的地まで移動する
		pos = CVector(targetPos.X(), pos.Y(), targetPos.Z());
		Position(pos);
		return true; // 目的地の到着したのでtrue
	}

	// 残りの距離が移動距離より長い場合は移動距離文目的地へ移動
	pos += moveDir * moveDist;
	Position(pos);

	// 目的地に到着しなかった
	return false;
}

void CRobot::ChangePatrolPoint()
{
	// 巡回ポイント後設定されていない場合処理しない
	int size = mPatrolPoints.size();
	if (size == 0) return;


	// 巡回開始時であれば一番近い巡回ポイントを選択
	if (mNextPatrolIndex == -1)
	{
		int nearIndex = -1; // 一番近い巡回ポイントの番号
		float nearDist = 0.0f; // 一番近い巡回ポイントまでの距離
		// すべての巡回ポイントの距離を調べ一番近い巡回ポイントを探す
		for (int i = 0; i < size; i++)
		{
			CVector point = mPatrolPoints[i]->GetPos();
			CVector vec = point - Position();
			vec.Y(0.0f);
			float dist = vec.Length();
			// 巡回ポイントが近すぎる場合はスルー
			if (dist < PATROL_NEAR_DIST) continue;
			// 一番最初の巡回ポイントもしくは現在一番近い巡回ポイントよりさらに近い場合
			// 巡回ポイントの番号を置き換える
			if (nearIndex < 0 || dist < nearDist)
			{
				nearIndex = i;
				nearDist = dist;
			}
		}
		mNextPatrolIndex = (nearIndex >= 0) ? nearIndex : 0;
	}
	// 巡回中の場合次の巡回ポイントを指定する
	else
	{
		mNextPatrolIndex++;
		if (mNextPatrolIndex >= size) mNextPatrolIndex -= size;
	}

	// 次に巡回するポイントが決まった時
	if (mNextMoveIndex >= 0)
	{
		CNavManager* navMgr = CNavManager::Instance();
		if (navMgr != nullptr)
		{
			for (CNavNode* node : mPatrolPoints)
			{
				node->SetPos(node->GetPos());
			}
			//巡回ポイントまでの最短経路を求める
			if (navMgr->Navigate(mpNavNode, mPatrolPoints[mNextPatrolIndex], mMoveRoute))
			{
				// 次の目的地のインデックスを設定
				mNextMoveIndex = 1;
			}
		}
	}
}

void CRobot::UpdateIdle()
{
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}

	// 待機アニメーションを再生
	ChangeAnimation(EAnimType::eIdle);

	if (mPatrolPoints.size() > 1)
	{
		if (mElapsedTime < IDLE_TIME)
		{
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			// 待機時間経過したら巡回状態へ移行
			ChangeState(EState::ePatrol);
		}
	}

}

void CRobot::UpdatePatrol()
{
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}


	// ステップごとに処理を切り替える
	switch (mStateStep)
	{
		// 巡回開始時の巡回ポイントを求める
	case 0:
		mNextPatrolIndex = -1;
		ChangePatrolPoint();
		mStateStep++;
		break;
		// 巡回ポイントまで移動
	case 1:
	{
		ChangeAnimation(EAnimType::eWalk);
		CNavNode* moveNode = mMoveRoute[mNextMoveIndex];
		if (MoveTo(moveNode->GetPos(), WALK_SPEED))
		{
			// 移動が終われば次のノードへ切替
			mNextMoveIndex++;
			// 最後のノードだった場合は次のステップへ進む
			if (mNextMoveIndex >= mMoveRoute.size())
			{
				mStateStep++;
			}
		}
		break;
	}
	// 移動後の待機
	case 2:
		ChangeAnimation(EAnimType::eIdle);
		if (mElapsedTime < PATROL_INTERVAL)
		{
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			ChangePatrolPoint();
			mStateStep = 1;
			mElapsedTime = 0.0f;
		}
		break;
	}
}

void CRobot::UpdateChase()
{
	// プレイヤーを追跡
	CPlayer* player = CPlayer::Instance();
	CVector targetPos = player->Position();

	if (!IsLookPlayer())
	{
		// 見失った位置にノードを配置
		mpLostPlayerNode->SetPos(targetPos);
		ChangeState(EState::eLost);
		return;
	}
	// プレイヤーに攻撃できるなら攻撃状態へ移行
	if (CanAttackPlayer())
	{
		ChangeState(EState::eAttack);
		return;
	}

	// 走るアニメーションを再生
	ChangeAnimation(EAnimType::eRun);


	//// 経路探索管理クラスが存在するとき
	//CNavManager* navMgr = CNavManager::Instance();
	//if (navMgr != nullptr)
	//{
	//	// 自身のノードからプレイヤーのノードまでの最短経路を求める
	//	CNavNode* playerNode = player->GetNavNode();
	//	if (navMgr->Navigate(mpNavNode, playerNode, mMoveRoute))
	//	{
	//		targetPos = mMoveRoute[1]->GetPos();
	//	}
	//}

	if (MoveTo(targetPos, RUN_SPEED))
	{

	}
}

void CRobot::UpdateLost()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr == nullptr)
	{
		ChangeState(EState::eIdle);
		return;
	}
	// プレイヤーが見えたら追跡状態へ移行(もとはIsLook)
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}

	ChangeAnimation(EAnimType::eRun);

	switch (mStateStep)
	{
		// 見失った位置までの最短経路を求める
	case 0:
		if (navMgr->Navigate(mpNavNode, mpLostPlayerNode, mMoveRoute))
		{
			mNextMoveIndex = 1;
			mStateStep++;
		}
		else
		{
			ChangeState(EState::eIdle);
		}

		break;
	case 1:
		// 見失った位置まで移動
		if (MoveTo(mMoveRoute[mNextMoveIndex]->GetPos(), RUN_SPEED))
		{
			mNextMoveIndex++;
			if (mNextMoveIndex >= mMoveRoute.size())
			{
				// 移動が終われば待機状態へ
				ChangeState(EState::eIdle);
			}
		}
		break;
	}

}

void CRobot::UpdateAttack()
{
	ChangeAnimation(EAnimType::eAttack);
	mBulletTime -= Times::DeltaTime();
	CPlayer* player = CPlayer::Instance();
	// プレイヤー座標取得
	CVector playerPos = player->Position();
	// 自分自身の座標を取得
	CVector pos = Position();
	// 自身からプレイヤーまでのベクトルを求める
	CVector vec = playerPos - pos;
	// プレイヤーの方向を向く
	Rotation(CQuaternion::LookRotation(CVector(vec.X(),0.0f,vec.Z())));
	if (mBulletTime <= 0)
	{
		// 弾丸を生成
		new CBullet
		(
			// 発射位置
			Position() + CVector(0.0f, 14.0f, 0.0f),
			vec + CVector(0.0f, -4.0f, 0.0f),	// 発射方向
			100.0f,	// 移動距離
			100.0f,		// 飛距離
			ELayer::eBullet
		);
		mBulletTime = BULLET_TIME;
	}
	if (!CanAttackPlayer())
	{
		if (!IsFoundPlayer())
		{
			ChangeState(EState::eLost);
			return;
		}
		ChangeState(EState::eChase);
	}
}

void CRobot::UpdateAround()
{
	CBlackOut* black = CBlackOut::Instance();
	if (!black->IsBlack())
	{
		ChangeAnimation(EAnimType::eIdle);
		mState = EState::eIdle;
	}
}

void CRobot::UpdateDie()
{
	if (GetAnimationFrameRatio() >= 1.0f)
	{
		mpNavNode->ClearConnects();
		
		CTask::Kill();
		CTask::SetEnable(false);
		nullptr;
		return;
	}
}

std::string CRobot::GetStateStr(EState state) const
{
	switch (mState)
	{
	case EState::eIdle: return "待機";
	case EState::ePatrol: return "巡回";
	case EState::eChase: return "追跡";
	case EState::eLost: return "見失う";
	case EState::eAttack: return "攻撃";
	case EState::eAround: return "見渡す";
	}
	return std::string();
}

CColor CRobot::GetStateColor(EState state) const
{
	switch (mState)
	{
	case EState::eIdle: return CColor::green;
	case EState::ePatrol: return CColor::green;
	case EState::eChase: return CColor::red;
	case EState::eLost: return CColor::yellow;
	case EState::eAttack: return CColor::red;
	case EState::eAround: return CColor::yellow;
	}
	return CColor::white;
}
