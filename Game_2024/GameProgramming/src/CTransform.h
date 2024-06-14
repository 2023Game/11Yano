#pragma once
#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"

class CTransform {
public:
	const CVector& Position() const;//�ʒu�̎擾
	void Position(const CVector& v);//�ʒu�̐ݒ�
	void Rotation(const CVector& v);//��]�n�̐ݒ�
	void Scale(const CVector& v);//�g��k���̐ݒ�
	const CMatrix& Matrix() const;//�����s��̎擾
	const CMatrix& MatrixRotate() const;//��]�s��̎擾
	void Update();//�s��X�V����
	//Update(�ʒu�A��]�A�X�P�[��)
	void Update(const CVector& pos, const CVector& rot, const CVector& scale);
protected:
	CVector mPosition;//�ʒu
	CVector mRotation;//��]
	CVector mScale;//�g��k��
	CMatrix mMatrixTranslate;//���s�ړ��s��
	CMatrix mMatrixRotate;//��]�s��
	CMatrix mMatrixScale;//�g��k���s��
	CMatrix mMatrix;//�����s��
};

#endif