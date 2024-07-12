#pragma once
#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include "CCharacter3.h"
#include "CMatrix.h"

class CCollisionManager;

class CCollider :public CTransform, public CTask {
	friend CCollisionManager;
public:
	void Matrix(CMatrix* m);
	void ChangePriority();//優先度の変更
	void ChangePriority(int priority);
	static bool CollisionTriangleSphere(CCollider* triangle, CCollider* sphere, CVector* adjust);
	//CollisionTriangleLine(三角コライダ、線分コライダ、調整値)
	//調整池：衝突しない位置まで戻す地
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//コライダタイプ
	enum class EType {
		ESPHERE,//球コライダ
		ETRIANGLE,//三角コライダ
		ELINE,//線分コライダ
	};
	CCollider();
	static bool Collision(CCollider* m, CCollider* o);//衝突判定
	~CCollider();
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	CCharacter3* Parent();//親ポインタの取得
	void Render();
	EType Type();
protected:
	EType mType;//コライダタイプ
	CVector mV[3];//頂点
	CCharacter3* mpParent;//親
	CMatrix* mpMatrix;//親行列
	float mRadius;//半径
};

#endif