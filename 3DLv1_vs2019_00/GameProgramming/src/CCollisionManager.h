#pragma once
#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#define COLLISIONRANGE 30
#include "CTaskManager.h"
#include "CCollider.h"

class CCollisionManager :public CTaskManager
{
public:
	void Collision();//�Փˏ���
	void Collision(CCollider *c, int range);
	static CCollisionManager* Instance();//�C���X�^���X�̎擾
private:
	static CCollisionManager* mpInstance;//�}�l�[�W���̃C���X�^���X
};

#endif