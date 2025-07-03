#include "CEnemy2D.h"
#include "CPlayer2D.h"
#include "CBullet2D.h"

#define WALK_SPEED 100.0f
#define BULLET_TIME 3.0f

CEnemy2D::CEnemy2D(const CVector2& pos, float bulletTime)
	: CObjectBase(ETag::eEnemy2D, ETaskPriority::eUI)
	, mTime(bulletTime)
{
	Position2D(pos);
	mpImage = new CImage
	(
		"UI/enemy2D.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpImage->SetSize(CVector2(90.0f, 130.0f));
	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(pos);
	mpImage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpCollider = new CColliderCircle2D(
		this, ELayer::e2D,
		40.0f
	);
	mpCollider->SetCollisionTags({ ETag::eBullet2D });
}
CEnemy2D::~CEnemy2D()
{
	SAFE_DELETE(mpCollider);
}
void CEnemy2D::Update()
{
	if (IsKill()) return;
	mTime -= Times::DeltaTime();
	CPlayer2D* player = CPlayer2D::Instance();
	// プレイヤー座標取得
	CVector2 playerPos = player->Position2D();
	// 自分自身の座標を取得
	CVector pos = Position2D();
	// 自身からプレイヤーまでのベクトルを求める
	CVector2 vec = playerPos - pos;
	if (mTime <= 0)
	{
		// 弾丸を生成
		new CBullet2D
		(
			this,
			// 発射位置
			Position2D() + CVector2(-50.0f, 0.0f),
			vec,	// 発射方向
			400.0f,	// 移動距離
			800.0f,	// 飛距離
			ETag::eEnemy2D
		);
		mTime = BULLET_TIME;
	}
}

void CEnemy2D::Render()
{
	mpImage->Render();
}

void CEnemy2D::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpCollider)
	{
		if (other->Tag() == ETag::eBullet2D)
		{
			Kill();
			return;
		}
	}
}
