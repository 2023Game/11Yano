#include "CCollisionManager.h"

CCollisionManager* CCollisionManager::mpInstance = nullptr;

CCollisionManager* CCollisionManager::Instance() {
	if (mpInstance == nullptr) {
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}