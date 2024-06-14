#include "CCollisionManager.h"
#include "CCollider.h"

CCollisionManager* CCollisionManager::mpInstance = nullptr;

CCollisionManager* CCollisionManager::Instance() {
	if (mpInstance == nullptr) {
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

void CCollisionManager::Collision() {
	CCollider* task = (CCollider*)mHead.mpNext;//現在位置を先頭に
	while (task->mpNext) {
		CCollider* next = (CCollider*)task->mpNext;//現在地の次を求める
		while (next->mpNext) {
			//自分の衝突処理
			if (task->mpParent) {
				task->mpParent->Collision(task, next);
			}
			//相手の衝突処理
			if (next->mpParent) {
				next->mpParent->Collision(next, task);
			}
			next = (CCollider*)next->mpNext;//次を求める
		}
		task = (CCollider*)task->mpNext;//現在地を次にする
	}
}

void CCollisionManager::Collision(CCollider* c, int range)
{
	//現在位置を先頭にする
	CCollider* task = (CCollider*)mHead.mpNext;
	//範囲まで読み飛ばし
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//現在位置を次にする
		task = (CCollider*)task->mpNext;
	}
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//親の衝突処理呼出し
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//現在位置を次にする
		task = (CCollider*)task->mpNext;
	}
}