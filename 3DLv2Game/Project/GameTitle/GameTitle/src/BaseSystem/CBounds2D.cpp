#include "CBounds2D.h"
#include <algorithm>

CBounds2D::CBounds2D()
{
}

CBounds2D::~CBounds2D()
{
}

void CBounds2D::SetRange(const CVector2& min, const CVector2& max)
{
	mMin = min;
	mMax = max;
}

void CBounds2D::SetPos(const CVector2& center, const CVector2& size)
{
	mMin = center - size * 0.5f;
	mMax = center + size * 0.5f;
}

void CBounds2D::Min(const CVector2& min)
{
	mMin = min;
}

const CVector2& CBounds2D::Min() const
{
	return mMin;
}

void CBounds2D::Max(const CVector2& max)
{
	mMax = max;
}

const CVector2& CBounds2D::Max() const
{
	return mMax;
}

void CBounds2D::Center(const CVector2& center)
{
	SetPos(center, Size());
}

CVector2 CBounds2D::Center() const
{
	return (mMax + mMin) * 0.5f;
}

void CBounds2D::Size(const CVector2& size)
{
	SetPos(Center(), size);
}

CVector2 CBounds2D::Size() const
{
	return (mMax - mMin) * 0.5f;
}

bool CBounds2D::Intersect(const CBounds2D& b0, const CBounds2D& b1)
{
	return b0.mMin.X() <= b1.mMax.X()
		&& b0.mMax.X() >= b1.mMin.X()
		&& b0.mMin.Y() <= b1.mMax.Y()
		&& b0.mMax.Y() >= b1.mMin.Y();
}

CBounds2D CBounds2D::GetCircleBounds(const CVector2& pos, float rad)
{
	CVector2 min = pos - CVector2(1.0f, 1.0f) * rad;
	CVector2 max = pos + CVector2(1.0f, 1.0f) * rad;

	CBounds2D ret;
	ret.SetRange(min, max);
	return ret;
}

CBounds2D CBounds2D::GetTriangleBounds(const CVector2& v0, const CVector2& v1, const CVector2& v2)
{
	CVector2 min(
		std::min(std::min(v0.X(), v1.X()), v2.X()),
		std::min(std::min(v0.Y(), v1.Y()), v2.Y())
	);
	CVector2 max(
		std::max(std::max(v0.X(), v1.X()), v2.X()),
		std::max(std::max(v0.Y(), v1.Y()), v2.Y())
	);

	CBounds2D bounds;
	bounds.SetRange(min, max);
	return bounds;
}
