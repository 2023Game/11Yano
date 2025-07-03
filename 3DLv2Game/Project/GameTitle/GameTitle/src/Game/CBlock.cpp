#include "CBlock.h"

#define TEXCOORD 0.0f,48.0f,128.0f,80.0f


CBlock::CBlock(float x, float y)
	: CCharaBase(ETag::eField, ETaskPriority::eUI)
{
	mpImage = new CImage
	(
		"UI/2D_idle.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);

	mpImage->SetSize(CVector2(20.0f, 20.0f));
	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(CVector2(x, y));
	mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}
