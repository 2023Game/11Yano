#pragma once
#ifndef CMODELX_H
#define CMODELX_H
#include <vector>
#include "CMatrix.h"
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

class CSkinWeights;
class CModelX;//�N���X�̐錾
class CModelXFrame;
class CMesh;
class CMaterial;
class CAnimationSet;
class CAnimation;
class CAnimationKey;


#define MODEL_FILE "res\\���O�i.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=nullptr;}

class CModelX {
	friend CModelXFrame;
	friend CAnimationSet;
	friend CAnimation;
public:
	void AnimateVertex(CMatrix*);
	std::vector<CMaterial*>& Material();
	CMaterial* FindMaterial(char* name);
	void AnimateVertex();//���_�ɃA�j���[�V�����K�p
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	std::vector<CModelXFrame*>& Frames();
	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);
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
	std::vector<CMaterial*> mMaterial;//�܂ꃊ�A���z��
	std::vector<CAnimationSet*> mAnimationSet;//�Z�C���[�V�����̔z��
	std::vector<CModelXFrame*> mFrame;//�t���[���̔z��
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);
	char* mpPointer;//�ǂݍ��݈ʒu
	char mToken[1024];//���o�����P��̗̈�
};

class CModelXFrame {
	friend CAnimationSet;
	friend CAnimation;
	friend CModelX;
public:
	const CMatrix& CombinedMatrix();
	void AnimateCombined(CMatrix* parent);
	int Index();
	void Render();
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	~CModelXFrame();//�f�X�g���N�^
private:
	CMatrix mCombinedMatrix;//�����s��
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
	void AnimateVertex(CMatrix*);
	void AnimateVertex(CModelX* model);//���_�ɃA�j���[�V�����K�p
	//�X�L���E�F�C�g�Ƀt���[���ԍ���ݒ�
	void SetSkinWeightFrameIndex(CModelX* model);
	void Render();
	//�R���X�g���N�^
	CMesh();
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
private:
	float* mpTextureCoords;//�e�N�X�`�����W�f�[�^
	CVector* mpAnimateVertex;//�A�j���[�V�����p���_
	CVector* mpAnimateNormal;//�A�j���[�V�����p�@��
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
	friend CModelX;
public:
	float Time();
	float MaxTime();
	void AnimateMatrix(CModelX* model);
	std::vector<CAnimation*>& Animation();
	void Time(float time);//���Ԑݒ�
	void Weight(float weight);//�d�݂̐ݒ�
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	float mTime;//���ݎ���
	float mWeight;//�d��
	float mMaxTime;//�ő厞��
	std::vector<CAnimation*> mAnimation;
	char* mpName;//�A�j���[�V�����Z�b�g��
};

class CAnimation {
	friend CModelX;
	friend CAnimationSet;
public:
	CAnimation(CModelX* model);
	~CAnimation();
private:
	int mKeyNum;//�L�[��(���Ԑ�)
	CAnimationKey* mpKey;//�L�[�̔z��
	char* mpFrameName;//�t���[����
	int mFrameIndex;//�t���[���ԍ�
};

class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
private:
	float mTime;//����
	CMatrix mMatrix;//�s��
};
#endif