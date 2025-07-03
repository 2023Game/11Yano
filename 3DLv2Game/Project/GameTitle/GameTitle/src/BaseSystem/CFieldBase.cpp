#include "CFieldBase.h"

CFieldBase* CFieldBase::spInstance = nullptr;

CFieldBase::CFieldBase()
{
	spInstance = this;
}

CFieldBase::~CFieldBase()
{
}

CFieldBase* CFieldBase::Instance()
{
	return spInstance;
}

bool CFieldBase::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	return false;
}
