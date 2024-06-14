#pragma once
#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"

class CColliderMesh {
public:
	CColliderMesh();
	~CColliderMesh();
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter3* parent, CMatrix* matrix, CModel* model);
private:
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
};

#endif