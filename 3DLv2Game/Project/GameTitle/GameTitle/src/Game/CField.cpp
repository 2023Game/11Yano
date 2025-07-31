#include "CField.h"
#include "CCollisionManager.h"
#include "CMoveFloor.h"
#include "CRotateFloor.h"
#include "CLineEffect.h"
#include "CNavManager.h"
#include "CNavNode.h"
#include "CIntercom.h"
#include <assert.h>
#include "CDoor.h"
#include "CSwitch.h"
#include "CGoal.h"
#include "CBlackOut.h"

// �t�B�[���h�̃C���X�^���X
CField* CField::spInstanse = nullptr;

// �t�B�[���h�̃C���X�^���X��Ԃ�
CField* CField::Instanse()
{
	return spInstanse;
}

CField::CField()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, CFieldBase()
	, mEffectAnimData(1, 11, true, 11, 0.03f)
{
	assert(spInstanse == nullptr);
	spInstanse = this;

	mpModel = CResourceManager::Get<CModel>("Field");

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	CreateFieldObjects();
}

CField::~CField()
{
	spInstanse = nullptr;

	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}


}

void CField::CreateFieldObjects()
{
	// �C���^�[�t�H��
	CIntercom* intercom = new CIntercom
	(
		CVector(-56.5f, 10.0f, 54.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom->SetDebugName("Intercom1");
#endif
	CIntercom* intercom2 = new CIntercom
	(
		CVector(-116.0f, 10.0f, 106.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom2->SetDebugName("Intercom2");
#endif
	CIntercom* intercom3 = new CIntercom
	(
		CVector(44.5f, 10.0f, 50.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom3->SetDebugName("Intercom3");
#endif
	CIntercom* intercom4 = new CIntercom
	(
		CVector(-17.0f, 10.0f, -84.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom4->SetDebugName("Intercom4");
#endif

	CSwitch* cswitch = new CSwitch
	(
		CVector(-129.0f, 10.30f, 148.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	cswitch->SetDebugName("cswitch");
#endif

	// �h�A
	CDoor* door = new CDoor
	(
		CVector(-68.0f, 0.0f, 54.8f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door->SetAnimPos
	(
		CVector(-80.0f, 0.0f, 54.8f),
		CVector(-68.0f, 0.0f, 54.8f)
	);
	door->AddIntercom(intercom);
	CDoor* door2 = new CDoor
	(
		CVector(-127.4f, 0.0f, 108.46f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door2->SetAnimPos
	(
		CVector(-139.4f, 0.0f, 108.46f),
		CVector(-127.4f, 0.0f, 108.46f)
		
	);
	door2->AddIntercom(intercom2);
	CDoor* door3 = new CDoor
	(
		CVector(54.93f, 0.0f, 48.83f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door3->SetAnimPos
	(
		CVector(66.93f, 0.0f, 48.83f),
		CVector(54.93f, 0.0f, 48.83f)
	);
	door3->AddIntercom(intercom3);
	CDoor* door4 = new CDoor
	(
		CVector(-7.2f, 0.0f, -85.9f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door4->SetAnimPos
	(
		CVector(5.2f, 0.0f, -85.9f),
		CVector(-7.2f, 0.0f, -85.9f)
	);
	door4->AddIntercom(intercom4);
	mDoors.push_back(door);
	mDoors.push_back(door2);
	mDoors.push_back(door3);


	// ��d���u
	CBlackOut* black = new CBlackOut
	(
		CVector(-88.5f, 15.0f, -120.0f),
		CVector(0.0f, 180.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
	// �S�[��
	CGoal* goal = new CGoal
	(
		CVector(29.0f, 0.0f, -18.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.6f, 0.6f, 0.6f),
		ELayer::eGoal
	);
#if _DEBUG
	goal->SetDebugName("Goal");
#endif
}

void CField::CreateNavNodes()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		//// �Ǉ@�̎���̌o�H�T���m�[�h
		//new CNavNode(CVector(-142.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-114.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-114.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-142.0f, 0.0f, 25.0f));

		//// �ǇA�̎���̌o�H�T���m�[�h
		//new CNavNode(CVector(-103.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-75.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-75.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-103.0f, 0.0f, -56.0f));

		//// �ǇB�̎���̌o�H�T���m�[�h
		//new CNavNode(CVector(-64.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-38.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-38.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-64.0f, 0.0f, 25.0f));
	}
}

bool CField::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	// �Փˏ��ۑ��p
	CHitInfo tHit;
	// �Փ˂������ǂ����̃t���O
	bool isHit = false;

	// �t�B�[���h�I�u�W�F�N�g�Ƃ̏Փ˔���
	if (CCollider::CollisionRay(mpColliderMesh, start, end, &tHit))
	{
		*hit = tHit;
		isHit = true;
	}

	// �h�A�Ƃ̏Փ˔���
	for (CDoor* door : mDoors)
	{
		if (door->CollisionRay(start, end, &tHit))
		{
			// �܂��Փ˂��Ă��Ȃ������łɏՓ˂��Ă���R���C�_���߂��ꍇ
			if (!isHit || tHit.dist < hit->dist)
			{
				// �Փˏ��X�V
				*hit = tHit;
				isHit = true;
			}
		}
	}

	return isHit;
}

void CField::Update()
{
}

void CField::Render()
{
	mpModel->Render(Matrix());
}

CCollider* CField::GetFieldCol() const
{
	return mpColliderMesh;
}

std::list<CDoor*> CField::GetDoors() const
{
	return mDoors;
}
