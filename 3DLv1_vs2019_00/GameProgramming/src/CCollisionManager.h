#pragma once
#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#include "CTaskManager.h"

class CCollisionManager :public CTaskManager
{
public:
	static CCollisionManager* Instance();//�C���X�^���X�̎擾
private:
	static CCollisionManager* mpInstance;//�}�l�[�W���̃C���X�^���X
};

#endif