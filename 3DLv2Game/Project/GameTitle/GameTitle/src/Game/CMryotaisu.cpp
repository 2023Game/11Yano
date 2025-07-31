#include "CMryotaisu.h"
#include "CInput.h"
#include "CBullet2D.h"
#include <algorithm>

#define MOVE_SPEED 8.0f

CMryotaisu::CMryotaisu(const CVector2& pos)
	: CObjectBase(ETag::ePlayer2D, ETaskPriority::eUI)
	, mPosition(pos)
{
	//インスタンスの設定
	Position2D(pos);
	mpImage = new CImage
	(
		"UI/2D_idle.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);

	mpImage->SetSize(CVector2(100.0f, 120.0f));
	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(pos);
	mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpCollider = new CColliderCircle2D(
		this, ELayer::ePlayer,
		30.0f
	);
	mpCollider->SetCollisionTags({ ETag::eClear, ETag::eField });

	mpSE = CResourceManager::Get<CSound>("Damage");
}

CMryotaisu::~CMryotaisu()
{
	SAFE_DELETE(mpCollider);
}

void CMryotaisu::Update()
{

	if (CInput::Key('W')/* && mPosition.Y() >= 200.0f*/)
	{
		mPosition = Position2D() + CVector2(0.0f, -MOVE_SPEED);
	}
	if (CInput::Key('S')/* && mPosition.Y() <= 550.0f*/)
	{
		mPosition = Position2D() + CVector2(0.0f, MOVE_SPEED);
	}
	if (CInput::Key('D')/* && mPosition.X() <= 600.0f*/)
	{
		mPosition = Position2D() + CVector2(MOVE_SPEED, 0.0f);
	}
	if (CInput::Key('A')/* && mPosition.X() >= 230.0f*/)
	{
		mPosition = Position2D() + CVector2(-MOVE_SPEED, 0.0f);
	}

	// 位置反映
	Position2D(mPosition);
	mpImage->SetPos(mPosition);
}

void CMryotaisu::Render()
{
	mpImage->Render();
}

void CMryotaisu::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpCollider)
	{
		if (other->Tag() == ETag::eField)
		{
			Position2D(Position2D() + hit.adjust);
		}
	}
}