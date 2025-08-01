#include "CBullet.h"
#include "CTrailEffect.h"
#include "Primitive.h"

// コンストラクタ
CBullet::CBullet(const CVector& pos, const CVector& dir,
	float speed, float distance, ELayer layer)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
{
	Position(pos);
	mMoveDir = dir.Normalized();
	Rotation(CQuaternion::LookRotation(mMoveDir, CVector::up));

	mpColliderLine = new CColliderLine
	(
		this, layer,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 5.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eEnemy, ELayer::ePlayer });

	// 軌跡のエフェクトを作成
	mpTrailEffect = new CTrailEffect
	(
		ETag::eBullet,	// オブジェクトタグ
		this,
		nullptr,
		CVector(0.0f, 0.0f, 0.0f),
		0.01f,			// 更新間隔（時間）
		10.0f,			// 更新間隔（距離）
		2.0f,			// 開始時の軌跡の幅
		0.0f,			// 終了時の軌跡の幅
		0.0625f			// 表示時間
	);
	mpTrailEffect->SetTexture("Laser");
	mpTrailEffect->SetColor(CColor(1.0f, 0.75f, 0.25f, 1.0f));

	mpSE = CResourceManager::Get<CSound>("Shot");
	mpSE->Play(0.3f, true);
}

// デストラクタ
CBullet::~CBullet()
{
	mpTrailEffect->SetOwner(nullptr);
	SAFE_DELETE(mpColliderLine);
}

void CBullet::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderLine)
	{
		
		if (other->Layer() == ELayer::ePlayer)
		{
			Kill();
			return;
		}
	}
}

// 更新
void CBullet::Update()
{
	if (IsKill()) return;

	// 残り飛距離が0ならば、弾丸削除
	float remain = mFlyingDistance - mCurrentFlyingDistance;
	if (remain <= 0.0f)
	{
		Kill();
		return;
	}

	// 移動速度を計算
	// 移動速度が残りの飛距離より大きい場合は、
	// 残りの飛距離を移動速度とする
	float moveSpeed = mMoveSpeed * Times::DeltaTime();
	if (abs(moveSpeed) > remain)
	{
		moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
	}

	// 弾丸を正面方向に移動
	Position(Position() + mMoveDir * moveSpeed);
	// 現在の飛距離を更新
	mCurrentFlyingDistance += abs(moveSpeed);
}

// 描画
void CBullet::Render()
{
	Primitive::DrawSphere(Matrix(), 0.1f, mColor);
}
