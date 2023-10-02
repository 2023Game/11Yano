#include "CModel.h"
#include <stdio.h>
void CModel::Load(char* obj, char* mtl) {
	FILE* fp; //ファイルポインタ変数の作成
	FILE* fp2;
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
	fp2 = fopen(obj, "r");
	if (fp2 == NULL) {
		printf("%s file open error\n", obj); //コンソールにエラー出力して戻る
		return;
	}
	while (fgets(buf, sizeof(buf), fp2) != NULL) {
		printf("%s", buf); //入力した値をコンソールに出力する
	}

	fclose(fp); //ファイルのクローズ
	fclose(fp2);
}