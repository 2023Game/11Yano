#include "CSwitch.h"
#include "CInput.h"
#include "CHackGame2.h"
#include "CGameScene.h"

CSwitch::CSwitch(const CVector& pos, const CVector& angle, const CVector& size)
	: mpHackGame(nullptr)
	, mIsHack(false)
	, mIsClear(false)
	, mIsPlayed(false)
{
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

CSwitch::~CSwitch()
{
	SAFE_DELETE(mpColliderLine);
}

void CSwitch::Interact()
{
	mIsHack = !mIsHack;
	mInteractStr = mIsHack ? "オフにする" : "オンにする";
	if (CInput::PushKey('F'))
	{
		mpHackGame->Open();
	}
}

void CSwitch::Update()
{
	if (mpHackGame->IsClear())
	{
		mIsClear = true;
		KillObj();
		mpColliderLine->SetCollisionLayers({ ELayer::eNone });

	}
}

void CSwitch::Render()
{
	mpModel->Render(Matrix());
}

bool CSwitch::IsClear() const
{
	return mIsClear;
}

void CSwitch::KillObj()
{
	if (!mIsPlayed)
	{
		mpSE->Play(0.3f, true);
		mIsPlayed = true;
	}
	
	CGameScene* scene = CGameScene::Instance();
	std::list<CDrone*> drones = scene->GetDrones();
	for (CDrone* drone : drones)
	{
		drone->Stop();
	}
}

void CSwitch::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}
