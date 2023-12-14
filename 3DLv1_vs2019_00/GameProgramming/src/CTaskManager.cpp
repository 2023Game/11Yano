#include "CTaskManager.h"

CTaskManager::CTaskManager() {
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() {

}

void CTaskManager::Add(CTask* addTask) {
	CTask* task = mHead.mpNext;//mHead�̎����猟��
	//�D��x�̑傫�����ɓ����
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;//����
	}
	addTask->mpNext = task;//addTask�̎���task
	addTask->mpPrev = task->mpPrev;//addtask�̑O��task�̑O��
	addTask->mpPrev->mpNext = addTask;//addtask�̑O�̎���addtask��
	task->mpPrev = addTask;//task�̑O��addtask��
}

void CTaskManager::Update() {
	CTask* task = mHead.mpNext;//�擪����Ō�܂ŌJ��Ԃ�
	while (task->mpNext) {
		task->Update();
		task = task->mpNext;//����
	}
}

void CTaskManager::Render() {
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		task->Render();
		task = task->mpPrev;
	}
}

void CTaskManager::Remove(CTask* task) {
	task->mpPrev->mpNext = task->mpNext;//�^�X�N�̑O�̎����^�X�N�̎���
	task->mpNext->mpPrev = task->mpPrev;
}

void CTaskManager::Delete() {
	CTask* task = mHead.mpNext;//�擪����Ō�܂ŌJ��Ԃ�
	while (task->mpNext) {
		CTask* del = task;
		task = task->mpNext;//����
		if (del->mEnabled == false) {
			delete del;
		}
	}
}

CTaskManager* CTaskManager::mpInstance = nullptr;

CTaskManager* CTaskManager::Instance() {
	if (mpInstance == nullptr) {
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}