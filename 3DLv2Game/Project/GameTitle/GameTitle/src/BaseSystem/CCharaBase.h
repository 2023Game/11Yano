#pragma once
#include "CObjectBase.h"

/// <summary>
/// キャラクターのベースクラス
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame);
	virtual ~CCharaBase();
	virtual bool IsPlayerChase() const;
	virtual bool IsPlayerLost() const;
};
