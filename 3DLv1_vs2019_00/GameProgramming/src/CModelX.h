#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

class CSkinWeights;
class CModelX;//クラスの宣言
class CModelXFrame;
class CMesh;
class CMaterial;
class CAnimationSet;
class CAnimation;
class CAnimationKey;


#define MODEL_FILE "res\\ラグナ.x"
//領域開放をマクロか
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
	friend CAnimationSet;
	friend CAnimation;
public:
	void AnimateVertex(CMatrix*);
	std::vector<CMaterial*>& Material();
	CMaterial* FindMaterial(char* name);
	void AnimateVertex();//頂点にアニメーション適用
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	std::vector<CModelXFrame*>& Frames();
	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);
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
	std::vector<CMaterial*> mMaterial;//まれリアル配列
	std::vector<CAnimationSet*> mAnimationSet;//兄イメーションの配列
	std::vector<CModelXFrame*> mFrame;//フレームの配列
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
	char* mpPointer;//読み込み位置
	char mToken[1024];//取り出した単語の領域
};

class CModelXFrame {
	friend CAnimationSet;
	friend CAnimation;
	friend CModelX;
public:
	const CMatrix& CombinedMatrix();
	void AnimateCombined(CMatrix* parent);
	int Index();
	void Render();
	//コンストラクタ
	CModelXFrame(CModelX* model);
	~CModelXFrame();//デストラクタ
private:
	CMatrix mCombinedMatrix;//合成行列
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
	void AnimateVertex(CMatrix*);
	void AnimateVertex(CModelX* model);//頂点にアニメーション適用
	//スキンウェイトにフレーム番号を設定
	void SetSkinWeightFrameIndex(CModelX* model);
	void Render();
	//コンストラクタ
	CMesh();
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
private:
	float* mpTextureCoords;//テクスチャ座標データ
	CVector* mpAnimateVertex;//アニメーション用頂点
	CVector* mpAnimateNormal;//アニメーション用法線
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
	friend CModelX;
public:
	float Time();
	float MaxTime();
	void AnimateMatrix(CModelX* model);
	std::vector<CAnimation*>& Animation();
	void Time(float time);//時間設定
	void Weight(float weight);//重みの設定
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	float mTime;//現在時間
	float mWeight;//重み
	float mMaxTime;//最大時間
	std::vector<CAnimation*> mAnimation;
	char* mpName;//アニメーションセット名
};

class CAnimation {
	friend CModelX;
	friend CAnimationSet;
public:
	CAnimation(CModelX* model);
	~CAnimation();
private:
	int mKeyNum;//キー数(時間数)
	CAnimationKey* mpKey;//キーの配列
	char* mpFrameName;//フレーム名
	int mFrameIndex;//フレーム番号
};

class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
private:
	float mTime;//時間
	CMatrix mMatrix;//行列
};
#endif