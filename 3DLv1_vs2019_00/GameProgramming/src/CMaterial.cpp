#include "CMaterial.h"
#include <string.h> //mamset,strncpy�̃C���N���[�h
#include "glut.h"

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
{
	memset(mName, 0, sizeof(mName)); //���O���[���Ŗ���
	memset(mDiffuse, 0, sizeof(mDiffuse)); //0�Ŗ��߂�
}

void CMaterial::Enebled()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse); //�g�U���̐ݒ�
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