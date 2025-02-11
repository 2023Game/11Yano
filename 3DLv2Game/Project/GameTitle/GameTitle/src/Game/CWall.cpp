#include "CWall.h"

CWall::CWall(const CVector& pos, const CVector& angle, const CVector& size)
{
	mpModel = CResourceManager::Get<CModel>("Wall");
	// コライダー作成
	CModel* colModel = CResourceManager::Get<CModel>("WallCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, colModel, true);

	// 位置と向きとサイズを設定
	Position(pos);
	Rotation(angle);
	Scale(size);
}

CWall::~CWall()
{
	// コライダー削除
	SAFE_DELETE(mpColliderMesh);
}

bool CWall::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	// 壁のコライダが存在しなければ衝突していない
	if (mpColliderMesh == nullptr)return false;
	return CCollider::CollisionRay(mpColliderMesh, start, end, hit);
}

void CWall::Update()
{
}

void CWall::Render()
{
	mpModel->Render(Matrix());
}
