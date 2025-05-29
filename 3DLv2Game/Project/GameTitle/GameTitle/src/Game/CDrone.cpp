#include "CDrone.h"
#include "CModel.h"

CDrone::CDrone(const CVector& pos, const CVector& angle, const CVector& size)
{
	mpModel = CResourceManager::Get<CModel>("Drone");

	mpColliderMesh = new CColliderMesh(this, ELayer::eInteractObj, mpModel, true);

	// �ʒu�ƌ����ƃT�C�Y��ݒ�
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
