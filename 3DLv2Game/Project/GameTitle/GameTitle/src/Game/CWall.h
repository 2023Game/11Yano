#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CWall : public CObjectBase
{
public:
	CWall(const CVector& pos, const CVector& angle, const CVector& size);
	~CWall();

	// ÉåÉCÇ∆ï«Ç∆ÇÃè’ìÀîªíË
	bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit) override;

	void Update() override;
	void Render() override;

private:
	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
};