#pragma once
#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include "CTask.h"

class CTaskManager {
public:
	static CTaskManager* Instance();//�C���X�^���X�̎擾
	void Delete();//�^�X�N�̍폜
	void Remove(CTask* task);//���X�g����폜
	virtual ~CTaskManager();//�f�X�g���N�^
	void Add(CTask* addTask);//���X�g�ɒǉ�
	void Update();
	void Render();

protected:
	CTaskManager();	
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
private:
	static CTaskManager* mpInstance;
};

#endif