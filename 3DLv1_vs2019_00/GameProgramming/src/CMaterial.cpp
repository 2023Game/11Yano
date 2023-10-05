#include "CMaterial.h"
#include <string.h> //mamset,strncpyのインクルード
#include "glut.h"

//コピー先str1にコピー元str2の文字をlen文字数までコピーする
char* strncpy(char* str1, const char* str2, int len)
{
	int i = 0;
	while (i < len && *str2 != '\0') //iがlenより小さいかつコピー元が終わりでない間繰り返し
	{
		*(str1 + i) = *str2; //コピー先にコピー元を代入
		str2++; //コピー元を次へ
		i++;
	}
	str1[i] = '\0'; //コピー先の文字列に終わり
	return str1; //コピー先の戦闘アドレスを返却
}

CMaterial::CMaterial()
{
	memset(mName, 0, sizeof(mName)); //名前をゼロで埋め
	memset(mDiffuse, 0, sizeof(mDiffuse)); //0で埋める
}

void CMaterial::Enebled()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse); //拡散光の設定
}

char* CMaterial::Name()
{
	return mName;
}

void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN);
}

float* CMaterial::Diffuse()
{
	return mDiffuse;
}