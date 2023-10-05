#include "CModel.h"
#include <stdio.h>
#include "CVector.h"

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
	FILE* fp; //ファイルポインタ変数の作成
	char buf[256]; //ファイルからデータ入力、入力エリア作成

	fp = fopen(mtl, "r"); //ファイルオープン

	//NULLの時はエラー
	if (fp == NULL) {
		printf("%s file open error\n", mtl); //コンソールにエラー出力して戻る
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		printf("%s", buf); //入力した値をコンソールに出力する
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
			sscanf(str[1], "%d//%d", &v[0], &n[0]); //頂点と法線の番号取得
			sscanf(str[2], "%d//%d", &v[1], &n[1]);
			sscanf(str[3], "%d//%d", &v[2], &n[2]);
			CTriangle t; //三角形作成
			t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
			mTriangles.push_back(t); //mTrianglesに三角形を追加
		}
	}

	fclose(fp);
}

void CModel::Render() {
	for (int i = 0; i < mTriangles.size(); i++) {
		mTriangles[i].Render();
	}
}