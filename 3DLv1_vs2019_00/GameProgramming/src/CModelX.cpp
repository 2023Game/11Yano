#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"
#include <ctype.h>

CModelX::CModelX()
	:mpPointer(nullptr)
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
	//文字列最後まで繰り返し
	while (*mpPointer != '\0')
	{
		GetToken();//単語取得
		//単語がFrameの場合
		if (strcmp(mToken, "Frame") == 0)
		{
			//フレーム作成
			new CModelXFrame(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);//確保した領域を解放する
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



CModelXFrame::~CModelXFrame()
{
	//子フレームをすべて開放する
	std::vector<CModelXFrame*>::iterator itr;
	for (itr = mChild.begin(); itr != mChild.end(); itr++)
	{
		delete* itr;
	}
	//名前エリアを開放する
	SAFE_DELETE_ARRAY(mpName);
}

CModelXFrame::CModelXFrame(CModelX* model)
	:mpName(nullptr)
	, mIndex(0)
{
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.Identity();
	//次の単語（フレーム名の予定）を取得する
	model->GetToken();//frame name
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
			//フレーム作成し子フレームの配列に追加
			mChild.push_back(new CModelXFrame(model));
		}
		else
		{
			//上記以外は読み飛ばす
			model->SkipNode();
		}
	}
	//デバッグバージョンのみ有効
#ifdef _DEBUG
	printf("%s\n", mpName);
#endif
}