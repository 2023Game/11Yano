#pragma once
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CWall;
class CDoor;
class CIntercom;

class CField : public CObjectBase
{
public:
	static CField* Instanse();

	CField();
	~CField();

	// ���C�ƃt�B�[���h�I�u�W�F�N�g�Ƃ̏Փ˔���
	bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit) override;

	void Update();
	void Render();

private:
	// �ǂ𐶐�
	void CreateWalls();
	void CreateIntercoms();
	void CreateFieldObjects();
	// �o�H�T���p�m�[�h���쐬
	void CreateNavNodes();

	static CField* spInstanse;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	CModel* mpCubeModel;
	CModel* mpCylinderModel;

	TexAnimData mEffectAnimData;

	// ���׃I�u�W�F�N�g�̃��X�g
	std::list<CWall*> mWalls;

	// �h�A�I�u�W�F�N�g�̃��X�g
	std::list<CDoor*> mDoors;

	std::list<CIntercom*> mIntercoms;
};