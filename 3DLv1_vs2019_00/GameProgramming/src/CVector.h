#pragma once
#ifndef CVECTOR_H
#define CVECTIR_H

class CVector {
public:
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