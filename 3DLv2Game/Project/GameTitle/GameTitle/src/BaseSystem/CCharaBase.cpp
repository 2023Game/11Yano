#include "CCharaBase.h"

CCharaBase::CCharaBase(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CObjectBase(tag, prio, sortOrder, pause)
{
}

CCharaBase::~CCharaBase()
{
}

bool CCharaBase::IsPlayerChase() const
{
	return false;
}

bool CCharaBase::IsPlayerLost() const
{
	return false;
}
