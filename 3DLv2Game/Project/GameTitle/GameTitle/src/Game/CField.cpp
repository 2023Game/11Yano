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

// フィールドのインスタンス
CField* CField::spInstanse = nullptr;

// フィールドのインスタンスを返す
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

	CIntercom* intercom = new CIntercom
	(
		CVector(141.5f, 25.0f, 94.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom->SetDebugName("Intercom1");
#endif
	CIntercom* intercom2 = new CIntercom
	(
		CVector(-93.0f, 25.0f, -97.0f),
		CVector(0.0f, 180.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom2->SetDebugName("Intercom2");
#endif
	CIntercom* intercom3 = new CIntercom
	(
		CVector(36.0f, 25.0f, -44.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom3->SetDebugName("Intercom3");
#endif

	CSwitch* cswitch = new CSwitch
	(
		CVector(100.5f, 25.0f, -139.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	cswitch->SetDebugName("cswitch");
#endif

	CDoor* door = new CDoor
	(
		CVector(153.0f, 12.0f, 92.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door->SetAnimPos
	(
		CVector(163.0f, 12.0f, 94.0f),
		CVector(153.0f, 12.0f, 94.0f)
	);
	door->AddIntercom(intercom);
	CDoor* door2 = new CDoor
	(
		CVector(-93.0f, 12.0f, -117.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door2->SetAnimPos
	(
		CVector(-93.0f, 12.0f, -120.0f),
		CVector(-93.0f, 12.0f, -107.0f)
		
	);
	door2->AddIntercom(intercom2);
	CDoor* door3 = new CDoor
	(
		CVector(153.0f, 12.0f, 92.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door3->SetAnimPos
	(
		CVector(60.0f, 12.0f, -44.0f),
		CVector(47.0f, 12.0f, -44.0f)
	);
	door3->AddIntercom(intercom3);
	mDoors.push_back(door);
	mDoors.push_back(door2);
	mDoors.push_back(door3);


	CGoal* goal = new CGoal
	(
		CVector(-145.0f, 10.30f, -112.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.6f, 0.6f, 0.6f),
		ELayer::eNextStage
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
		// 壁①の周りの経路探索ノード
		new CNavNode(CVector(129.0f, 0.0f, 15.0f));
		new CNavNode(CVector(163.0f, 0.0f, 15.0f));
		new CNavNode(CVector(163.0f, 0.0f, 28.0f));
		new CNavNode(CVector(129.0f, 0.0f, 28.0f));
	}
}

bool CField::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	// 衝突情報保存用
	CHitInfo tHit;
	// 衝突したかどうかのフラグ
	bool isHit = false;

	// フィールドオブジェクトとの衝突判定
	if (CCollider::CollisionRay(mpColliderMesh, start, end, &tHit))
	{
		*hit = tHit;
		isHit = true;
	}

	// ドアとの衝突判定
	for (CDoor* door : mDoors)
	{
		if (door->CollisionRay(start, end, &tHit))
		{
			// まだ衝突していないかすでに衝突しているコライダより近い場合
			if (!isHit || tHit.dist < hit->dist)
			{
				// 衝突情報更新
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
