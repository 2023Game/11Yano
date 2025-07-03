#include "CGoal.h"
#include "CInput.h"
#include "CSceneManager.h"

CGoal::CGoal(const CVector& pos, const CVector& angle, const CVector& size, ELayer layer)
	:mIsAction(false)
{
	mpModel = CResourceManager::Get<CModel>("Goal");

	mpColliderLine = new CColliderLine
	(
		this, layer,
		CVector(0.0f, 10.0f, 20.0f),
		CVector(0.0f, 10.0f, -20.0f), true
	);
	mpColliderLine->SetCollisionLayers({ ELayer::ePlayer, ELayer::eInteractSearch });

	// 位置と向きとサイズを設定
	Position(pos);
	Rotation(angle);
	Scale(size);

	mpLayer = layer;
}

CGoal::~CGoal()
{
	SAFE_DELETE(mpColliderLine);
}

void CGoal::Interact()
{
	mIsAction = !mIsAction;
	mInteractStr = mIsAction ? "オフにする" : "オンにする";
	if (mpLayer==ELayer::eNextStage && CInput::PushKey('F'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame2);
	}
	else if (mpLayer == ELayer::eGoal && CInput::PushKey('F'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eClear);
	}
}

void CGoal::Update()
{
}

void CGoal::Render()
{
	mpModel->Render(Matrix());
}

void CGoal::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

