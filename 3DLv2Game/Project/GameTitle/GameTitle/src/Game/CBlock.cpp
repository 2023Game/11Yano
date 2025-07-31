#include "CBlock.h"

#define TEXCOORD 0.0f,48.0f,128.0f,80.0f


CBlock::CBlock(float x, float y)
	: CCharaBase(ETag::eField, ETaskPriority::eUI)
{
	mpImage = new CImage
	(
		"UI/Tile.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);

	mpImage->SetSize(CVector2(50.0f, 50.0f));
	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(CVector2(x, y));
	mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mpCollider = new CColliderTriangle2D(
		this, ELayer::eField,
		CVector2(25.0f, 25.0f),
		CVector2(25.0f, -25.0f),
		CVector2(-25.0f, -25.0f)
	);
	mpCollider->SetCollisionTags({ ETag::ePlayer2D });
	mpCollider2 = new CColliderTriangle2D(
		this, ELayer::eField,
		CVector2(25.0f, -25.0f),
		CVector2(-25.0f, 25.0f),
		CVector2(-25.0f, 25.0f)
	);
	mpCollider2->SetCollisionTags({ ETag::ePlayer2D });
}

void CBlock::Render()
{
	mpImage->Render();
}
