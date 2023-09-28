#include "CApplication.h"
#include "glut.h" //OpenGL
#include "CVector.h"
#include "CTriangle.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��

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
	mEye = CVector(1.0f, 2.0f, 3.0f);
}

void CApplication::Update()
{
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

	//���_�̐ݒ�
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//�`��J�n
	glBegin(GL_TRIANGLES);
	//�@���i�ʂ̌����j�̐ݒ�
	glNormal3f(n.X(),n.Y(),n.Z());
	//���_���W�̐ݒ�
	glVertex3f(v0.X(),v0.Y(),v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());
	//�@���ƒ��_�̐ݒ�
	n.Set(0.0f, 0.0f, 1.0f);
	v0.Set(0.5f, 0.0f, 0.0f);
	v1.Set(0.0f, 1.0f, 0.0f);
	v2.Set(-0.5f, 0.0f, 0.0f);
	//�O�p�`2�̕`��
	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	n.Set(1.0f, 0.0f, 0.0f);
	v0.Set(0.0f, 0.5f, 0.0f);
	v1.Set(0.0f, 0.0f, 1.0f);
	v2.Set(0.0f, -0.5f, 0.0f);

	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());
	
	//�`��I��
	glEnd();

	CTriangle t0;
	t0.Vertex(CVector(1.0f, 0.0f, 0.5f), CVector(2.0f, 0.0f, 0.0f), CVector(1.0f, 0.0f, -0.5f));
	t0.Normal(CVector(0.0f, 1.0f, 0.0f));
	t0.Render();
	CTriangle t1;
	t1.Vertex(CVector(0.5f,1.0f,0.0f), CVector(0.0f,2.0f,0.0f), CVector(-0.5f,1.0f,0.0f));
	t1.Normal(CVector(0.0f, 0.0f, 1.0f));
	t1.Render();
	CTriangle t2;
	t2.Vertex(CVector(0.0f,0.5f,1.0f), CVector(0.0f,0.0f, 2.0f), CVector(0.0f,-0.5f, 1.0f));
	t2.Normal(CVector(1.0f,0.0f, 0.0f));
	t2.Render();
}
