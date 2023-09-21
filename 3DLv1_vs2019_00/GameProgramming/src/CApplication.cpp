#include "CApplication.h"
#include "glut.h" //OpenGL
#include "CVector.h"

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
	
}

void CApplication::Update()
{
	CVector v0, v1, v2, n; //���_1�C2�C3�C�@���f�[�^�̍쐬
	n.Set(0.0f, 1.0f, 0.0f); //�@����������Őݒ肷��
	v0.Set(0.0f, 0.0f, 0.5f); //���_1�̍��W
	v1.Set(1.0f, 0.0f, 0.0f); //���_2�̍��W
	v2.Set(0.0f, 0.0f, -0.5f); //���_3�̍��W

	//���_�̐ݒ�
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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
}
