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
#include "CGround.h"
#include <math.h>

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define MODEL_OBJ "res\\Maru.obj","res\\Maru.mtl" //���f���f�[�^�̎w��
#define MODEL_BACKGROUND "res\\Stage1.obj", "res\\Stage1.mtl"
#define MODEL_GROUND "res\\Yuka.obj", "res\\Yuka.mtl"//�����䂩
//#define MOS_POS_X 400 //�}�E�X���W��X�␳
//#define MOS_POS_Y 300 //�}�E�X���W��Y�␳

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
	mModelGround.Load(MODEL_GROUND);
	new CGround(&mModelGround, CVector(0.0f, 1.0f, -10.0f), CVector(), CVector());
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
	mPlayer.Position(CVector(-30.0f, 1.5f, 0.0f));
	mPlayer.Rotation(CVector(0.0f, 270.0f, 0.0f));
	CMatrix matrix;
	matrix.Point();
	mBackGround.Load(MODEL_BACKGROUND);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load(MODEL_OBJ);
	
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	mColliderMesh.Set(nullptr, nullptr, &mModelGround);
	spUi = new CUi();//UI�N���X�̐���
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();
	//CCollisionManager::Instance()->Collision();
	CTaskManager::Instance()->Collision();
	//CVector v0, v1, v2, n; //���_1�C2�C3�C�@���f�[�^�̍쐬
	//n.Set(0.0f, 1.0f, 0.0f); //�@����������Őݒ肷��
	//v0.Set(0.0f, 0.0f, 0.5f); //���_1�̍��W
	//v1.Set(1.0f, 0.0f, 0.0f); //���_2�̍��W
	//v2.Set(0.0f, 0.0f, -0.5f); //���_3�̍��W


	CVector e, c, u; //���_�A���ӓ_�A�����
	e = mPlayer.Position() + CVector(0.2f, 1.0f, -3.0f) * mPlayer.MatrixRotate();// 
	c = mPlayer.Position();
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.MatrixRotate();//
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
	mModelGround.Render();
	CTaskManager::Instance()->Render();
	CCollisionManager::Instance()->Render();
	spUi->Render();//UI�̕`��


	//�������烊�X�^�[�g
	if (mPlayer.Position().Y() < -10.0f)
	{
		mPlayer.Position(CVector(0.0f, 1.5f, 0.0f));
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