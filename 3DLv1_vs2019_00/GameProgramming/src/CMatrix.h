#pragma once

#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix {
public:
	void Point(); //4x4�̍s�����ʏo��
	CMatrix(); //�f�t�H���g�R���X�g���N�^
	CMatrix Identity(); //�P�ʍs��̍쐬
private:
	float mM[4][4]; //4x4�̍s��f�[�^��ݒ�
};

#endif