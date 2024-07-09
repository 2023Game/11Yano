#include "CApplication.h"
#include "glut.h" //OpenGL
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMaterial.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include <math.h>

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define MODEL_OBJ "res\\Col.obj","res\\Col.mtl" //���f���f�[�^�̎w��
#define MODEL_BACKGROUND "res\\BS1.obj", "res\\BS1.mtl"
#define MODEL_GROUND "res\\Yuka.obj", "res\\Yuka.mtl"//�����䂩

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
	Clear = false;
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.63f, 0.63f, 0.63f));
	mPlayer.Position(CVector(0.0f, 2.5f, 0.0f));
	mPlayer.Rotation(CVector(0.0f, 0.0f, 0.0f));
	CMatrix matrix;
	matrix.Point();
	mBackGround.Load(MODEL_BACKGROUND);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load(MODEL_OBJ);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	spUi = new CUi();//UI�N���X�̐���
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();
	//CCollisionManager::Instance()->Collision();
	CTaskManager::Instance()->Collision();
	CVector v0, v1, v2, n; //���_1�C2�C3�C�@���f�[�^�̍쐬
	n.Set(0.0f, 1.0f, 0.0f); //�@����������Őݒ肷��
	v0.Set(0.0f, 0.0f, 0.5f); //���_1�̍��W
	v1.Set(1.0f, 0.0f, 0.0f); //���_2�̍��W
	v2.Set(0.0f, 0.0f, -0.5f); //���_3�̍��W


	CVector e, c, u; //���_�A���ӓ_�A�����
	e = mPlayer.Position() + CVector(6.0f, 3.0f, 0.0f); 
	c = mPlayer.Position();
	u = CVector(0.0f, 1.0f, 0.0f);
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
	mBackGround.Render();

	CTaskManager::Instance()->Render();
	CCollisionManager::Instance()->Render();
	if (Clear == false)
	{
		spUi->Time(mTime++);
	}
	
	spUi->Render();//UI�̕`��

	//�������烊�X�^�[�g
	if (mPlayer.Position().Y() < -14.0f)
	{
		mPlayer.Position(CVector(0.0f, 1.5f, 0.0f));
	}
	if (mPlayer.Position().Y() <= -8.0f && mPlayer.Position().X()<-32.0f && mPlayer.Position().X() > -33.0f)
	{
		Clear = true;
		spUi->Clear();
	}
}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse() {
	return mModelViewInverse;
}

CUi* CApplication::spUi = nullptr;

CUi* CApplication::Ui()
{
	return spUi;//�C���X�^���X�̃|�C���^��Ԃ�
}

CApplication::~CApplication()
{
	delete spUi;
}