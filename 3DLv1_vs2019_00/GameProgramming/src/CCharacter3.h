#pragma once
#ifndef CCHARACTER3_H
#define CCHARACTER3_H
#include "CModel.h"
#include "CTransform.h"
#include "CTask.h"

class CCharacter3 :public CTransform ,public CTask {
public:
	CCharacter3();
	~CCharacter3();
	void Model(CModel* m);//モデルの設定
	void Render();
protected:
	CModel* mpModel;//モデルのポインタ
};

#endif