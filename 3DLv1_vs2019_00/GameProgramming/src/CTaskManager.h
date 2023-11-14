#pragma once
#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include "CTask.h"

class CTaskManager {
public:
	void Delete();//�^�X�N�̍폜
	void Remove(CTask* task);//���X�g����폜
	virtual ~CTaskManager();//�f�X�g���N�^
	void Add(CTask* addTask);//���X�g�ɒǉ�
	void Update();
	void Render();
	CTaskManager();
protected:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
};

#endif