#include "CDrone.h"
#include "CModel.h"

CDrone::CDrone(const CVector& pos, const CVector& angle, const CVector& size)
{
	mpModel = CResourceManager::Get<CModel>("Drone");

	mpColliderMesh = new CColliderMesh(this, ELayer::eInteractObj, mpModel, true);

	// 位置と向きとサイズを設定
	Position(pos);
	Rotation(angle);
	Scale(size);

}

CDrone::~CDrone()
{
}

void CDrone::Update()
{
}

void CDrone::Render()
{
	mpModel->Render(Matrix());
}
