#pragma once
#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CCollider.h"
#include "CFieldBase.h"

class CWall;
class CDoor;
class CIntercom;

class CField2 : public CObjectBase, public CFieldBase
{
public:
	static CField2* Instanse();

	CField2();
	~CField2();

	// ���C�ƃt�B�[���h�I�u�W�F�N�g�Ƃ̏Փ˔���
	bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit) override;

	void Update();
	void Render();
	//�J�����Ƃ̓����蔻��擾
	CCollider* GetFieldCol() const;
	std::list<CDoor*> GetDoors() const;
private:

	void CreateFieldObjects();
	// �o�H�T���p�m�[�h���쐬
	void CreateNavNodes();

	static CField2* spInstanse;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	TexAnimData mEffectAnimData;

	// �h�A�I�u�W�F�N�g�̃��X�g
	std::list<CDoor*> mDoors;

	std::list<CIntercom*> mIntercoms;
};