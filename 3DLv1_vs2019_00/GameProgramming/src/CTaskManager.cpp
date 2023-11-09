#include "CTaskManager.h"

CTaskManager::CTaskManager() {
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() {

}

void CTaskManager::Add(CTask* addTask) {
	CTask* task = &mTail;//mTailの前に追加
	addTask->mpNext = task;//addTaskの次をtask
	addTask->mpPrev = task->mpPrev;//addtaskの前をtaskの前に
	addTask->mpPrev->mpNext = addTask;//addtaskの前の次をaddtaskに
	task->mpPrev = addTask;//taskの前をaddtaskに
}

void CTaskManager::Update() {
	CTask* task = mHead.mpNext;//先頭から最後まで繰り返し
	while (task->mpNext) {
		task->Update();
		task = task->mpNext;//次へ
	}
}

void CTaskManager::Render() {
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		task->Render();
		task = task->mpNext;
	}
}