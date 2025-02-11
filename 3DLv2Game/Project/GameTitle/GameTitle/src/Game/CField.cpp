#include "CField.h"
#include "CCollisionManager.h"
#include "CMoveFloor.h"
#include "CRotateFloor.h"
#include "CLineEffect.h"
#include "CWall.h"
#include "CIntercom.h"
#include <assert.h>
#include "CNavManager.h"
#include "CNavNode.h"
#include "CDoor.h"

// フィールドのインスタンス
CField* CField::spInstanse = nullptr;

// フィールドのインスタンスを返す
CField* CField::Instanse()
{
	return spInstanse;
}

CField::CField()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, mEffectAnimData(1, 11, true, 11, 0.03f)
{
	assert(spInstanse == nullptr);
	spInstanse = this;

	mpModel = CResourceManager::Get<CModel>("Field");

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	CreateWalls();
	CreateIntercoms();
	CreateNavNodes();

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

void CField::CreateWalls()
{
	//CWall* wall = new CWall
	//(
	//	CVector(20.0f, 0.0f, 0.0f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	CVector(5.0f, 5.0f, 5.0f)
	//);
	//mWalls.push_back(wall); // 生成した壁を壁のリストに追加

	//// 壁②生成
	//wall = new CWall
	//(
	//	CVector(-50.0f, 0.0f, -50.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	CVector(5.0f, 5.0f, 5.0f)
	//);
	//mWalls.push_back(wall);
}

void CField::CreateIntercoms()
{
	
}

void CField::CreateFieldObjects()
{

	CIntercom* intercom = new CIntercom
	(
		CVector(200.5f, 25.0f, 126.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom->SetDebugName("Intercom1");
#endif
	CIntercom* intercom2 = new CIntercom
	(
		CVector(-123.0f, 25.0f, -23.0f),
		CVector(0.0f, 180.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom2->SetDebugName("Intercom2");
#endif
	CIntercom* intercom3 = new CIntercom
	(
		CVector(-221.0f, 25.0f, -125.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom3->SetDebugName("Intercom3");
#endif

	CDoor* door = new CDoor
	(
		CVector(210.5f, 25.0f, 125.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door->SetAnimPos
	(
		CVector(-30.0f, 1.0f, -50.0f),
		CVector(-50.0f, 1.0f, -50.0f)
	);
	door->AddIntercom(intercom);
}

void CField::CreateNavNodes()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		// 壁①の周りの経路探索ノード
		new CNavNode(CVector(144.5f, 0.0f, 87.0f));
		new CNavNode(CVector(221.5f, 0.0f, 87.0f));
		new CNavNode(CVector(221.5f, 0.0f, -94.0f));
		new CNavNode(CVector(144.5f, 0.0f, -94.0f));

		// 壁にの経路探索ノード
		new CNavNode(CVector(29.0f, 0.0f, 87.0f));
		new CNavNode(CVector(108.0f, 0.0f, 87.0f));
		new CNavNode(CVector(108.0f, 0.0f, -94.0f));
		new CNavNode(CVector(29.0f, 0.0f, -94.0f));

		// 壁③の経路探索ノード
		new CNavNode(CVector(-90.0f, 0.0f, 87.0f));
		new CNavNode(CVector(-12.5f, 0.0f, 87.0f));
		new CNavNode(CVector(-12.5f, 0.0f, -94.0f));
		new CNavNode(CVector(-90.0f, 0.0f, -94.0f));
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

	// 壁との衝突判定
	for (CWall* wall : mWalls)
	{
		if (wall->CollisionRay(start, end, &tHit))
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
