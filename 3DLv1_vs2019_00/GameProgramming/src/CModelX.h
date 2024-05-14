#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
class CModelX;//クラスの宣言
class CModelXFrame;
class CMesh;

#define MODEL_FILE "res\\sample.blend.x"
//領域開放をマクロか
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
public:
	char* Token();
	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();
	//単語取り出し
	char* GetToken();
	CModelX();
	//ファイル読み込み
	void Load(char* file);
private:
	std::vector<CModelXFrame*> mFrame;//フレームの配列
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
	char* mpPointer;//読み込み位置
	char mToken[1024];//取り出した単語の領域
};

class CModelXFrame {
public:
	//コンストラクタ
	CModelXFrame(CModelX* model);
	~CModelXFrame();//デストラクタ
private:
	CMesh* mpMesh;//Meshデータ
	std::vector<CModelXFrame*> mChild;//子フレームの配列
	CMatrix mTransformMatrix;//変換行列
	char* mpName;//フレーム名
	int mIndex;//フレーム番号
};

class CMesh {
public:
	//コンストラクタ
	CMesh();
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
private:
	int mNormalNum;//法線数
	CVector* mpNormal;//法線ベクトル
	int mFaceNum;//面数
	int* mpVertexIndex;//面を構成する頂点インデックス
	int mVertexNum;//頂点数
	CVector* mpVertex;//頂点データ
};
#endif