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

	// レイとフィールドオブジェクトとの衝突判定
	bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit) override;

	void Update();
	void Render();
	//カメラとの当たり判定取得
	CCollider* GetFieldCol() const;
	std::list<CDoor*> GetDoors() const;
private:

	void CreateFieldObjects();
	// 経路探索用ノードを作成
	void CreateNavNodes();

	static CField2* spInstanse;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	TexAnimData mEffectAnimData;

	// ドアオブジェクトのリスト
	std::list<CDoor*> mDoors;

	std::list<CIntercom*> mIntercoms;
};