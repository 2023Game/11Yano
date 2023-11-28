#include "CApplication.h"
#include "glut.h" //OpenGL
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMaterial.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CEnemy.h"
#include "CCollisionManager.h"
#include "CBillBoard.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
#define MODEL_OBJ "res\\f14.obj","res\\f14.mtl" //���f���f�[�^�̎w��
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"
#define MODEL_C5 "res\\c5.obj","res\\c5.mtl"//�G�A���@���f��

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	mModelC5.Load(MODEL_C5);
	new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f,180.0f,0.0f));
	CMatrix matrix;
	matrix.Point();
	mBackGround.Load(MODEL_BACKGROUND);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load(MODEL_OBJ);
	//�r���{�[�h�̍쐬
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();
	CCollisionManager::Instance()->Collision();
	CVector v0, v1, v2, n; //���_1�C2�C3�C�@���f�[�^�̍쐬
	n.Set(0.0f, 1.0f, 0.0f); //�@����������Őݒ肷��
	v0.Set(0.0f, 0.0f, 0.5f); //���_1�̍��W
	v1.Set(1.0f, 0.0f, 0.0f); //���_2�̍��W
	v2.Set(0.0f, 0.0f, -0.5f); //���_3�̍��W

	if (mInput.Key('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('O'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}

	CVector e, c, u; //���_�A���ӓ_�A�����
	e = mPlayer.Position() + CVector(0.0f, 1.0f, -3.0f) * mPlayer.MatrixRotate();
	c = mPlayer.Position();
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.MatrixRotate();
	//�J�����ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//���f���r���[�s��擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//�t�s��̎擾
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);
	
	CTaskManager::Instance()->Delete();
	CTaskManager::Instance()->Render();
	mBackGround.Render();
	CCollisionManager::Instance()->Render();
}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse() {
	return mModelViewInverse;
}
