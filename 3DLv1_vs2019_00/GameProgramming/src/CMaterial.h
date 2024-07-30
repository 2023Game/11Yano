#pragma once
#include "CTexture.h"
#include "CVertex.h"
#include "CModelX.h"
#include "CMyShader.h"
#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 //���O�̒���

class CMaterial {
	friend CMyShader;
public:
	CMaterial(CModelX *model);
	~CMaterial();
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
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char* mpTextureFilename;
	int mVertexNum;
	CTexture mTexture;
	char mName[MATERIAL_NAME_LEN + 1]; //�}�e���A����
	float mDiffuse[4]; //�g�U���̐FRGBA
};

#endif