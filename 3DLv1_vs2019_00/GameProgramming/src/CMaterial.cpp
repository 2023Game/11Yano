#include "CMaterial.h"
#include <string.h> //mamset,strncpy�̃C���N���[�h
#include "glut.h"

int CMaterial::VertexNum()
{
	return mVertexNum;
}

void CMaterial::VertexNum(int num)
{
	num = mVertexNum;
}

//�R�s�[��str1�ɃR�s�[��str2�̕�����len�������܂ŃR�s�[����
char* strncpy(char* str1, const char* str2, int len)
{
	int i = 0;
	while (i < len && *str2 != '\0') //i��len��菬�������R�s�[�����I���łȂ��ԌJ��Ԃ�
	{
		*(str1 + i) = *str2; //�R�s�[��ɃR�s�[������
		str2++; //�R�s�[��������
		i++;
	}
	str1[i] = '\0'; //�R�s�[��̕�����ɏI���
	return str1; //�R�s�[��̐퓬�A�h���X��ԋp
}

CMaterial::CMaterial()
	:mVertexNum(0)
{
	memset(mName, 0, sizeof(mName)); //���O���[���Ŗ���
	memset(mDiffuse, 0, sizeof(mDiffuse)); //0�Ŗ��߂�
}

void CMaterial::Enabled()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse); //�g�U���̐ݒ�
	if (mTexture.Id()) //�e�N�X�`������
	{
		glEnable(GL_TEXTURE_2D); //�e�N�X�`�����g�p�\
		glBindTexture(GL_TEXTURE_2D, mTexture.Id()); //�e�N�X�`�����o�C���h
		glEnable(GL_BLEND); //�A���t�@�u�����h��L��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //�u�����h���@���w��
	}
}

char* CMaterial::Name()
{
	return mName;
}

void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN);
}

float* CMaterial::Diffuse()
{
	return mDiffuse;
}

void CMaterial::Disabled()
{
	if (mTexture.Id())
	{
		glDisable(GL_BLEND); //�A���t�@�u�����h����
		glBindTexture(GL_TEXTURE_2D, 0); //�e�N�X�`���̃o�C���h������
		glDisable(GL_TEXTURE_2D); //�e�N�X�`������
	}
}

CTexture* CMaterial::Texture()
{
	return &mTexture;
}