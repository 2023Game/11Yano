#include "CBullet2D.h"
#include "Primitive.h"

CBullet2D::CBullet2D(CObjectBase* owner, const CVector2& pos, const CVector2& dir, float speed, float distance, ETag tag)
    : CObjectBase(tag, ETaskPriority::eUI)
    , mMoveSpeed(speed)
    , mFlyingDistance(distance)
    , mCurrentFlyingDistance(0.0f)
    , mpOwner(nullptr)
{
    Position2D(pos);
    mMoveDir = dir.Normalized();

    mpImage = new CImage
    (
        "UI/bullet2D.png",
        ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
        false, false
    );
    mpImage->SetSize(CVector2(50.0f, 30.0f));
    mpImage->SetCenter(mpImage->GetSize() * 0.5f);
    mpImage->SetPos(pos);
    mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
   
    mpCollider = new CColliderCircle2D(
        this, ELayer::e2D,
        20.0f
    );
    mpCollider->SetCollisionTags({ ETag::ePlayer2D, ETag::eEnemy2D });

    mpOwner = owner;

    mpSE = CResourceManager::Get<CSound>("Shot");
    mpSE->Play(0.3f, true);
}

CBullet2D::~CBullet2D()
{
    SAFE_DELETE(mpCollider);
}

void CBullet2D::Update()
{
    if (IsKill()) return;

    float remain = mFlyingDistance - mCurrentFlyingDistance;
    if (remain <= 0.0f)
    {
        CTask::Kill();
        return;
    }

    float moveSpeed = mMoveSpeed * Times::DeltaTime();
    if (abs(moveSpeed) > remain)
    {
        moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
    }

    Position2D(Position2D() + mMoveDir * moveSpeed);
    mpImage->SetPos(Position2D());
    mCurrentFlyingDistance += abs(moveSpeed);

    if (mpOwner->IsKill())
    {
        CTask::Kill();
        mpOwner = nullptr;
        return;
    }
}

void CBullet2D::Render()
{
    mpImage->Render();
}

void CBullet2D::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
    if (self == mpCollider)
    {
        if (other->Tag() == ETag::ePlayer2D)
        {
            CTask::Kill();
            return;
        }
    }
}
