#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
class CSkinWeights;
class CModelX;//クラスの宣言
class CModelXFrame;
class CMesh;
class CMaterial;
class CAnimationSet;


#define MODEL_FILE "res\\sample.blend.x"
//領域開放をマクロか
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
	friend CAnimationSet;
public:
	bool EOT();//トークンがなくなったらtrue
	void Render();
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
	std::vector<CAnimationSet*> mAnimationSet;//兄イメーションの配列
	std::vector<CModelXFrame*> mFrame;//フレームの配列
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
	char* mpPointer;//読み込み位置
	char mToken[1024];//取り出した単語の領域
};

class CModelXFrame {
public:
	void Render();
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

class CSkinWeights {
	friend class CMesh;
	friend class CModelX;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
	char* mpFrameName;//フレーム名
	int mFrameIndex;//フレーム番号
	int mIndexNum;//頂点番号数
	int* mpIndex;//頂点番号配列
	float* mpWeight;//頂点ウェイト配列
	CMatrix mOffset;//オフセットマトリクス
private:
	
};

class CMesh {
public:
	void Render();
	//コンストラクタ
	CMesh();
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
private:
	std::vector<CSkinWeights*> mSkinWeights;//スキンウェイト
	int mMaterialNum;//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int* mpMaterialIndex;//マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ
	int mNormalNum;//法線数
	CVector* mpNormal;//法線ベクトル
	int mFaceNum;//面数
	int* mpVertexIndex;//面を構成する頂点インデックス
	int mVertexNum;//頂点数
	CVector* mpVertex;//頂点データ
};

class CAnimationSet {
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	char* mpName;//アニメーションセット名
};

#endif