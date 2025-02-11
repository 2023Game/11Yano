#include "CDoor.h"
#include "CIntercom.h"

CDoor::CDoor(const CVector& pos, const CVector& angle, const CVector& size)
	: mIsOpened(false)
	, mAnimTime(1.0f)
	, mElapsedTime(0.0f)
	, mIsPlaying(false)
{
	mpModel = CResourceManager::Get<CModel>("Door");
	// コライダー作成
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// 位置と向きとサイズを設定
	Position(pos);
	Rotation(angle);
	Scale(size);
}

CDoor::~CDoor()
{
	// コライダー削除
	SAFE_DELETE(mpColliderMesh);
}

void CDoor::AddIntercom(CIntercom* intercom)
{
	mpIntercoms.push_back(intercom);
}

void CDoor::SetAnimPos(const CVector& openPos, const CVector& closePos)
{
	mOpenPos = openPos;
	mClosePos = closePos;
	Position(mIsOpened ? mOpenPos : mClosePos);
}

void CDoor::Update()
{
	if (mIsPlaying)
	{
		if (mIsOpened)
		{
			if (mElapsedTime < mAnimTime)
			{
				float per = mElapsedTime / mAnimTime;
				CVector pos = CVector::Lerp(mClosePos, mOpenPos, per);
				Position(pos);
				mElapsedTime += Times::DeltaTime();
			}
			else
			{
				Position(mOpenPos);
				mElapsedTime = 0.0f;
				mIsPlaying = false;
			}
		}
		else 
		{
			if (mElapsedTime < mAnimTime)
			{
				float per = mElapsedTime / mAnimTime;
				CVector pos = CVector::Lerp(mOpenPos, mClosePos, per);
				Position(pos);
				mElapsedTime += Times::DeltaTime();
			}
			else
			{
				Position(mClosePos);
				mElapsedTime = 0.0f;
				mIsPlaying = false;
			}
		}
	}
	else
	{
		if (IsOpen() && !mIsOpened)
		{
			mIsOpened = true;
			mIsPlaying = true;
		}
		else if (!IsOpen() && mIsOpened)
		{
			mIsOpened = false;
			mIsPlaying = true;
		}
	}
}

void CDoor::Render()
{
	mpModel->Render();
}

bool CDoor::IsOpen() const
{
	for (CIntercom* intercom : mpIntercoms)
	{
		if (!intercom->IsClear()) return false;
	}
	return true;
}
