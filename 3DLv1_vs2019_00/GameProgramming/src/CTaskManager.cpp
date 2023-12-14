#include "CTaskManager.h"

CTaskManager::CTaskManager() {
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() {

}

void CTaskManager::Add(CTask* addTask) {
	CTask* task = mHead.mpNext;//mHeadの次から検索
	//優先度の大きい順に入れる
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;//次へ
	}
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
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		task->Render();
		task = task->mpPrev;
	}
}

void CTaskManager::Remove(CTask* task) {
	task->mpPrev->mpNext = task->mpNext;//タスクの前の次をタスクの次に
	task->mpNext->mpPrev = task->mpPrev;
}

void CTaskManager::Delete() {
	CTask* task = mHead.mpNext;//先頭から最後まで繰り返し
	while (task->mpNext) {
		CTask* del = task;
		task = task->mpNext;//次へ
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