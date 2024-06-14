#pragma once
#include "CTexture.h"
#include "CVertex.h"
#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 //名前の長さ

class CMaterial {
public:
	void VertexNum(int num); //頂点数の設定
	int VertexNum(); //頂点数の取得
	void Disabled(); //マテリアル無効
	CTexture* Texture(); //テクスチャの取得
	CMaterial(); //デフォルトコンストラクタ
	void Enabled(); //マテリアルを有効にする
	char* Name(); //マテリアル名の取得
	void Name(char* name); //マテリアル名の設定
	float* Diffuse(); //mDiffuse配列の取得
private:
	int mVertexNum;
	CTexture mTexture;
	char mName[MATERIAL_NAME_LEN + 1]; //マテリアル名
	float mDiffuse[4]; //拡散光の色RGBA
};

#endif