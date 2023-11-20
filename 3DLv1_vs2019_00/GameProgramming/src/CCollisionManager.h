#pragma once
#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#include "CTaskManager.h"

class CCollisionManager :public CTaskManager
{
public:
	static CCollisionManager* Instance();//インスタンスの取得
private:
	static CCollisionManager* mpInstance;//マネージャのインスタンス
};

#endif