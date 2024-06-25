#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
class CSkinWeights;
class CModelX;//�N���X�̐錾
class CModelXFrame;
class CMesh;
class CMaterial;
class CAnimationSet;


#define MODEL_FILE "res\\sample.blend.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
	friend CAnimationSet;
public:
	bool EOT();//�g�[�N�����Ȃ��Ȃ�����true
	void Render();
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
	std::vector<CAnimationSet*> mAnimationSet;//�Z�C���[�V�����̔z��
	std::vector<CModelXFrame*> mFrame;//�t���[���̔z��
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);
	char* mpPointer;//�ǂݍ��݈ʒu
	char mToken[1024];//���o�����P��̗̈�
};

class CModelXFrame {
public:
	void Render();
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

class CSkinWeights {
	friend class CMesh;
	friend class CModelX;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
	char* mpFrameName;//�t���[����
	int mFrameIndex;//�t���[���ԍ�
	int mIndexNum;//���_�ԍ���
	int* mpIndex;//���_�ԍ��z��
	float* mpWeight;//���_�E�F�C�g�z��
	CMatrix mOffset;//�I�t�Z�b�g�}�g���N�X
private:
	
};

class CMesh {
public:
	void Render();
	//�R���X�g���N�^
	CMesh();
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
private:
	std::vector<CSkinWeights*> mSkinWeights;//�X�L���E�F�C�g
	int mMaterialNum;//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	int* mpMaterialIndex;//�}�e���A���ԍ�
	std::vector<CMaterial*> mMaterial;//�}�e���A���f�[�^
	int mNormalNum;//�@����
	CVector* mpNormal;//�@���x�N�g��
	int mFaceNum;//�ʐ�
	int* mpVertexIndex;//�ʂ��\�����钸�_�C���f�b�N�X
	int mVertexNum;//���_��
	CVector* mpVertex;//���_�f�[�^
};

class CAnimationSet {
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	char* mpName;//�A�j���[�V�����Z�b�g��
};

#endif