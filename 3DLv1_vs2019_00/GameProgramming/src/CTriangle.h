#pragma once
#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"

class CTriangle {
public:
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2); //頂点座標設定
	void Normal(const CVector& n); //法線設定
	void Render(); //描画
private:
	CVector mV[3]; //頂点座標
	CVector mN; //法線
};
#endif