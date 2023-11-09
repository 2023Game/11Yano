#pragma once
#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include "CTask.h"

class CTaskManager {
public:
	virtual ~CTaskManager();//デストラクタ
	void Add(CTask* addTask);//リストに追加
	void Update();
	void Render();
	CTaskManager();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};

#endif