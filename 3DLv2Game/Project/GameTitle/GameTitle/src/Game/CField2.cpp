#include "CField2.h"
#include "CCollisionManager.h"
#include "CLineEffect.h"
#include "CIntercom.h"
#include <assert.h>
#include "CNavManager.h"
#include "CNavNode.h"
#include "CDoor.h"
#include "CSwitch.h"
#include "CGoal.h"

// フィールドのインスタンス
CField2* CField2::spInstanse = nullptr;

// フィールドのインスタンスを返す
CField2* CField2::Instanse()
{
	return spInstanse;
}

CField2::CField2()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, CFieldBase()
	, mEffectAnimData(1, 11, true, 11, 0.03f)
{
	assert(spInstanse == nullptr);
	spInstanse = this;

	mpModel = CResourceManager::Get<CModel>("Field2");

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);;
	CreateNavNodes();
	CreateFieldObjects();
}

CField2::~CField2()
{
	spInstanse = nullptr;

	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}
}

void CField2::CreateFieldObjects()
{

	CIntercom* intercom = new CIntercom
	(
		CVector(38.0f, 25.0f, -44.0f),
		CVector(0.0f, 270.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom->SetDebugName("Intercom1");
#endif
	CIntercom* intercom2 = new CIntercom
	(
		CVector(59.0f, 25.0f, 92.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.5f, 0.5f, 0.5f)
	);
#if _DEBUG
	intercom2->SetDebugName("Intercom2");
#endif
	CIntercom* intercom3 = new CIntercom
	(
		CVector(-54.0f, 25.0f, -126.0f),
		CVector(0.0f, 0.0f, 0.0f),
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
		CVector(60.0f, 12.0f, -44.0f),
		CVector(48.0f, 12.0f, -44.0f)
	);
	door->AddIntercom(intercom);
	CDoor* door2 = new CDoor
	(
		CVector(-93.0f, 12.0f, -117.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door2->SetAnimPos
	(
		CVector(35.0f, 12.0f, 92.0f),
		CVector(48.0f, 12.0f, 92.0f)

	);
	door2->AddIntercom(intercom2);
	CDoor* door3 = new CDoor
	(
		CVector(153.0f, 12.0f, 92.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f)
	);
	door3->SetAnimPos
	(

		CVector(-54.0f, 12.0f, -102.0f),
		CVector(-54.0f, 12.0f, -115.0f)
	);
	door3->AddIntercom(intercom3);
	mDoors.push_back(door);
	mDoors.push_back(door2);
	mDoors.push_back(door3);


	CGoal* goal = new CGoal
	(
		CVector(-50.0f, 10.30f, 25.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.6f, 0.6f, 0.6f),
		ELayer::eGoal
	);
#if _DEBUG
	goal->SetDebugName("Goal");
#endif

	// 電撃エフェクト
	CLineEffect* le = new CLineEffect(ETag::eBullet);
	le->SetTexture("LightningBolt");
	le->SetBaseUV(CRect(0.0f, 0.0f, 128.0f, 1024.0f));
	le->SetAnimData(&mEffectAnimData);
}

void CField2::CreateNavNodes()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		// 壁①の周りの経路探索ノード
		new CNavNode(CVector(129.0f, 0.0f, 15.0f));
		new CNavNode(CVector(163.0f, 0.0f, 15.0f));
		new CNavNode(CVector(163.0f, 0.0f, 28.0f));
		new CNavNode(CVector(129.0f, 0.0f, 28.0f));

		new CNavNode(CVector(111.0f, 0.0f, -6.0f));

		// 壁②の経路探索ノード
		new CNavNode(CVector(5.0f, 0.0f, 57.0f));
		new CNavNode(CVector(5.0f, 0.0f, -12.0f));
		new CNavNode(CVector(-9.0f, 0.0f, -12.0f));
		new CNavNode(CVector(-9.0f, 0.0f, 57.0f));

		// 壁③の経路探索ノード
		new CNavNode(CVector(26.0f, 0.0f, -160.0f));
		new CNavNode(CVector(10.0f, 0.0f, -160.0f));

		new CNavNode(CVector(-44.0f, 0.0f, 130.0f));
		new CNavNode(CVector(-58.0f, 0.0f, 130.0f));

		new CNavNode(CVector(-103.0f, 0.0f, 95.0f));

		new CNavNode(CVector(-103.0f, 0.0f, -43.0f));

		new CNavNode(CVector(-90.0f, 0.0f, -82.0f));

		new CNavNode(CVector(8.0f, 0.0f, -70.0f));
	}
}

bool CField2::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
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

void CField2::Update()
{
}

void CField2::Render()
{
	mpModel->Render(Matrix());
}

CCollider* CField2::GetFieldCol() const
{
	return mpColliderMesh;
}

std::list<CDoor*> CField2::GetDoors() const
{
	return mDoors;
}
