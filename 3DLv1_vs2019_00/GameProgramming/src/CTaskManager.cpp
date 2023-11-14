#include "CTaskManager.h"

CTaskManager::CTaskManager() {
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() {

}

void CTaskManager::Add(CTask* addTask) {
	CTask* task = &mTail;//mTail�̑O�ɒǉ�
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
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		task->Render();
		task = task->mpNext;
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