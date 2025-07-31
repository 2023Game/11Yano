//プレイヤークラスのインクルード
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CBullet.h"
#include "CFlamethrower.h"
#include "CSlash.h"
#include "Maths.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CColliderSphere.h"
#include "CInteractObject.h"
#include "CSceneBase.h"
#include "CTaskManager.h"
#include "CSceneManager.h"
#include "CFieldBase.h"
// プレイヤーのインスタンス
CPlayer* CPlayer::spInstance = nullptr;

// プレイヤーのアニメーションデータのテーブル
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// Tポーズ
	{ "Character\\Mryotaisu\\anim\\idle.x",		true,	500.0f	},	// 待機
	{ "Character\\Mryotaisu\\anim\\walk.x",		true,	62.0f	},	// 歩行
	{ "Character\\Mryotaisu\\anim\\run.x",		true,	44.0f	},	// 走る
	{ "Character\\Mryotaisu\\anim\\damage.x",    false,	71.0f	},	// ダメージ
	{ "Character\\Mryotaisu\\anim\\die.x",	   	false,	221.0f	},	// 死
	//{ "Character\\Player\\anim\\jump_end.x",	false,	26.0f	},	// ジャンプ終了
};

#define PLAYER_HEIGHT	 12.0f
#define PLAYER_WIDTH	  5.0f
#define MOVE_SPEED		  0.375f
#define MOVE_SPEED2		  0.775f
#define GRAVITY			  0.0625f



// コンストラクタ
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mMoveSpeedY(0.0f)
	, mIsDash(false)
	, mpCollider(nullptr)
	, mIsGrounded(false)
	, mSetImage(0)
	, mIsInteract(false)
	, mIsDie(false)
{
	//インスタンスの設定
	spInstance = this;

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Player");

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
		this, ELayer::ePlayer,
		CVector(0.0f, 2.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f),
		2.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eField, ELayer::eBullet, ELayer::eEnemy });

	mpCollider = new CColliderSphere
	(
		this, ELayer::eInteractSearch,
		20.0f
	);
	mpCollider->SetCollisionTags({ ETag::eInteractObject });
	mpCollider->SetCollisionLayers({ ELayer::eInteractObj, ELayer::eNextStage, ELayer::eGoal, ELayer::ePlayRobot });


	// 経路探索用ノードを作成
	mpNavNode = new CNavNode(Position(), true);
	mpNavNode->SetColor(CColor::red);

	mpSE = CResourceManager::Get<CSound>("Die");

}

CPlayer::~CPlayer()
{
	SAFE_DELETE(mpColliderCapsule);
	SAFE_DELETE(mpCollider);

	if (mpNavNode != nullptr)
	{
		mpNavNode = nullptr;
	}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// アニメーション切り替え
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

CInteractObject* CPlayer::GetNearInteractObj() const
{
	CInteractObject* nearObj = nullptr;
	float nearDist = 0.0f;
	CVector pos = Position();
	for (CInteractObject* obj : mNearInteractObjs)
	{
		if (!obj->CanInteract()) continue;
		float dist = (obj->Position() - pos).LengthSqr();
		if (nearObj == nullptr || dist < nearDist)
		{
			nearObj = obj;
			nearDist = dist;
		}
	}
	return nearObj;
}

// 待機
void CPlayer::UpdateIdle()
{
	// 接地していれば
	if (mIsGrounded)
	{
		CInteractObject* obj = GetNearInteractObj();
		if (obj != nullptr)
		{
			if (CInput::PushKey('F'))
			{
				obj->Interact();
			}
		}
	}
}

void CPlayer::UpdateDamage()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

void CPlayer::UpdateDie()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	if (IsAnimationFinished())
	{
		CSceneManager::Instance()->LoadScene(EScene::eGameOver);
	}
}


// キーの入力情報から移動ベクトルを求める
CVector CPlayer::CalcMoveVec() const
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
void CPlayer::UpdateMove()
{
	mMoveSpeed = CVector::zero;

	// プレイヤーの移動ベクトルを求める
	CVector move = CalcMoveVec();
	// 求めた移動ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		if (mIsDash == true)
		{
			if (mState != EState::eDamage)
			{
				ChangeAnimation(EAnimType::eRun);
			}
			mMoveSpeed += move * MOVE_SPEED2;
		}
		else
		{
			if (mState != EState::eDamage)
			{
				ChangeAnimation(EAnimType::eWalk);
			}
			mMoveSpeed += move * MOVE_SPEED;
		}


		// 待機状態であれば、歩行アニメーションに切り替え
		if (mState == EState::eIdle)
		{

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

// 更新
void CPlayer::Update()
{

	if (mpScene->CameraTarget() == this)
	{
		// 状態に合わせて、更新処理を切り替える
		switch (mState)
		{
			// 待機状態
		case EState::eIdle:
			UpdateIdle();
			break;
		case EState::eDamage:
			UpdateDamage();
			break;
		case EState::eDie:
			UpdateDie();
			break;
		}

		// 待機中とダメージ中は、移動処理を行う
		if (mState == EState::eIdle || mState == EState::eDamage)
		{
			UpdateMove();
		}

		mMoveSpeedY -= GRAVITY;
		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);

		// 移動
		Position(Position() + moveSpeed);

		// プレイヤーを移動方向へ向ける
		CVector current = VectorZ();
		CVector target = moveSpeed;
		target.Y(0.0f);
		target.Normalize();
		CVector forward = CVector::Slerp(current, target, 0.4f);
		Rotation(CQuaternion::LookRotation(forward));

		if (CInput::Key(VK_SHIFT) || CInput::Key(VK_LBUTTON))
		{
			mIsDash = true;
		}
		else
		{
			mIsDash = false;
		}
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);
		mState = EState::eIdle;
	}
	// 「P」キーを押したら、ゲームを終了
	if (CInput::PushKey('P'))
	{
		System::ExitGame();
	}

	// キャラクターの更新
	CXCharacter::Update();


	mIsGrounded = false;

	//CDebugPrint::Print("HP:%i\n", mHp);

	//CDebugPrint::Print("FPS:%f\n", Times::FPS());

	mNearInteractObjs.clear();

	PostCollisionUpdate();
}

// 衝突処理
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	mCurrentColliders.push_back(other);
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eField || other->Layer() == ELayer::eEnemy)
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
		if (other->Layer() == ELayer::eBullet)
		{
			mpSE->Play(0.3f, true);
			mIsDie = true;
			// 死亡処理
			mState = EState::eDie;
			ChangeAnimation(EAnimType::eDie);
		}
	}
	if (self == mpCollider)
	{
		CInteractObject* obj = dynamic_cast<CInteractObject*>(other->Owner());
		if (obj != nullptr)
		{
			mNearInteractObjs.push_back(obj);
#if _DEBUG
			CDebugPrint::Print("%s:%s\n",
				obj->GetDebugName().c_str(),
				obj->GetInteractStr().c_str());
#endif
		}

		if (other->Layer() == ELayer::eNextStage)
		{
			mIsInteract = true;
			mSetImage = 1;
		}
		if (other->Layer() == ELayer::eGoal)
		{
			mIsInteract = true;
			mSetImage = 2;
		}
		if (other->Layer() == ELayer::eInteractObj)
		{
			mIsInteract = true;
			mSetImage = 3;
		}
		if (other->Layer() == ELayer::ePlayRobot)
		{
			mIsInteract = false;
			mSetImage = 0;
		}

	}

}

void CPlayer::PostCollisionUpdate()
{
	// 前フレームにあったが、今フレームにない　= 衝突終了
	for (auto* prev : mColliders)
	{
		bool found = false;
		for (auto* curr : mCurrentColliders)
		{
			if (curr == prev)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			OnCollisionExit(prev);
		}
	}

	// 現在の衝突状態を次フレームにコピー
	mColliders = mCurrentColliders;
	mCurrentColliders.clear();
}

void CPlayer::OnCollisionExit(CCollider* col)
{
	if (col->Layer() == ELayer::eInteractObj || col->Layer() == ELayer::eNextStage || col->Layer() == ELayer::eGoal)
	{
		mIsInteract = false;
		mSetImage = 0;
	}
}

int CPlayer::SetImage() const
{
	return mSetImage;
}


// 描画
void CPlayer::Render()
{
	CXCharacter::Render();
}

bool CPlayer::IsInteract() const
{
	return mIsInteract;
}

bool CPlayer::IsDie() const
{
	return mIsDie;
}

