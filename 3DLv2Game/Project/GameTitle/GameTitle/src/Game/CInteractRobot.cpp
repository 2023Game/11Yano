#include "CInteractRobot.h"
#include "CInput.h"
#include "CDebugFieldOfView.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Primitive.h"
#include "CField.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CHackGame2.h"
#include "CBullet.h"
#include "CSceneBase.h"

#define ROBOT_HEIGHT 13.0f
#define ROBOT_WIDTH 10.0f
#define MOVE_SPEED	  0.375f * 2.0f // 移動速度
#define GRAVITY	  0.0625f // 重力
#define FOV_ANGLE 45.0f // 視野範囲の角度
#define FOV_LENGTH 100.0f // 視野範囲の距離
#define EYE_HEIGHT 10.0f // 視点の高さ
#define WALK_SPEED 10.0f // 歩行速度
#define RUN_SPEED 20.0f // 走行速度
#define ROTATE_SPEED 6.0f // 回転速度
#define ATTACK_LANGE 40.0f // 攻撃範囲
#define PATROL_INTERVAL 3.0f // 次の巡回ポイントに移動開始するまでの時間
#define PATROL_NEAR_DIST 10.0f // 巡回開始時に選択される巡回ポイントの最短距離
#define IDLE_TIME 5.0f // 待機状態の時間
#define BULLET_TIME 0.5f // 弾の発射間隔


// プレイヤーのアニメーションデータのテーブル
const CInteractRobot::AnimData CInteractRobot::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// Tポーズ
	{ "Character\\Robot\\anim\\idle.x",		true,	110.0f	},	// 待機
	{ "Character\\Robot\\anim\\walk.x",		true,	78.0f	},	// 歩行
	{ "Character\\Robot\\anim\\run.x",		true,	44.0f	},	// 走行
	{ "Character\\Robot\\anim\\attack.x",		true,	86.0f	},	// 攻撃
	{ "Character\\Robot\\anim\\down.x",		false,	59.0f	},	// 死
	{ "Character\\Robot\\anim\\sit.x",		true,	0.0f	},	// 座る

};

// コンストラクタ
CInteractRobot::CInteractRobot()
	: mState(EState::eWait)
	, mMoveSpeedY(0.0f)
	, mIsGrounded(false)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mFovAngle(FOV_ANGLE)
	, mFovLength(FOV_LENGTH)
	, mpDebugFov(nullptr)
	, mNextPatrolIndex(-1)
	, mNextMoveIndex(0)
	, mpHackGame(nullptr)
	, mIsHack(false)
	, mIsClear(false)
	, mBulletTime(0.0f)
{
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
		this, ELayer::eInteractObj,
		CVector(0.0f, 3.0f, 0.0f),
		CVector(0.0f, ROBOT_HEIGHT, 0.0f),
		3.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eField, ELayer::eInteractSearch });

	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eRange,
		70.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eEnemy, ELayer::eField });

	mpHackGame = new CHackGame2();
	mInteractStr = "オンにする";

}

CInteractRobot::~CInteractRobot()
{
	SAFE_DELETE(mpColliderSphere);
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
		SAFE_DELETE(mpNavNode);
		SAFE_DELETE(mpLostPlayerNode);

		// 巡回ポイントに配置したノードをすべて削除
		auto itr = mPatrolPoints.begin();
		auto end = mPatrolPoints.end();
		while (itr != end)
		{
			CNavNode* del = *itr;
			itr = mPatrolPoints.erase(itr);
			delete del;
		}
	}
}

void CInteractRobot::DeleteObject(CObjectBase* obj)
{
	// 削除されたオブジェクトが視野範囲のデバッグ表示であればポインタを空にする
	if (obj == mpDebugFov)
	{
		mpDebugFov = nullptr;
	}
}

//更新処理
void CInteractRobot::Update()
{

	//mMoveSpeedY -= GRAVITY;
	
	switch (mState)
	{
	case EState::eWait:
		ChangeAnimation(EAnimType::eWait);
		break;
		// 操作可能状態
	case EState::ePlay:
		UpdateIdle();
		UpdateMove();
		break;
	}

	//CDebugPrint::Print("状態 : %s\n", GetStateStr(mState).c_str());
	if (mpHackGame->IsClear())
	{
		mIsClear = true;
		mpColliderCapsule->ChangeLayer(ELayer::ePlayer);
	}

	if (mpScene->CameraTarget() != this)
	{
		mState = EState::eWait;
	}
	else if (mpScene->CameraTarget() == this)
	{

		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);
		
		mState = EState::ePlay;

		// 移動
		Position(Position() + moveSpeed);

		// プレイヤーを移動方向へ向ける
		CVector current = VectorZ();
		CVector target = moveSpeed;
		target.Y(0.0f);
		target.Normalize();
		CVector forward = CVector::Slerp(current, target, 0.4f);
		Rotation(CQuaternion::LookRotation(forward));

		// 左クリックで弾丸発射
		if (CInput::Key(VK_LBUTTON) || CInput::Key(VK_SPACE))
		{
			UpdateAttack();
			
		}
	}

	// キャラクターの更新
	CXCharacter::Update();

	mIsGrounded = false;
}

void CInteractRobot::Render()
{
	CXCharacter::Render();
}

void CInteractRobot::Interact()
{
	if (mIsClear) return;
	mIsHack = !mIsHack;
	mInteractStr = mIsHack ? "オフにする" : "オンにする";
	if (CInput::PushKey('F'))
	{
		mpHackGame->Open();
	}
}

bool CInteractRobot::IsClear() const
{
	if (!mpHackGame->IsClear()) return false;

	return true;
}

// キーの入力情報から移動ベクトルを求める
CVector CInteractRobot::CalcMoveVec() const
{
	CVector move = CVector::zero;

	// キーの入力ベクトルを取得
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Y(-1.0f);
	else if (CInput::Key('S'))	input.Y(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// 入力ベクトルの長さで入力されているか判定
	if (input.LengthSqr() > 0.0f)
	{
		// 上方向ベクトル(設置している場合は、地面の法線)
		CVector up = mIsGrounded ? mGroundNormal : CVector::up;
		// カメラの向きに合わせた移動ベクトルに変換
		CCamera* mainCamera = CCamera::MainCamera();
		CVector camForward = mainCamera->VectorZ();
		camForward.Y(0.0f);
		camForward.Normalize();
		// カメラの正面方向ベクトルと上方向ベクトルの外積から
		// 横方向の移動ベクトルを求める
		CVector moveSide = CVector::Cross(up, camForward);
		// 横方向の移動ベクトルと上方向ベクトルの外積から
		// 正面方向の移動ベクトルを求める
		CVector moveForward = CVector::Cross(moveSide, up);

		// 求めた各方向の移動ベクトルから、
		// 最終的なプレイヤーの移動ベクトルを求める
		move = moveForward * input.Y() + moveSide * input.X();
		move.Normalize();
	}

	return move;
}

// 移動の更新処理
void CInteractRobot::UpdateMove()
{
	if (IsClear())
	{
		mMoveSpeed = CVector::zero;

		// プレイヤーの移動ベクトルを求める
		CVector move = CalcMoveVec();
		// 求めた移動ベクトルの長さで入力されているか判定
		if (move.LengthSqr() > 0.0f)
		{
			mMoveSpeed += move * MOVE_SPEED;

			// 操作状態であれば、歩行アニメーションに切り替え
			if (mState == EState::ePlay)
			{
				ChangeAnimation(EAnimType::eWalk);
			}
		}
		// 移動キーを入力していない
		else
		{
			// 操作状態であれば、待機アニメーションに切り替え
			if (mState == EState::ePlay)
			{
				ChangeAnimation(EAnimType::eIdle);
			}
		}
	}
}


void CInteractRobot::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eField)
		{
			CVector adjust = hit.adjust;
			CVector normal = adjust.Normalized();
			float dot = CVector::Dot(normal, CVector::up);

			// 床（または坂）と判定
			if (dot > 0.7f)
			{
				// 上方向のみの押し戻し（X,Z方向は固定）
				adjust.X(0.0f);
				adjust.Z(0.0f);
				Position(Position() + adjust * hit.weight);

				if (mMoveSpeedY < 0.0f)
				{
					mMoveSpeedY = 0.0f;
				}
				mIsGrounded = true;
				mGroundNormal = normal;
			}
			// 壁と判定された
			else
			{
				// 横方向（X,Z）だけ押し戻す
				adjust.Y(0.0f);
				Position(Position() + adjust * hit.weight);
			}
		}
	}
	if (self == mpColliderSphere)
	{
		if (other->Layer() == ELayer::eEnemy)
		{
			mIsTarget = true;
			mpTargetPos = other->Position();
			mpTarget = other->Owner();
		}
		else
		{
			mIsTarget = false;
			mpTarget = nullptr;
		}
	}
}

void CInteractRobot::ChangeAnimation(EAnimType type)
{
	int index = (int)type;
	if (!(0 <= index && index < (int)EAnimType::Num)) return;
	const AnimData& data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

void CInteractRobot::ChangeState(EState state)
{
	//すでに同じ状態であれば処理しない
	if (state == mState) return;

	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

void CInteractRobot::UpdateIdle()
{
}

void CInteractRobot::UpdateAttack()
{
	ChangeAnimation(EAnimType::eAttack);
	mBulletTime -= Times::DeltaTime();

	if (mBulletTime <= 0)
	{
		CVector shootPos = Position() + CVector(0.0f, 14.0f, 0.0f) + VectorZ() * 20.0f;
		CVector direction;

		if (mpTarget != nullptr)
		{
			CVector targetPos = mpTarget->Position(); // 毎回最新の位置を取得
			direction = targetPos - shootPos;
		}
		else
		{
			direction = VectorZ(); // 前方に発射
		}

		// 弾を生成
		new CBullet(
			shootPos,
			direction,
			100.0f, // 移動距離
			100.0f, // 飛距離
			ELayer::eAttackCol
		);

		mBulletTime = BULLET_TIME;
	}
}

std::string CInteractRobot::GetStateStr(EState state) const
{
	switch (mState)
	{
	case EState::eWait: return "待機";
	case EState::ePlay: return "操作中";
	}
	return std::string();
}

