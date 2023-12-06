#pragma once
#include "CMatrix.h"

#ifndef CVECTOR_H
#define CVECTIR_H

class CVector {
public:
	CVector Nomalize() const;//���K���i�傫��1�̃x�N�g���j
	CVector Cross(const CVector& v) const;//�O��
	CVector operator*(const float& f) const;//*���Z�q�̃I�[�o�[���[�h
	float Dot(const CVector& v) const;//����
	float Length() const;
	CVector operator*(const CMatrix &m);
	CVector operator+(const CVector &v) const; //+���Z�q�̃I�[�o�[���[�h
	CVector operator-(const CVector &v) const; //-���Z�q�̃I�[�o�[���[�h
	CVector(); //�f�t�H���g�R���X�g���N�^
	CVector(float x, float y, float z); //�R���X�g���N�^
	void Set(float x, float y, float z); //�e���ł̒l�̐ݒ�
	float X()const; //X�̒l�𓾂�
	float Y()const; //Y�̒l�𓾂�
	float Z()const; //Z�̒l�𓾂�
private:
	float mX, mY, mZ; //3D�e���ł̒l��ݒ�
};
#endif