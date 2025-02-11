#include "CIntercom.h"
#include "CInput.h"
#include "CHackGame.h"

CIntercom::CIntercom(const CVector& pos, const CVector& angle, const CVector& size)
	: mpHackGame(nullptr)
	, mIsHack(false)
	, mIsClear(false)
{
	mpModel = CResourceManager::Get<CModel>("Intercom");

	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eInteractObj,
		5.0f, true
	);
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer });
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer, ELayer::eInteractSearch });

	// �ʒu�ƌ����ƃT�C�Y��ݒ�
	Position(pos);
	Rotation(angle);
	Scale(size);

	mpHackGame = new CHackGame();
	mInteractStr = "�I���ɂ���";
}

CIntercom::~CIntercom()
{
}

void CIntercom::Interact()
{

	mIsHack = mIsHack;
	mInteractStr = mIsHack ? "�I�t�ɂ���" : "�I���ɂ���";
	if (CInput::PushKey('F'))
	{
		mpHackGame->Open();
	}
}

void CIntercom::Update()
{
	if (mpHackGame->mIsClear == true)
	{
		mIsClear = true;

	}
}

void CIntercom::Render()
{
	mpModel->Render(Matrix());
}

bool CIntercom::IsClear() const
{
	return mIsClear;
}

void CIntercom::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}
