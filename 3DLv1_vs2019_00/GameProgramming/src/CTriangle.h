#pragma once
#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"

class CTriangle {
public:
	void Render(const CMatrix& m); //�`��
	void UV(const CVector& v0, const CVector& v1, const CVector& v2); //UV�ݒ�
	int MaterialIdx(); //�}�e���A���ԍ��̎擾
	void MaterialIdx(int idx); //�}�e���A���ԍ��̐ݒ�
	//Normal(�@���x�N�g���P�C�@���x�N�g��2�A�@���x�N�g���R)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2); 
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2); //���_���W�ݒ�
	void Normal(const CVector& n); //�@���ݒ�
	void Render(); //�`��
private:
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	int mMaterialIdx; //�}�e���A���ԍ�
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
};
#endif