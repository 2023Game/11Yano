#include "CDoor.h"
#include "CIntercom.h"

CDoor::CDoor(const CVector& pos, const CVector& angle, const CVector& size)
	: mIsOpened(false)
	, mAnimTime(1.0f)
	, mElapsedTime(0.0f)
	, mIsPlaying(false)
{
	mpModel = CResourceManager::Get<CModel>("Door");
	// �R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eEnemy });

	// �ʒu�ƌ����ƃT�C�Y��ݒ�
	Position(pos);
	Rotation(angle);
	Scale(size);
}

CDoor::~CDoor()
{
	// �R���C�_�[�폜
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
	if (!mIsPlaying && IsOpen() == mIsOpened) return; // ��ԕω����Ȃ��Ȃ珈���X�L�b�v

	if (mIsPlaying)
	{
		if (mIsOpened)
		{
			// �h�A���J���A�j���[�V����
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
			// �h�A�����A�j���[�V����
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
	// �ǂ̃R���C�_�����݂��Ȃ���ΏՓ˂��Ă��Ȃ�
	if (mpColliderMesh == nullptr)return false;
	return CCollider::CollisionRay(mpColliderMesh, start, end, hit);
}