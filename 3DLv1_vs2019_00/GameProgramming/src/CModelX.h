#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
class CModelX;//�N���X�̐錾
class CModelXFrame;

#define MODEL_FILE "res\\sample.blend.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
public:
	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//�P����o��
	char* GetToken();
	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
private:
	std::vector<CModelXFrame*> mFrame;//�t���[���̔z��
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);
	char* mpPointer;//�ǂݍ��݈ʒu
	char mToken[1024];//���o�����P��̗̈�
};
class CModelXFrame {
public:
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	~CModelXFrame();//�f�X�g���N�^
private:
	std::vector<CModelXFrame*> mChild;//�q�t���[���̔z��
	CMatrix mTransformMatrix;//�ϊ��s��
	char* mpName;//�t���[����
	int mIndex;//�t���[���ԍ�
};
#endif