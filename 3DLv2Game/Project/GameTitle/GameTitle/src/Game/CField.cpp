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
	// インターフォン
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

	// ドア
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


	// 停電装置
	CBlackOut* black = new CBlackOut
	(
		CVector(-88.5f, 15.0f, -120.0f),
		CVector(0.0f, 180.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
	// ゴール
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
		//// 壁①の周りの経路探索ノード
		//new CNavNode(CVector(-142.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-114.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-114.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-142.0f, 0.0f, 25.0f));

		//// 壁②の周りの経路探索ノード
		//new CNavNode(CVector(-103.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-75.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-75.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-103.0f, 0.0f, -56.0f));

		//// 壁③の周りの経路探索ノード
		//new CNavNode(CVector(-64.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-38.0f, 0.0f, -56.0f));
		//new CNavNode(CVector(-38.0f, 0.0f, 25.0f));
		//new CNavNode(CVector(-64.0f, 0.0f, 25.0f));
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
