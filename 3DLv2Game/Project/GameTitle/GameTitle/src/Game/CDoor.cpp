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
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eEnemy });

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
	mpIntercom = intercom;
}

void CDoor::SetAnimPos(const CVector& openPos, const CVector& closePos)
{
	mOpenPos = openPos;
	mClosePos = closePos;
	Position(mIsOpened ? mOpenPos : mClosePos);
}

void CDoor::Update()
{
	if (!mIsPlaying && IsOpen() == mIsOpened) return; // 状態変化しないなら処理スキップ

	if (mIsPlaying)
	{
		if (mIsOpened)
		{
			// ドアを開くアニメーション
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
			// ドアを閉じるアニメーション
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
	mpModel->Render(Matrix());
}

CCollider* CDoor::GetFieldCol() const
{
	return mpColliderMesh;
}

bool CDoor::IsOpen() const
{
	if (!mpIntercom->IsClear()) return false;
	
	return true;
}

bool CDoor::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	// 壁のコライダが存在しなければ衝突していない
	if (mpColliderMesh == nullptr)return false;
	return CCollider::CollisionRay(mpColliderMesh, start, end, hit);
}