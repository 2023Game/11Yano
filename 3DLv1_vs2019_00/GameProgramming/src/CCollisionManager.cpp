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
	CCollider* task = (CCollider*)mHead.mpNext;//���݈ʒu��擪��
	while (task->mpNext) {
		CCollider* next = (CCollider*)task->mpNext;//���ݒn�̎������߂�
		while (next->mpNext) {
			//�����̏Փˏ���
			if (task->mpParent) {
				task->mpParent->Collision(task, next);
			}
			//����̏Փˏ���
			if (next->mpParent) {
				next->mpParent->Collision(next, task);
			}
			next = (CCollider*)next->mpNext;//�������߂�
		}
		task = (CCollider*)task->mpNext;//���ݒn�����ɂ���
	}
}

void CCollisionManager::Collision(CCollider* c, int range)
{
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�͈͂܂œǂݔ�΂�
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//�e�̏Փˏ����ďo��
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}