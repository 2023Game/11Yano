#pragma once
#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"

class CTriangle {
public:
	void Render(const CMatrix& m); //描画
	void UV(const CVector& v0, const CVector& v1, const CVector& v2); //UV設定
	int MaterialIdx(); //マテリアル番号の取得
	void MaterialIdx(int idx); //マテリアル番号の設定
	//Normal(法線ベクトル１，法線ベクトル2、法線ベクトル３)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2); 
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2); //頂点座標設定
	void Normal(const CVector& n); //法線設定
	void Render(); //描画
private:
	CVector mUv[3]; //テクスチャマッピング
	int mMaterialIdx; //マテリアル番号
	CVector mV[3]; //頂点座標
	CVector mN[3]; //法線
};
#endif