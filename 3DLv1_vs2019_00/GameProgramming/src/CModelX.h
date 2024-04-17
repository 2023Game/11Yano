#pragma once
#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "res\\sample.blend.x"
//領域開放をマクロか
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
public:
	//単語取り出し
	char* GetToken();
	CModelX();
	//ファイル読み込み
	void Load(char* file);
private:
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
	char* mpPointer;//読み込み位置
	char mToken[1024];//取り出した単語の領域
};
#endif