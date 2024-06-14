#pragma once
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "Cmatrix.h"
#include "CTransform.h"
#ifndef CMODEL_H
#define CMODEL_H

class CModel : public CTransform{
public:
	void Render(const CMatrix& m);
	~CModel();
	void Load(char* obj, char* mtl); //モデルファイルの入力
	void Render();
	const std::vector<CTriangle>& Triangles() const;
private:
	CVertex* mpVertexes;
	void CreateVertexbuffer();
	std::vector<CMaterial*> mpMaterials;
	std::vector<CTriangle> mTriangles;
};

#endif