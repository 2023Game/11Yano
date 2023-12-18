#pragma once
#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#define COLLISIONRANGE 30
#include "CTaskManager.h"
#include "CCollider.h"

class CCollisionManager :public CTaskManager
{
public:
	void Collision();//衝突処理
	void Collision(CCollider *c, int range);
	static CCollisionManager* Instance();//インスタンスの取得
private:
	static CCollisionManager* mpInstance;//マネージャのインスタンス
};

#endif