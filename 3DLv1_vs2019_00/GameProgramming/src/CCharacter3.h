#pragma once
#ifndef CCHARACTER3_H
#define CCHARACTER3_H
#include "CModel.h"
#include "CTransform.h"
#include "CTask.h"

class CCollider;

class CCharacter3 :public CTransform ,public CTask {
public:
	virtual void Collision(CCollider *m,CCollider *o){}//�Փˏ���
	CCharacter3();
	~CCharacter3();
	void Model(CModel* m);//���f���̐ݒ�
	void Render();
protected:
	CModel* mpModel;//���f���̃|�C���^
};

#endif