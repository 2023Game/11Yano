#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
class CModelX;//�N���X�̐錾
class CModelXFrame;
class CMesh;

#define MODEL_FILE "res\\sample.blend.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
public:
	char* Token();
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
	CMesh* mpMesh;//Mesh�f�[�^
	std::vector<CModelXFrame*> mChild;//�q�t���[���̔z��
	CMatrix mTransformMatrix;//�ϊ��s��
	char* mpName;//�t���[����
	int mIndex;//�t���[���ԍ�
};

class CMesh {
public:
	//�R���X�g���N�^
	CMesh();
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
private:
	int mNormalNum;//�@����
	CVector* mpNormal;//�@���x�N�g��
	int mFaceNum;//�ʐ�
	int* mpVertexIndex;//�ʂ��\�����钸�_�C���f�b�N�X
	int mVertexNum;//���_��
	CVector* mpVertex;//���_�f�[�^
};
#endif