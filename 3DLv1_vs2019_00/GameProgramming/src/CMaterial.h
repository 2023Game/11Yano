#pragma once
#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 //���O�̒���

class CMaterial {
public:
	CMaterial(); //�f�t�H���g�R���X�g���N�^
	void Enebled(); //�}�e���A����L���ɂ���
	char* Name(); //�}�e���A�����̎擾
	void Name(char* name); //�}�e���A�����̐ݒ�
	float* Diffuse(); //mDiffuse�z��̎擾
private:
	char mName[MATERIAL_NAME_LEN + 1]; //�}�e���A����
	float mDiffuse[4]; //�g�U���̐FRGBA
};

#endif