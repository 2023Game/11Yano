#include "CWall.h"

CWall::CWall(const CVector& pos, const CVector& angle, const CVector& size)
{
	mpModel = CResourceManager::Get<CModel>("Wall");
	// �R���C�_�[�쐬
	CModel* colModel = CResourceManager::Get<CModel>("WallCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, colModel, true);

	// �ʒu�ƌ����ƃT�C�Y��ݒ�
	Position(pos);
	Rotation(angle);
	Scale(size);
}

CWall::~CWall()
{
	// �R���C�_�[�폜
	SAFE_DELETE(mpColliderMesh);
}

bool CWall::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	// �ǂ̃R���C�_�����݂��Ȃ���ΏՓ˂��Ă��Ȃ�
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
