#pragma once
#include <vector>
#include "CTriangle.h"
#ifndef CMODEL_H
#define CMODEL_H

class CModel {
public:
	void Load(char* obj, char* mtl); //モデルファイルの入力
	void Render();
private:
	std::vector<CTriangle> mTriangles;
};

#endif