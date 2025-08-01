#include "CPlayer2D.h"
#include "CInput.h"
#include "CBullet2D.h"
#include <algorithm>

#define ATTACK_TIME 1.0f
#define MOVE_SPEED 8.0f

// プレイヤーのインスタンス
CPlayer2D* CPlayer2D::spInstance = nullptr;

CPlayer2D::CPlayer2D(const CVector2& pos)
	: CObjectBase(ETag::ePlayer2D, ETaskPriority::eUI)
	, mState(EState::eIdle)
	, mTime(0.0f)
	, mPosition(pos)
	, mHp(3)
	, mKilled(false)
{
	//インスタンスの設定
	spInstance = this;
	Position2D(pos);
	mpImage = new CImage
	(
		"UI/jet2D.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);

	mpImage->SetSize(CVector2(100.0f, 120.0f));
	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(pos);
	mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpHp1 = new CImage
	(
		"UI/heart.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpHp1->SetSize(CVector2(50.0f, 50.0f));
	mpHp1->SetCenter(mpHp1->GetSize() * 0.5f);
	mpHp1->SetPos(CVector2(200.0f, 600.0f));
	mpHp1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpHp2 = new CImage
	(
		"UI/heart.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpHp2->SetSize(CVector2(50.0f, 50.0f));
	mpHp2->SetCenter(mpHp2->GetSize() * 0.5f);
	mpHp2->SetPos(CVector2(300.0f, 600.0f));
	mpHp2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpHp3 = new CImage
	(
		"UI/heart.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpHp3->SetSize(CVector2(50.0f, 50.0f));
	mpHp3->SetCenter(mpHp3->GetSize() * 0.5f);
	mpHp3->SetPos(CVector2(400.0f, 600.0f));
	mpHp3->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpCollider = new CColliderCircle2D(
		this, ELayer::ePlayer,
		30.0f
	);
	mpCollider->SetCollisionTags({ ETag::eEnemy2D });

	mpSE = CResourceManager::Get<CSound>("Damage");
}

CPlayer2D::~CPlayer2D()
{
	SAFE_DELETE(mpCollider);
}

void CPlayer2D::Update()
{
	
	if (IsKill()) return;

	switch (mState)
	{
	case EState::eIdle: UpdateIdle(); break;
	case EState::eAttack: UpdateAttack(); break;
	case EState::eDamage: UpdateDamage(); break;
	}

	if (CInput::Key('W') && mPosition.Y() >= 200.0f)
	{
		mPosition = Position2D() + CVector2(0.0f, -MOVE_SPEED);
	}
	if (CInput::Key('S') && mPosition.Y() <= 550.0f)
	{
		mPosition = Position2D() + CVector2(0.0f, MOVE_SPEED);
	}
	if (CInput::Key('D') && mPosition.X() <= 600.0f)
	{
		mPosition = Position2D() + CVector2(MOVE_SPEED, 0.0f);
	}
	if (CInput::Key('A') && mPosition.X() >= 230.0f)
	{
		mPosition = Position2D() + CVector2(-MOVE_SPEED, 0.0f);
	}

	// 位置反映
	Position2D(mPosition);
	mpImage->SetPos(mPosition);

	if (CInput::Key(VK_SPACE))
	{
		UpdateAttack();
	}
	if (CInput::PullKey(VK_SPACE))
	{
		mTime = 0.0f;
	}
}

void CPlayer2D::Render()
{
	
	if (mHp >= 1) mpHp1->Render();
	if (mHp >= 2) mpHp2->Render();
	if (mHp >= 3) mpHp3->Render();
	mpImage->Render();
}

void CPlayer2D::UpdateIdle()
{
	
}

void CPlayer2D::UpdateAttack()
{
	
	mTime -= Times::DeltaTime();
	if (mTime <= 0)
	{
		// 弾丸を生成
		new CBullet2D
		(
			this,
			// 発射位置
			Position2D() + CVector2(70.0f, 0.0f),
			CVector2(1.0f, 0.0f),	// 発射方向
			400.0f,	// 移動距離
			800.0f,	// 飛距離
			ETag::eBullet2D
		);
		mTime = ATTACK_TIME;
	}
}

void CPlayer2D::UpdateDamage()
{

}

bool CPlayer2D::IsAttack() const
{
	if (mState != EState::eAttack) return false;

	return true;
}

void CPlayer2D::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpCollider)
	{
		if (other->Tag() == ETag::eEnemy2D)
		{
			mpSE->Play(0.3f, true);
			mHp--;
			if (mHp <= 0)
			{
				mKilled = true;
				CTask::Kill();
				return;
			}
		}
	}
}

bool CPlayer2D::Killed() const
{
	return mKilled;
}

CPlayer2D* CPlayer2D::Instance()
{
	return spInstance;
}