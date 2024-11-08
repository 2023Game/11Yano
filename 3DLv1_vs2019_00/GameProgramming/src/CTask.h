#pragma once
#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CCollisionManager;
//タスククラス//タスクリストの要素
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
public:
	virtual void Collision(){}
	//デフォルトコンストラクタ
	CTask()
		:mpNext(nullptr),mpPrev(nullptr),mPriority(0),mEnabled(true)
	{}
	//デストラクタvirtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask(){}
	virtual void Update(){}
	virtual void Render(){}
protected:
	int mPriority;//優先度
	bool mEnabled;//有効フラグ
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
};

#endif