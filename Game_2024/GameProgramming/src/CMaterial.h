#pragma once
#include "CTexture.h"
#include "CVertex.h"
#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 //���O�̒���

class CMaterial {
public:
	void VertexNum(int num); //���_���̐ݒ�
	int VertexNum(); //���_���̎擾
	void Disabled(); //�}�e���A������
	CTexture* Texture(); //�e�N�X�`���̎擾
	CMaterial(); //�f�t�H���g�R���X�g���N�^
	void Enabled(); //�}�e���A����L���ɂ���
	char* Name(); //�}�e���A�����̎擾
	void Name(char* name); //�}�e���A�����̐ݒ�
	float* Diffuse(); //mDiffuse�z��̎擾
private:
	int mVertexNum;
	CTexture mTexture;
	char mName[MATERIAL_NAME_LEN + 1]; //�}�e���A����
	float mDiffuse[4]; //�g�U���̐FRGBA
};

#endif