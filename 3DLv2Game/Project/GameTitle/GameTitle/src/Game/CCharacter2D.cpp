#include "CCharacter2D.h"

bool CCharacter2D::Enabled()
{
	return mEnabled;
}

CCharacter2D::ETag CCharacter2D::Tag()
{
	return mTag;
}

void CCharacter2D::Texture(CTexture* texture,
	int left, int right, int bottom, int top)
{
	mpTexture = texture;
	mLeft = left;
	mRight = right;
	mBottom = bottom;
	mTop = top;
}

void CCharacter2D::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop
	);
}

void CCharacter2D::Move()
{
	mState = EState::eMove;
}

CCharacter2D::EState CCharacter2D::State()
{
	return mState;
}

CCharacter2D::CCharacter2D()
	:mpTexture(nullptr)
	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)
	, mState(EState::eMove)
	, mTag(ETag::eZero)
	, mEnabled(true)
	, mVy(0.0f)
	, mVx(0.0f)
{
}

CTexture* CCharacter2D::Texture()
{
	return mpTexture;
}
