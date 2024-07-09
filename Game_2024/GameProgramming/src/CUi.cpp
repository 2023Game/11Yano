#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"

void CUi::Clear()
{
	CCamera::Start(0, 800, 0, 600);//2D�`��J�n
	//�`��F�̐ݒ�i�΂̔������j
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	//������ҏW�G���A�̍쐬
	char buf[64];
	sprintf(buf, "GAME CLEAR!!");
	mFont.Draw(36, 300, 18, 36, buf);
	
	CCamera::End();
	
}

void CUi::Over()
{
	mFont.Draw(36, 300, 18, 36, "GAME OVER!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");
}

void CUi::Start()
{
	mFont.Draw(36, 300, 18, 36, "START PUSH ENTER KEY!");
}

CUi::CUi()
	: mTime(0)
	,mPosY(0.0f)
	,mPosX(0.0f)
	,mPosZ(0.0f)
{
	mFont.Load("FontWhite.png", 1, 64);
}

void CUi::Time(int time)
{
	mTime = time;
}

void CUi::Render()
{
	CCamera::Start(0, 800, 0, 600);//2D�`��J�n
	//�`��F�̐ݒ�i�΂̔������j
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	//������ҏW�G���A�̍쐬
	char buf[64];
	sprintf(buf, "TIME:%03d", mTime);
	mFont.Draw(620, 580, 10, 20, buf);
	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "PX:%7.2f", mRotX);
	//������̕`��
	mFont.Draw(500, 330, 8, 16, buf);
	sprintf(buf, "PY:%7.2f", mRotY);
	mFont.Draw(500, 300, 8, 16, buf);
	sprintf(buf, "PZ:%7.2f", mRotZ);
	mFont.Draw(500, 270, 8, 16, buf);
	CCamera::End();
}

void CUi::PosY(float f)
{
	mPosY = f;
}

void CUi::PosX(float f)
{
	mPosX = f;
}

void CUi::PosZ(float f)
{
	mPosZ = f;
}

void CUi::RotY(float f)
{
	mRotY = f;
}

void CUi::RotX(float f)
{
	mRotX = f;
}

void CUi::RotZ(float f)
{
	mRotZ = f;
}