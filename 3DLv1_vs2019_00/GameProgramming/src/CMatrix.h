#pragma once
#ifndef CMATRIX_H
#define CMATRIX_H

class CVector;

class CMatrix {
public:
	//�N�H�[�^�j�I���ŉ�]�s���ݒ肷��
	CMatrix Quaternion(float x, float y, float z, float w);
	//�v�f���̎擾
	int Size();
	CVector VectorZ() const; //Z���x�N�g���̎擾
	CVector VectorX() const; //X���x�N�g���̎擾
	CVector VectorY() const; //Y���x�N�g���̎擾
	CMatrix Transpose() const;
	float* M() const;
	const CMatrix operator*(const CMatrix& m) const;
	void M(int row, int col, float value); //�s��l�̑��
	CMatrix Translate(float mx, float my, float mz); //�ړ��s��̍쐬
	CMatrix RotateX(float degree);
	CMatrix RotateZ(float degree);
	CMatrix RotateY(float degree); //��]�s��(Y��)�̍쐬
	float M(int r, int c) const; //�s��n�̎擾
	CMatrix Scale(float sx, float sy, float sz); //�g��k���s��̍쐬
	void Print(); //4x4�̍s�����ʏo��
	CMatrix(); //�f�t�H���g�R���X�g���N�^
	CMatrix Identity(); //�P�ʍs��̍쐬
private:
	float mM[4][4]; //4x4�̍s��f�[�^��ݒ�
};

#endif