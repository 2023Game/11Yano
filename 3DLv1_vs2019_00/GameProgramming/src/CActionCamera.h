#pragma once
#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
#include "CInput.h"

class CActionCamera : public CTransform {
public:
	//�J������X���擾
	CVector VectorX();
	//�J������Z���擾
	CVector VectorZ();
	CActionCamera();
	static CActionCamera* Instance();//�C���X�^���X�̎擾
	void Set(float distance, float xaxis, float yaxis);//�ݒ胁�\�b�h(����, X��],Y��])
	void Update();//�J�����X�V
	void Render();//�J�����K�p
private:
	static CActionCamera* spInstance;//�C���X�^���X
	CVector mEye;//���_
	CVector mCenter;//�����_
	CVector mUp;//�����
	CMatrix mModelView;//���f���r���[�s��
	CInput mInput;//���̓N���X
};
#endif