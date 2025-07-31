#include "CBlackOut.h"
#include "CInput.h"
#include "CHackGame2.h"
#include "CGameScene.h"

#define BLACK_TIME 12.0f	// 停電時間

CBlackOut* CBlackOut::spInstance = nullptr;

CBlackOut* CBlackOut::Instance()
{
	return spInstance;
}

CBlackOut::CBlackOut(const CVector& pos, const CVector& angle, const CVector& size)
	: mpHackGame(nullptr)
	, mIsHack(false)
	, mIsClear(false)
	, mIsBlack(false)
	, mIsBlacked(false)
	, mTime(BLACK_TIME)
{
	spInstance = this;

	mpModel = CResourceManager::Get<CModel>("Intercom");

	mpColliderLine = new CColliderLine
	(
		this, ELayer::eInteractObj,
		CVector(0.0f, -3.0f, 0.0f),
		CVector(0.0f, 3.0f, 0.0f), true
	);
	mpColliderLine->SetCollisionLayers({ ELayer::ePlayer, ELayer::eInteractSearch });

	// 位置と向きとサイズを設定
	Position(pos);
	Rotation(angle);
	Scale(size);

	mpHackGame = new CHackGame2();
	mInteractStr = "オンにする";

	mpSE = CResourceManager::Get<CSound>("Boot");
}

CBlackOut::~CBlackOut()
{
	if (spInstance != nullptr)
	{
		spInstance = nullptr;
	}
	SAFE_DELETE(mpColliderLine);
}

void CBlackOut::Interact()
{
	mIsHack = !mIsHack;
	mInteractStr = mIsHack ? "オフにする" : "オンにする";
	if (CInput::PushKey('F'))
	{
		mpHackGame->Open();
	}
}

void CBlackOut::Update()
{
	if (mpHackGame->IsClear() && !mIsBlacked)
	{
		mpColliderLine->SetCollisionLayers({ ELayer::eNone });
		mIsClear = true;
		mIsBlack = true;
	}

	if (mIsBlack == true)
	{
		mTime -= Times::DeltaTime();
		if (mTime <= 0)
		{
			mIsBlacked = true;
			mIsBlack = false;
		}
	}
}

void CBlackOut::Render()
{
	mpModel->Render(Matrix());
}

bool CBlackOut::IsClear() const
{
	return mIsClear;
}

bool CBlackOut::IsBlack() const
{
	return mIsBlack;
}

void CBlackOut::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}
