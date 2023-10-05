#pragma once
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#ifndef CMODEL_H
#define CMODEL_H

class CModel {
public:
	~CModel();
	void Load(char* obj, char* mtl); //���f���t�@�C���̓���
	void Render();
private:
	std::vector<CMaterial*> mpMaterials;
	std::vector<CTriangle> mTriangles;
};

#endif