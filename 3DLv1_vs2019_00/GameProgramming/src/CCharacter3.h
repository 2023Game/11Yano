#pragma once
#ifndef CCHARACTER3_H
#define CCHARACTER3_H
#include "CModel.h"
#include "CTransform.h"

class CCharacter3 :public CTransform {
public:
	void Model(CModel* m);//���f���̐ݒ�
	void Render();
protected:
	CModel* mpModel;//���f���̃|�C���^
};

#endif