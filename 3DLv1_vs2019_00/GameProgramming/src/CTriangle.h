#pragma once
#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"

class CTriangle {
public:
	//Normal(�@���x�N�g���P�C�@���x�N�g��2�A�@���x�N�g���R)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2); 
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2); //���_���W�ݒ�
	void Normal(const CVector& n); //�@���ݒ�
	void Render(); //�`��
private:
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
};
#endif