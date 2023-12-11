#pragma once
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "Cmatrix.h"
#ifndef CMODEL_H
#define CMODEL_H

class CModel {
public:
	void Render(const CMatrix& m);
	~CModel();
	void Load(char* obj, char* mtl); //モデルファイルの入力
	void Render();
	std::vector<CTriangle> Triangles() const;
private:
	CVertex* mpVertexes;
	void CreateVertexbuffer();
	std::vector<CMaterial*> mpMaterials;
	std::vector<CTriangle> mTriangles;
};

#endif