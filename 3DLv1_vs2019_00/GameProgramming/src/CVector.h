#pragma once
#ifndef CVECTOR_H
#define CVECTIR_H

class CVector {
public:
	//�e���ł̒l�̐ݒ�
	void Set(float x, float y, float z);
	float X()const; //X�̒l�𓾂�
	float Y()const; //Y�̒l�𓾂�
	float Z()const; //Z�̒l�𓾂�
private:
	float mX, mY, mZ; //3D�e���ł̒l��ݒ�
};
#endif