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

	// レイとフィールドオブジェクトとの衝突判定
	bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit) override;

	void Update();
	void Render();

private:
	// 壁を生成
	void CreateWalls();
	void CreateIntercoms();
	void CreateFieldObjects();
	// 経路探索用ノードを作成
	void CreateNavNodes();

	static CField* spInstanse;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	CModel* mpCubeModel;
	CModel* mpCylinderModel;

	TexAnimData mEffectAnimData;

	// ぁべオブジェクトのリスト
	std::list<CWall*> mWalls;

	// ドアオブジェクトのリスト
	std::list<CDoor*> mDoors;

	std::list<CIntercom*> mIntercoms;
};