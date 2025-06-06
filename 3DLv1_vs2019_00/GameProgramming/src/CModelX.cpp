#include "glew.h"
#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"
#include <ctype.h>
#include "CVector.h"
#include "CMaterial.h"

CModelX::CModelX()
	:mpPointer(nullptr)
	,mLoaded(false)
	,mpSkinningMatrix(nullptr)
{
	//mTokenを初期化
	memset(mToken, 0, sizeof(mToken));
}

void CModelX::Load(char* file)
{
	//ファイルサイズ取得

	FILE* fp;//ファイルポインタの作成
	fp = fopen(file, "rb");//ファイルオープン
	if (fp == NULL)
	{//エラーチェック
		printf("fopen error:%s\n", file);
		return;
	}
	//ファイルの最後へ移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズ取得
	int size = ftell(fp);
	//ファイルサイズ＋1バイト分の領域を確保
	char* buf = mpPointer = new char[size + 1];
	//ふぃあるから3Dモデルのデータを読み込む
	
	//ファイルの先頭へ移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分のデータを読み込む
	fread(buf, size, 1, fp);
	//最後に\0を設定する（文字列の終端）
	buf[size] = '\0';
	
	fclose(fp);//ファイルクローズ

	//ダミールートフレームの作成
	CModelXFrame* p = new CModelXFrame();
	//名前なし
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	//フレーム配列に追加
	mFrame.push_back(p);

	//文字列最後まで繰り返し
	while (*mpPointer != '\0')
	{
		GetToken();//単語取得
		//Template読み飛ばし
		if (strcmp(mToken, "template") == 0)
		{
			SkipNode();
		}
		//Materialの時
		else if (strcmp(mToken, "Material") == 0)
		{
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0)
		{
			//フレーム名取得
			GetToken();
			if (strchr(mToken, '{')) {
				//フレーム名なし：スキップ
				SkipNode();
				GetToken();//}
			}
			else {
				//フレームが無ければ
				if (FindFrame(mToken) == 0) {
					//フレームを作成する
					p->mChild.push_back(new CModelXFrame(this));
				}
			}
		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);//確保した領域を解放する
	//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();
	mLoaded = true;//読み込み済み
	//頂点バッファの作成
	for (size_t i = 0; i < mFrame.size(); i++) {
		if (mFrame[i]->mpMesh != nullptr) {
			mFrame[i]->mpMesh->CreateVertexBuffer();
		}
	}
	//スキンマトリックスのエリア作成
	mpSkinningMatrix = new CMatrix[mFrame.size()];
	//シェーダー読み込み
	mShader.Load("res\\skinmesh.vert", "res\\skinmesh.frag");
}

char* CModelX::GetToken()
{
	char* p = mpPointer;
	char* q = mToken;
	//タブ(\t)空白( )改行(\r)(\n)，；”の区切り文字以外になるまで読み飛ばす
	while (*p != '\0' && IsDelimiter(*p))p++;
	if (*p == '{' || *p == '}')
	{
		//mTokenに代入し次の文字へ
		*q++ = *p++;
	}
	else
	{
		//タブ(\t)空白( )改行(\r)(\n)，；”の区切り文字、
		//または、}の文字になるまでmTokenに代入する
		while (*p != '\0' && !IsDelimiter(*p) && *p != '}')
			*q++ = *p++;
	}

	*q = '\0';//mTokenの最後に\0を代入
	mpPointer = p;//次の読み込むポイントを更新する

	//もしmTokenが//の場合はコメントなので開業まで読み飛ばす
	/*
	strcmp(文字列１,文字列２)
	文字列１と文字列２がひとしいとき０を返す
	文字列１と文字列２が等しくないとき０以外を返す
	*/
	if (!strcmp("//", mToken))
	{
		//改行まで読み飛ばす
		while (*p != '\0' && !strchr("\r\n", *p))p++;
		//読み込み位置の更新
		mpPointer = p;
		//単語を取得(再帰呼出し)
		return GetToken();
	}
	return mToken;
}

bool CModelX::IsDelimiter(char c)
{
	if (c < 0)
		return false;
	//isspace(c)
	//cが空白文字なら０以外を返す
	if (isspace(c) != 0)
		return true;
	
	/*
	* strchr(文字列,文字)
	* 文字列に文字が含まれていると見つかった文字へポインタ返し
	* 見つからないとNULL返し
	*/
	if (strchr(",;\"", c) != NULL)
		return true;
	//区切り文字でない
	return false;
}

CModelX::~CModelX()
{
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
	for (size_t i = 0; i < mAnimationSet.size(); i++)
	{
		delete mAnimationSet[i];
	}
	for (size_t i = 0; i < mMaterial.size(); i++)
	{
		delete mMaterial[i];
	}
	SAFE_DELETE_ARRAY(mpSkinningMatrix);
}

void CModelX::SkipNode()
{
	//文字が終わったら終了
	while (*mpPointer != '\0')
	{
		GetToken();//次の単語取得
		//{が見つかったらループ終了
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	//文字が終わるかカウントが０になったら終了
	while (*mpPointer != '\0' && count > 0)
	{
		GetToken();//次の単語取得
		//{を見つけるとカウントアップ
		if (strchr(mToken, '{'))count++;
		//}を見つけるとカウントダウン
		else if (strchr(mToken, '}'))count--;
	}
}

char* CModelX::Token()
{
	return mToken;
}

void CModelX::Render()
{
	for (size_t i = 0; i < mFrame.size(); i++)
	{
		mFrame[i]->Render();
	}
}

bool CModelX::EOT()
{
	if (*mpPointer == '\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<CAnimationSet*>& CModelX::AnimationSet()
{
	return mAnimationSet;
}

void CModelX::AnimateFrame()
{
	//アニメーションで適用されるフレームの変換行列をゼロクリアする
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* animSet = mAnimationSet[i];
		//重み0飛ばし
		if (animSet->mWeight == 0)continue;
		//フレーム分（Animation分）繰り返す
		for (size_t j = 0;j < animSet->Animation().size(); j++)
		{
			CAnimation* animation =
				animSet->Animation()[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(
				&mFrame[animation->mFrameIndex]
				->mTransformMatrix,
				0, sizeof(CMatrix));
		}
	}
	//アニメーションに該当するフレームの変換行列をアニメーションのデータで設定する
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* animSet = mAnimationSet[i];
		//重み0飛ばし
		if (animSet->mWeight == 0) continue;
		animSet->AnimateMatrix(this);
	}

}

std::vector<CModelXFrame*>& CModelX::Frames()
{
	return mFrame;
}

void CModelX::AnimateVertex()
{
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++)
	{
		//メッシュに面があれば
		if (mFrame[i]->mpMesh != nullptr)
		{
			//頂点をアニメーションで更新
			mFrame[i]->mpMesh->AnimateVertex(this);
		}
	}
}

CMaterial* CModelX::FindMaterial(char* name)
{
	//マテリアル配列のイテレータ作成
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name, (*itr)->Name()) == 0) {
			return *itr;
		}
	}
	//無い時はnullptrを返却
	return nullptr;
}

std::vector<CMaterial*>& CModelX::Material()
{
	return mMaterial;
}



CModelXFrame* CModelX::FindFrame(char* name) {
	//イテレータの作成
	std::vector<CModelXFrame*>::iterator itr;
	//戦闘から最後まで繰り返し
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++) {
		//名前が一致したかあ
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;//一致したらそのアドレスを返す
		}
	}
	return nullptr;//一致するフレームがない場合はnullptrを返す
}

void CModelX::SetSkinWeightFrameIndex()
{
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++)
	{
		//メッシュがあれば
		if (mFrame[i]->mpMesh != nullptr)
		{
			mFrame[i]->mpMesh->SetSkinWeightFrameIndex(this);
		}
	}
}

void CModelX::AnimateVertex(CMatrix* mat) {
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++) {
		//メッシュがあれば
		if (mFrame[i]->mpMesh) {
			//頂点をアニメーションで更新する
			mFrame[i]->mpMesh->AnimateVertex(mat);
		}
	}
}

void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name)
{
	CAnimationSet* anim = mAnimationSet[idx];//分割するアニメーションセットを確定
	CAnimationSet* as = new CAnimationSet();//アニメーションセットの生成
	as->mpName = new char[strlen(name) + 1];
	strcpy(as->mpName, name);
	as->mMaxTime = end - start;
	for (size_t i = 0; i < anim->mAnimation.size(); i++) {//既存のアニメーション分繰り返し
		CAnimation* animation = new CAnimation();//アニメーションの生成
		animation->mpFrameName = new char[strlen(anim->mAnimation[i]->mpFrameName) + 1];
		strcpy(animation->mpFrameName, anim->mAnimation[i]->mpFrameName);
		animation->mFrameIndex = anim->mAnimation[i]->mFrameIndex;
		animation->mKeyNum = end - start + 1;
		animation->mpKey = new CAnimationKey[animation->mKeyNum];//アニメーションキーの生成
		animation->mKeyNum = 0;
		for (int j = start; j <= end && j < anim->mAnimation[i]->mKeyNum; j++) {
			if (j < anim->mAnimation[i]->mKeyNum) {
				animation->mpKey[animation->mKeyNum] = anim->mAnimation[i]->mpKey[j];
			}
			else {
				animation->mpKey[animation->mKeyNum] =
					anim->mAnimation[i]->mpKey[anim->mAnimation[i]->mKeyNum - 1];
			}
			animation->mpKey[animation->mKeyNum].mTime = animation->mKeyNum++;
		}//アニメーションキーのコピー
		as->mAnimation.push_back(animation);//アニメーションの追加
	}
	mAnimationSet.push_back(as);//アニメーションセットの追加
}

bool CModelX::IsLoaded()
{
	return mLoaded;
}

void CModelX::AddAnimationSet(const char* file)
{
	//ファイルサイズを取得する
	FILE* fp;//ファイルポインタ変数の作成
	fp = fopen(file, "rb");//ファイルをオープンする
	if (fp == NULL) {//エラーチェック
		printf("fopen error:%s￥n", file);
		return;
	}
	//ファイルの最後へ移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズの取得
	int size = ftell(fp);

	//ファイルサイズ+1バイト分の領域を確保
	char* buf = mpPointer = new char[size + 1];
	//ファイルから3Dモデルのデータを読み込む
	//ファイルの先頭へ移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分データを読み込む
	fread(buf, size, 1, fp);
	//最後に\0を設定する（文字列の終端）
	buf[size] = '\0';
	fclose(fp);	//ファイルをクローズする

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();	//単語の取得
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}
	SAFE_DELETE_ARRAY(buf);//確保した領域を開放する
}

void CModelX::RenderShader(
	CMatrix* pCombinedMatrix) {
	mShader.Render(this, pCombinedMatrix);
}




CModelXFrame::~CModelXFrame()
{
	if (mpMesh != nullptr)
	{
		delete mpMesh;
	}
	//子フレームをすべて開放する
	std::vector<CModelXFrame*>::iterator itr;
	for (itr = mChild.begin(); itr != mChild.end(); itr++)
	{
		delete* itr;
	}
	//名前エリアを開放する
	SAFE_DELETE_ARRAY(mpName);
}

CModelXFrame::CModelXFrame() 
	:mpMesh(nullptr)
	,mpName(nullptr)
	,mIndex(0)
{

}

CModelXFrame::CModelXFrame(CModelX* model)
	:mpName(nullptr)
	, mIndex(0)
	, mpMesh(nullptr)
{
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.Identity();
	//次の単語（フレーム名の予定）を取得する
	//model->GetToken();//frame name
	//フレーム名分エリアを確保
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名こっぴー
	strcpy(mpName, model->mToken);
	//次の単語（｛の予定）を取得する
	model->GetToken();//{
	//文字がなくなったら終わり
	while (*model->mpPointer != '\0')
	{
		//次の単語取得
		model->GetToken();//frame
		//}かっこの場合は終了
		if (strchr(model->mToken, '}')) break;
		//新たなフレームな場合は子フレームに追加
		if (strcmp(model->mToken,"Frame")==0)
		{
			//フレーム名取得
			model->GetToken();
			if (strchr(model->mToken, '{')) {
				//フレーム名なし：スキップ
				model->SkipNode();
				model->GetToken();//}
			}
			else {
				//フレームが無ければ
				if (model->FindFrame(model->mToken) == 0) {
					//フレームを作成し、子フレームの配列に追加
					mChild.push_back(new CModelXFrame(model));
				}
			}

		}
		else if (strcmp(model->mToken, "FrameTransformMatrix")==0)
		{
			model->GetToken();
			for (int i = 0; i < mTransformMatrix.Size(); i++)
			{
				mTransformMatrix.M()[i] = atof(model->GetToken());
			}
			model->GetToken();//}
		}
		else if (strcmp(model->mToken, "Mesh") == 0)
		{
			mpMesh = new CMesh();
			mpMesh->Init(model);
		}
		else
		{
			//上記以外は読み飛ばす
			model->SkipNode();
		}
	}

}

void CModelXFrame::AnimateCombined(CMatrix* parent)
{
	//自分の変換行列に親からの変換行列を×
	mCombinedMatrix = mTransformMatrix * (*parent);
	//子フレームの合成行列を作成
	for (size_t i = 0; i < mChild.size(); i++) {
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}
/*#ifdef _DEBUG
    printf("Frame:%s\n", mpName);
    mCombinedMatrix.Print();
#endif*/
}

void CModelXFrame::Render()
{
	if (mpMesh != nullptr) mpMesh->Render();
}

int CModelXFrame::Index()
{
	return mIndex;
}

const CMatrix& CModelXFrame::CombinedMatrix()
{
	return mCombinedMatrix;
}




void CMesh::SetSkinWeightFrameIndex(CModelX* model)
{
	//スキンウェイト分繰り返し
	for (size_t i = 0; i < mSkinWeights.size(); i++)
	{
		//フレーム名のフレームを取得
		CModelXFrame* frame = model->FindFrame(mSkinWeights[i]->mpFrameName);
		mSkinWeights[i]->mFrameIndex = frame->Index();
	}
}

CMesh::CMesh()
	:mVertexNum(0)
	,mpVertex(nullptr)
	,mFaceNum(0)
	,mpVertexIndex(nullptr)
	,mNormalNum(0)
	,mpNormal(nullptr)
	,mMaterialNum(0)
	,mMaterialIndexNum(0)
	,mpMaterialIndex(nullptr)
	,mpAnimateVertex(nullptr)
	,mpAnimateNormal(nullptr)
	,mMyVertexBufferId(0)
{

}

CMesh::~CMesh()
{
	SAFE_DELETE_ARRAY(mpVertex);
	SAFE_DELETE_ARRAY(mpVertexIndex);
	SAFE_DELETE_ARRAY(mpNormal);
	SAFE_DELETE_ARRAY(mpMaterialIndex);
	SAFE_DELETE_ARRAY(mpAnimateVertex);
	SAFE_DELETE_ARRAY(mpAnimateNormal);
	SAFE_DELETE_ARRAY(mpTextureCoords);
	//スキンウェイトの削除
	for (size_t i = 0; i < mSkinWeights.size(); i++)
	{
		delete mSkinWeights[i];
	}
}

void CMesh::Init(CModelX* model) 
{
	model->GetToken();//{ or　名前
	if (!strchr(model->Token(), '{'))
	{
		//名前の場合次が{
		model->GetToken();//{
	}

	//頂点数の取得
	mVertexNum = atoi(model->GetToken());
	//頂点数分エリア確保
	mpVertex = new CVector[mVertexNum];
	mpAnimateVertex = new CVector[mVertexNum];
	//頂点数分データ取り込み
	for (int i = 0; i < mVertexNum; i++)
	{
		mpVertex[i].X(atof(model->GetToken()));
		mpVertex[i].Y(atof(model->GetToken()));
		mpVertex[i].Z(atof(model->GetToken()));
	}
	//面数読み込み
	mFaceNum = atoi(model->GetToken());
	//頂点数は1面に3頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3)
	{
		model->GetToken();//頂点数読み飛ばし
		mpVertexIndex[i] = atoi(model->GetToken());
		mpVertexIndex[i + 1] = atoi(model->GetToken());
		mpVertexIndex[i + 2] = atoi(model->GetToken());
	}
	while (!model->EOT()) {
		model->GetToken();//MeshNormals
		//}かっこの場合は終了
		if (strchr(model->Token(), '}')) break;
		if (strcmp(model->Token(), "MeshNormals") == 0) {
			model->GetToken();//{
			//法線データを取得
			mNormalNum = atoi(model->GetToken());
			//法線のデータを配列に組み込む
			CVector* pNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].X(atof(model->GetToken()));
				pNormal[i].Y(atof(model->GetToken()));
				pNormal[i].Z(atof(model->GetToken()));
			}
			//法線数=面数*3
			mNormalNum = atoi(model->GetToken()) * 3;//FaceNum
			int ni;
			//頂点毎に法線データを設定する
			mpNormal = new CVector[mNormalNum];
			mpAnimateNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken();//3
				ni = atoi(model->GetToken());
				mpNormal[i] = pNormal[ni];

				ni = atoi(model->GetToken());
				mpNormal[i + 1] = pNormal[ni];

				ni = atoi(model->GetToken());
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[] pNormal;
			model->GetToken();//}
		}//End of MeshNormals
		//MeshMaterialListのとき
		else if (strcmp(model->Token(), "MeshMaterialList") == 0) {
			model->GetToken();//{
			//Materialの数
			mMaterialNum = atoi(model->GetToken());
			//FaceNum
			mMaterialIndexNum = atoi(model->GetToken());
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = atoi(model->GetToken());
			}
			//マテリアルデータの作成
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();//Material
				if (strcmp(model->Token(), "Material") == 0) {
					mMaterial.push_back(new CMaterial(model));
				}
				else {
					//{ 既出
					model->GetToken();//MaterialName
					mMaterial.push_back(
						model->FindMaterial(model->Token()));
					model->GetToken();//}
				}
			}
			model->GetToken();//End of MeshMaterialList
		}//End of MeshMaterialList
		//SkinWeightsのとき
		else if (strcmp(model->Token(), "SkinWeights") == 0) {
			//CSkinWeightsクラスのインスタンス作成、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		//テクスチャ座標の時
		else if (strcmp(model->Token(), "MeshTextureCoords") == 0) {
			model->GetToken();//{
			//テクスチャ座標数を取得
			int textureCoordsNum = atoi(model->GetToken()) * 2;
			//テクスチャ座標のデータを配列に取り込む
			mpTextureCoords = new float[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i] = atof(model->GetToken());
			}
			model->GetToken();//}
		}

		else
		{
			//以外のノードは読み飛ばし
			model->SkipNode();
		}
	}
}

void CMesh::Render()
{
	//頂点データ、法線データの配列を有効にする
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);//テクスチャマッピングの配列を有効にする

	//頂点データ、法線データの場所を指定する
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	//頂点のインデックスの場所を指定して図形を描画する
	for (int i = 0; i < mFaceNum; i++) {
		mMaterial[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		mMaterial[mpMaterialIndex[i]]->Disabled();
	}

	//頂点データ、法線データの配列を無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CMesh::AnimateVertex(CModelX* model) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//スキンウェイト分繰り返し
	for (size_t i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//オフセット行列とフレーム合成行列を合成
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * model->Frames()[frameIndex]->CombinedMatrix();
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}

void CMesh::AnimateVertex(CMatrix* mat) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//スキンウェイト分繰り返し
	for (size_t i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合成
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * mat[frameIndex];
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}

void CMesh::CreateVertexBuffer() {
	//メッシュ毎に一回作成すればよい
	if (mMyVertexBufferId > 0)
		return;
	if (mVertexNum > 0) {
		//頂点インデックスを使わず、全ての面データを作成
		CVertex* pmyVertex, * vec;
		//頂点数計算
		int myVertexNum = mFaceNum * 3;
		//頂点数分頂点配列作成
		pmyVertex = new CVertex[myVertexNum];
		vec = new CVertex[mVertexNum];
		for (int j = 0; j < mVertexNum; j++) {
			//頂点座標設定
			vec[j].mPosition = mpVertex[j];
			//テクスチャマッピング設定
			if (mpTextureCoords != NULL) {
				vec[j].mTextureCoords.X(mpTextureCoords[j * 2]);
				vec[j].mTextureCoords.Y(mpTextureCoords[j * 2 + 1]);
			}
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//スキンウェイト設定
		for (size_t k = 0; k < mSkinWeights.size(); k++) {
			for (int l = 0; l < mSkinWeights[k]->mIndexNum; l++) {
				int idx = mSkinWeights[k]->mpIndex[l];
				for (int m = 0; m < 4; m++) {
					if (vec[idx].mBoneIndex[m] == 0) {
						vec[idx].mBoneIndex[m] =
							mSkinWeights[k]->mFrameIndex;
						vec[idx].mBoneWeight[m] =
							mSkinWeights[k]->mpWeight[l];
						break;
					}
				}
			}
		}
		int k = 0;
		//マテリアル番号の昇順に面の頂点を設定
		for (size_t i = 0; i < mMaterial.size(); i++) {
			int w = k;
			for (int j = 0; j < mMaterialIndexNum; j++) {
				if (mpMaterialIndex[j] == i) {
					//頂点配列に設定し、法線を設定する
					pmyVertex[k] = vec[mpVertexIndex[j * 3]];
					pmyVertex[k++].mNormal = mpNormal[j * 3];
					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 1]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 1];
					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 2]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 2];
				}
			}
			//マテリアル毎の頂点数を追加する
			mMaterialVertexCount.push_back(k - w);
		}
		//頂点バッファの作成
		glGenBuffers(1, &mMyVertexBufferId);
		//頂点バッファをバインド
		glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBufferId);
		//バインドしたバッファにデータを転送
		glBufferData(GL_ARRAY_BUFFER
			, sizeof(CVertex) * myVertexNum
			, pmyVertex, GL_STATIC_DRAW);
		//バインド解除
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//配列解放
		delete[] pmyVertex;
		delete[] vec;
		pmyVertex = nullptr;
	}
}





CSkinWeights::~CSkinWeights()
{
	SAFE_DELETE_ARRAY(mpFrameName);
	SAFE_DELETE_ARRAY(mpIndex);
	SAFE_DELETE_ARRAY(mpWeight);
}

CSkinWeights::CSkinWeights(CModelX* model)
	:mpFrameName(nullptr)
	,mFrameIndex(0)
	,mIndexNum(0)
	,mpIndex(nullptr)
	,mpWeight(nullptr)
{
	model->GetToken();//{
	model->GetToken();//FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());

	//頂点番号数取得
	mIndexNum = atoi(model->GetToken());
	//頂点番号が０を超える
	if (mIndexNum > 0)
	{
		//頂点番号と頂点ウェイトのエリア確保
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = atoi(model->GetToken());
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = atof(model->GetToken());
	}
	//オフセット行列取得
	for (int i = 0; i < 16; i++) {
		mOffset.M()[i] = atof(model->GetToken());
	}
	model->GetToken();//}

}



CAnimationSet::~CAnimationSet()
{
	SAFE_DELETE_ARRAY(mpName);
	//アニメーション要素の削除
	for (size_t i = 0; i < mAnimation.size(); i++) {
		delete mAnimation[i];
	}
}

CAnimationSet::CAnimationSet()
	:mTime(0.0f)
	,mWeight(0.0f)
	,mMaxTime(0.0f)
	,mpName(nullptr)
{

}

CAnimationSet::CAnimationSet(CModelX* model)
	:mpName(nullptr)
	,mTime(0)
	,mWeight(0)
	,mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken();//AnimationName
	//アニメーションセット名を退避
	mpName = new char[strlen(model->Token()) + 1];
	strcpy(mpName, model->Token());
	model->GetToken();//{
	while (!model->EOT()) {
		model->GetToken();//} or Animation
		if (strchr(model->Token(), '}')) break;
		if (strcmp(model->Token(), "Animation") == 0) {
			//Animation要素読み込み
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//終了時間設定
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
}

void CAnimationSet::Time(float time)
{
	mTime = time;
}

void CAnimationSet::Weight(float weight)
{
	mWeight = weight;
}

void CAnimationSet::AnimateMatrix(CModelX* model)
{
	//重みが0は飛ばす
	if (mWeight == 0) return;
	//フレーム分(Animation分)繰り返す
	for (size_t j = 0; j < mAnimation.size(); j++) {
		//フレームを取得する
		CAnimation* animation = mAnimation[j];
		//キーがない場合は次のアニメーションへ
		if (animation->mpKey == nullptr) continue;
		//該当するフレームの取得
		CModelXFrame* frame = model->mFrame[animation->mFrameIndex];
		//最初の時間より小さい場合
		if (mTime < animation->mpKey[0].mTime) {
			//変換行列を0コマ目の行列で更新
			frame->mTransformMatrix += animation->mpKey[0].mMatrix * mWeight;
		}
		//最後の時間より大きい場合
		else if (mTime >= animation->mpKey[animation->mKeyNum - 1].mTime) {
			//変換行列を最後のコマの行列で更新
			frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * mWeight;
		}
		else {
			//時間の途中の場合
			for (int k = 1; k < animation->mKeyNum; k++) {
				//変換行列を線形補間にて更新
				if (mTime < animation->mpKey[k].mTime && 
					animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime) {
					float r = (animation->mpKey[k].mTime - mTime) /
						(animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
					frame->mTransformMatrix +=
						(animation->mpKey[k - 1].mMatrix * r +
							animation->mpKey[k].mMatrix * (1 - r)) * mWeight;
					break;
				}
			}
		}
	}
}

std::vector<CAnimation*>& CAnimationSet::Animation()
{
	return mAnimation;
}

float CAnimationSet::Time()
{
	return mTime;
}

float CAnimationSet::MaxTime()
{
	return mMaxTime;
}



CAnimation::~CAnimation() {
	SAFE_DELETE_ARRAY(mpFrameName);
	SAFE_DELETE_ARRAY(mpKey);
}

CAnimation::CAnimation()
	:mKeyNum(0)
	,mpKey(nullptr)
	,mpFrameName(nullptr)
	,mFrameIndex(0)
{

}

CAnimation::CAnimation(CModelX* model)
	:mpFrameName(nullptr)
	,mFrameIndex(0)
	,mKeyNum(0)
	,mpKey(nullptr)
{
	model->GetToken();//{ or AnimationName
	if (strchr(model->Token(), '{')) {
		model->GetToken();//{
	}
	else {
		model->GetToken();//{
		model->GetToken();//{
	}

	model->GetToken();//FrameNmae
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());
	mFrameIndex = model->FindFrame(model->Token())->Index();
	model->GetToken();
	
	//キーの配列を保存しておく配列
	CMatrix* key[4] = { nullptr,nullptr,nullptr,nullptr };
	//時間の配列を保存しておく配列
	float* time[4] = { nullptr,nullptr,nullptr,nullptr };
	while (!model->EOT()) {
		model->GetToken();//} or AnimationKey
		if (strchr(model->Token(), '}')) break;
		if (strcmp(model->Token(), "AnimationKey") == 0) {
			model->GetToken();//{
			int type = atoi(model->GetToken());//データタイプ取得
			mKeyNum = atoi(model->GetToken());//時間数取得
			switch (type) {
			case 0://RotationQuaternion
				//行列の配列を時間数分確保
				key[type] = new CMatrix[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = atof(model->GetToken());//時間取得
					model->GetToken();//4を読み飛ばし
					//w,x,y,zを取得
					float w = atof(model->GetToken());
					float x = atof(model->GetToken());
					float y = atof(model->GetToken());
					float z = atof(model->GetToken());
					//クォータニオンから回転行列に変換
					key[type][i].Quaternion(x, y, z, w);
				}
				break;
			case 1://拡大・縮小の行列作成
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = atof(model->GetToken());
					model->GetToken();//3
					float x = atof(model->GetToken());
					float y = atof(model->GetToken());
					float z = atof(model->GetToken());
					key[type][i].Scale(x, y, z);
				}
				break;
			case 2://移動の行列作成
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = atof(model->GetToken());
					model->GetToken();//3
					float x = atof(model->GetToken());
					float y = atof(model->GetToken());
					float z = atof(model->GetToken());
					key[type][i].Translate(x, y, z);
				}
				break;
			case 4://行列データを取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					mpKey[i].mTime = atof(model->GetToken());//Time
					model->GetToken();//16
					for (int j = 0; j < 16; j++) {
						mpKey[i].mMatrix.M()[j] = atof(model->GetToken());
					}
				}
				break;
			}
			model->GetToken();//}
		}
		else {
			model->SkipNode();
		}
	}

	if (mpKey == nullptr) {
		//時間分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//時間設定
			mpKey[i].mTime = time[2][i];//Time
			//行列作成 Scale*Rotation*Position
			mpKey[i].mMatrix = key[1][i] * key[0][i] * key[2][i];
		}
	}
	//確保したエリア開放
	for (int i = 0; i < ARRAY_SIZE(key); i++) {
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}

}