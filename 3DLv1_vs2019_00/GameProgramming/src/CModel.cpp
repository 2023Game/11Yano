#include "CModel.h"
#include <stdio.h>
#include "CVector.h"
#include "CMaterial.h"

int strcmp(const char* s1, const char* s2) //文字列s1とs2の比較
{
	int i = 0;
	//文字が同じ場合は繰り返す、どっちかの文字が終わるとループ終了
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i]; //同じなら引いて０
}

void CModel::Load(char* obj, char* mtl) {
	std::vector<CVector> vertex; //頂点データの保存
	std::vector<CVector> normal; //法線データの保存
	std::vector<CVector> uv; //テクスチャマッピングの保存

	FILE* fp; //ファイルポインタ変数の作成
	char buf[256]; //ファイルからデータ入力、入力エリア作成

	fp = fopen(mtl, "r"); //ファイルオープン

	//NULLの時はエラー
	if (fp == NULL) {
		printf("%s file open error\n", mtl); //コンソールにエラー出力して戻る
		return;
	}

	int idx = 0; //マテリアルインデックス
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		char str[4][64] = { "","","","" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]); //文字列からデータを4つ変数へ代入
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			pm->Name(str[1]); //マテリアル名の設定
			mpMaterials.push_back(pm); //マテリアルの可変長配列に追加
			idx = mpMaterials.size() - 1; //配列の長さを取得
		}
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}

	fclose(fp); //ファイルのクローズ

	fp = fopen(obj, "r");

	if (fp == NULL) {
		printf("%s file open error\n", obj);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		char str[4][64] = { "","","","" }; //データを分割
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]); //文字列からデータを4つ変数へ代入
		if (strcmp(str[0], "v") == 0) //文字列比較
		{
			//可変長配列vertexに追加
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}

		else if (strcmp(str[0], "f") == 0) {
			int v[3], n[3]; //頂点と法線の番号作成
			if (strstr(str[1], "//")) {
				sscanf(str[1], "%d//%d", &v[0], &n[0]); //頂点と法線の番号取得
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				CTriangle t; //三角形作成
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.MaterialIdx(idx); //マテリアル番号の設定
				mTriangles.push_back(t); //mTrianglesに三角形を追加
			}
			else {
				int u[3]; //テクスチャマッピングの番号
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]); //頂点と法線とマッピングの番号取得
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				CTriangle t; //三角形作成
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.UV(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				t.MaterialIdx(idx);
				mTriangles.push_back(t);
			}
		}
		else if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		else if (strcmp(str[0], "usemtl") == 0) {
			//可変長配列を後から比較
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//同じ名前のマテリアルがあればループ終了
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //ループから出る
				}
			}
		}
		else if (strcmp(str[0], "vt") == 0) {
			//可変長配列uvに追加
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
	}

	fclose(fp);
}

void CModel::Render() {
	for (int i = 0; i < mTriangles.size(); i++) {
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled(); //マテリアルの適用
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}

CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
}

void CModel::Render(const CMatrix& m) {
	for (int i = 0; i < mTriangles.size(); i++) {
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render(m);
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}