#pragma once
#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"

class CColliderMesh {
public:
	CColliderMesh();
	~CColliderMesh();
	//モデルから三角コライダの生成
	void Set(CCharacter3* parent, CMatrix* matrix, CModel* model);
private:
	//三角コライダの配列作成
	CColliderTriangle* mpColliderTriangles;
};

#endif