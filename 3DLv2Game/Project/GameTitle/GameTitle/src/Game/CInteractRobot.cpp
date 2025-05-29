#include "CInteractRobot.h"
#include "CInput.h"
#include "CDebugFieldOfView.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Primitive.h"
#include "CField.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CHackGame.h"
#include "CBullet.h"

#define ROBOT_HEIGHT 16.0f
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


// プレイヤーのアニメーションデータのテーブル
const CInteractRobot::AnimData CInteractRobot::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// Tポーズ
	{ "Character\\Robot\\anim\\idle.x",		true,	460.0f	},	// 待機
	{ "Character\\Robot\\anim\\walk.x",		true,	78.0f	},	// 歩行
	{ "Character\\Robot\\anim\\run.x",		true,	44.0f	},	// 走行
	{ "Character\\Robot\\anim\\attack.x",		true,	186.0f	},	// 攻撃
	{ "Character\\Robot\\anim\\down.x",		false,	59.0f	},	// 倒れる
	{ "Character\\Robot\\anim\\sit.x",		false,	0.0f	},	// 座る

};

// コンストラクタ
CInteractRobot::CInteractRobot()
	: mState(EState::eIdle)
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

	mpColliderLine = new CColliderLine
	(
		this, ELayer::eInteractObj,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ROBOT_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eInteractSearch });

	float width = ROBOT_WIDTH * 0.5f;
	float posY = ROBOT_HEIGHT * 0.5f;
	mpColliderLineX = new CColliderLine
	(
		this, ELayer::eField,
		CVector(-width, posY, 0.0f),
		CVector(width, posY, 0.0f)
	);
	mpColliderLineX->SetCollisionLayers({ ELayer::eField });
	mpColliderLineZ = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, posY, -width),
		CVector(0.0f, posY, width)
	);
	mpColliderLineZ->SetCollisionLayers({ ELayer::eField });

	mpHackGame = new CHackGame();
	mInteractStr = "オンにする";
}

CInteractRobot::~CInteractRobot()
{
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderLineX);
	SAFE_DELETE(mpColliderLineZ);

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

	mMoveSpeedY -= GRAVITY;
	CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);

	// 移動
	Position(Position() + moveSpeed);

	// プレイヤーを移動方向へ向ける
	CVector current = VectorZ();
	CVector target = moveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// 右クリックで弾丸発射
	if (CInput::PushKey(VK_RBUTTON))
	{
		// 弾丸を生成
		new CBullet
		(
			// 発射位置
			Position() + CVector(0.0f, 10.0f, 0.0f) + VectorZ() * 20.0f,
			VectorZ(),	// 発射方向
			1000.0f,	// 移動距離
			1000.0f		// 飛距離
		);
	}

	if (!IsClear())
	{
		//// 現在の状態に合わせて更新処理を切替
		//switch (mState)
		//{
		//
		//case EState::ePatrol: UpdatePatrol(); break;
		//case EState::eChase: UpdateChase(); break;
		//case EState::eLost: UpdateLost(); break;
		//case EState::eAttack: UpdateAttack(); break;
		//}
		mState = EState::eIdle;

		CXCharacter::Update();

		CDebugPrint::Print("状態 : %s\n", GetStateStr(mState).c_str());
	}
	else if (IsClear())
	{
		mIsClear = true;
		mState = EState::eIdle;
	}

	// キャラクターの更新
	CXCharacter::Update();
}

void CInteractRobot::Render()
{
	CXCharacter::Render();
}

void CInteractRobot::Interact()
{
	mIsHack = mIsHack;
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
	mMoveSpeed = CVector::zero;

	// プレイヤーの移動ベクトルを求める
	CVector move = CalcMoveVec();
	// 求めた移動ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		mMoveSpeed += move * MOVE_SPEED;

		// 待機状態であれば、歩行アニメーションに切り替え
		if (mState == EState::eIdle)
		{
			ChangeAnimation(EAnimType::eWalk);
		}
	}
	// 移動キーを入力していない
	else
	{
		// 待機状態であれば、待機アニメーションに切り替え
		if (mState == EState::eIdle)
		{
			ChangeAnimation(EAnimType::eIdle);
		}
	}
}


void CInteractRobot::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			// 坂道で滑らないように、押し戻しベクトルのXとZの値を0にする
			CVector adjust = hit.adjust;
			adjust.X(0.0f);
			adjust.Z(0.0f);

			Position(Position() + adjust * hit.weight);
		}
	}
	else if (self == mpColliderLineX || self == mpColliderLineZ)
	{
		if (other->Layer() == ELayer::eField)
		{
			// 坂道で滑らないように、押し戻しベクトルのXとZの値を0にする
			CVector adjust = hit.adjust;
			adjust.Y(0.0f);

			// 押し戻しベクトルの分座標を移動
			Position(Position() + adjust * hit.weight);
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

std::string CInteractRobot::GetStateStr(EState state) const
{
	switch (mState)
	{
	case EState::eIdle: return "待機";
	case EState::ePatrol: return "巡回";
	case EState::eChase: return "追跡";
	case EState::eLost: return "見失う";
	case EState::eAttack: return "攻撃";
	}
	return std::string();
}

