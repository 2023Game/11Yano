#pragma once

#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix {
public:
	void M(int row, int col, float value); //�s��l�̑��
	CMatrix Translate(float mx, float my, float mz); //�ړ��s��̍쐬
	CMatrix RotateX(float degree);
	CMatrix RotateZ(float degree);
	CMatrix RotateY(float degree); //��]�s��(Y��)�̍쐬
	float M(int r, int c) const; //�s��n�̎擾
	CMatrix Scale(float sx, float sy, float sz); //�g��k���s��̍쐬
	void Point(); //4x4�̍s�����ʏo��
	CMatrix(); //�f�t�H���g�R���X�g���N�^
	CMatrix Identity(); //�P�ʍs��̍쐬
private:
	float mM[4][4]; //4x4�̍s��f�[�^��ݒ�
};

#endif