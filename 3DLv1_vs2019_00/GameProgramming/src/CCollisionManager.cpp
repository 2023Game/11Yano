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
	CCollider* task = (CCollider*)mHead.mpNext;//Œ»ÝˆÊ’u‚ðæ“ª‚É
	while (task->mpNext) {
		CCollider* next = (CCollider*)task->mpNext;//Œ»Ý’n‚ÌŽŸ‚ð‹‚ß‚é
		while (next->mpNext) {
			//Ž©•ª‚ÌÕ“Ëˆ—
			if (task->mpParent) {
				task->mpParent->Collision(task, next);
			}
			//‘ŠŽè‚ÌÕ“Ëˆ—
			if (next->mpParent) {
				next->mpParent->Collision(next, task);
			}
			next = (CCollider*)next->mpNext;//ŽŸ‚ð‹‚ß‚é
		}
		task = (CCollider*)task->mpNext;//Œ»Ý’n‚ðŽŸ‚É‚·‚é
	}
}