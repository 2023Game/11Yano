#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"
#include <ctype.h>

CModelX::CModelX()
	:mpPointer(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}

void CModelX::Load(char* file)
{
	//�t�@�C���T�C�Y�擾

	FILE* fp;//�t�@�C���|�C���^�̍쐬
	fp = fopen(file, "rb");//�t�@�C���I�[�v��
	if (fp == NULL)
	{//�G���[�`�F�b�N
		printf("fopen error:%s\n", file);
		return;
	}
	//�t�@�C���̍Ō�ֈړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y�{1�o�C�g���̗̈���m��
	char* buf = mpPointer = new char[size + 1];
	//�ӂ����邩��3D���f���̃f�[�^��ǂݍ���
	
	//�t�@�C���̐擪�ֈړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���̃f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ō��\0��ݒ肷��i������̏I�[�j
	buf[size] = '\0';
	
	fclose(fp);//�t�@�C���N���[�Y
	//������Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0')
	{
		GetToken();//�P��擾
		//�P�ꂪFrame�̏ꍇ
		if (strcmp(mToken, "Frame") == 0)
		{
			//�t���[���쐬
			new CModelXFrame(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);//�m�ۂ����̈���������
}

char* CModelX::GetToken()
{
	char* p = mpPointer;
	char* q = mToken;
	//�^�u(\t)��( )���s(\r)(\n)�C�G�h�̋�؂蕶���ȊO�ɂȂ�܂œǂݔ�΂�
	while (*p != '\0' && IsDelimiter(*p))p++;
	if (*p == '{' || *p == '}')
	{
		//mToken�ɑ�������̕�����
		*q++ = *p++;
	}
	else
	{
		//�^�u(\t)��( )���s(\r)(\n)�C�G�h�̋�؂蕶���A
		//�܂��́A}�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0' && !IsDelimiter(*p) && *p != '}')
			*q++ = *p++;
	}

	*q = '\0';//mToken�̍Ō��\0����
	mpPointer = p;//���̓ǂݍ��ރ|�C���g���X�V����

	//����mToken��//�̏ꍇ�̓R�����g�Ȃ̂ŊJ�Ƃ܂œǂݔ�΂�
	/*
	strcmp(������P,������Q)
	������P�ƕ�����Q���ЂƂ����Ƃ��O��Ԃ�
	������P�ƕ�����Q���������Ȃ��Ƃ��O�ȊO��Ԃ�
	*/
	if (!strcmp("//", mToken))
	{
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p))p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾(�ċA�ďo��)
		return GetToken();
	}
	return mToken;
}

bool CModelX::IsDelimiter(char c)
{
	//isspace(c)
	//c���󔒕����Ȃ�O�ȊO��Ԃ�
	if (isspace(c) != 0)
		return true;
	/*
	* strchr(������,����)
	* ������ɕ������܂܂�Ă���ƌ������������փ|�C���^�Ԃ�
	* ������Ȃ���NULL�Ԃ�
	*/
	if (strchr(",;\"", c) != NULL)
		return true;
	//��؂蕶���łȂ�
	return false;
}

CModelX::~CModelX()
{
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
}

void CModelX::SkipNode()
{
	//�������I�������I��
	while (*mpPointer != '\0')
	{
		GetToken();//���̒P��擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	//�������I��邩�J�E���g���O�ɂȂ�����I��
	while (*mpPointer != '\0' && count > 0)
	{
		GetToken();//���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{'))count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}'))count--;
	}
}



CModelXFrame::~CModelXFrame()
{
	//�q�t���[�������ׂĊJ������
	std::vector<CModelXFrame*>::iterator itr;
	for (itr = mChild.begin(); itr != mChild.end(); itr++)
	{
		delete* itr;
	}
	//���O�G���A���J������
	SAFE_DELETE_ARRAY(mpName);
}

CModelXFrame::CModelXFrame(CModelX* model)
	:mpName(nullptr)
	, mIndex(0)
{
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P��i�t���[�����̗\��j���擾����
	model->GetToken();//frame name
	//�t���[�������G���A���m��
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[���������ҁ[
	strcpy(mpName, model->mToken);
	//���̒P��i�o�̗\��j���擾����
	model->GetToken();//{
	//�������Ȃ��Ȃ�����I���
	while (*model->mpPointer != '\0')
	{
		//���̒P��擾
		model->GetToken();//frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}')) break;
		//�V���ȃt���[���ȏꍇ�͎q�t���[���ɒǉ�
		if (strcmp(model->mToken,"Frame")==0)
		{
			//�t���[���쐬���q�t���[���̔z��ɒǉ�
			mChild.push_back(new CModelXFrame(model));
		}
		else
		{
			//��L�ȊO�͓ǂݔ�΂�
			model->SkipNode();
		}
	}
	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	printf("%s\n", mpName);
#endif
}