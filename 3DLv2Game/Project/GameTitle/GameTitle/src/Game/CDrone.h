#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CDrone : public CObjectBase
{
public:
	CDrone(const CVector& pos, const CVector& angle, const CVector& size);
	~CDrone();
	void Update() override;
	void Render() override;
private:
	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
};