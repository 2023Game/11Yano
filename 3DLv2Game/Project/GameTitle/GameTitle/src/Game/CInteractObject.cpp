#include "CInteractObject.h"

CInteractObject::CInteractObject(
	ETaskPriority prio,
	int sortOrder,
	ETaskPauseType pause)
	: CXCharacter(ETag::eInteractObject, prio, sortOrder, pause)
	, mInteractStr("’²‚×‚é")
#if _DEBUG
	, mDebugName("mInteractObj")
#endif
{
}

CInteractObject::~CInteractObject()
{
}

bool CInteractObject::CanInteract() const
{
	return true;
}

std::string CInteractObject::GetInteractStr() const
{
	return mInteractStr;
}

#if _DEBUG
std::string CInteractObject::GetDebugName() const
{
	return mDebugName;
}

void CInteractObject::SetDebugName(std::string name)
{
	mDebugName = name;
}
#endif