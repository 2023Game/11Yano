#pragma once
#include "CFont.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi
{
public:
	void PosY(float f);//���x�̐ݒ�
	void PosX(float f);//�s�b�`�̐ݒ�
	void PosZ(float f);
	void RotY(float f);//���x�̐ݒ�
	void RotX(float f);//�s�b�`�̐ݒ�
	void RotZ(float f);
	//�Q�[���N���A�\��
	void Clear();
	//�Q�[���I�[�o�[�\��
	void Over();
	//�X�^�[�g�\��
	void Start();
	CUi();
	//Time(����)
	void Time(int time);
	void Render();
private:
	float mPosY;//���x�����W
	float mPosX;
	float mPosZ;
	float mRotY;//���x�����W
	float mRotX;
	float mRotZ;
	int mTime;	//�o�ߎ���
	CFont mFont;
};
