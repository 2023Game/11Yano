#pragma once
#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include "CTask.h"

class CTaskManager {
public:
	static CTaskManager* Instance();//インスタンスの取得
	void Delete();//タスクの削除
	void Remove(CTask* task);//リストから削除
	virtual ~CTaskManager();//デストラクタ
	void Add(CTask* addTask);//リストに追加
	void Update();
	void Render();

protected:
	CTaskManager();	
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
private:
	static CTaskManager* mpInstance;
};

#endif