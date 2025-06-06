#include "CVector.h"
#include <math.h>

void CVector::operator+=(const CVector& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
}

CVector CVector::operator+(const CVector &v) const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

CVector CVector::operator-(const CVector &v) const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

CVector CVector::operator*(const CMatrix& m) const
{
	return CVector(
		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
	);
}

CVector::CVector()
	:mX(0.0f)
	,mY(0.0f)
	,mZ(0.0f)
{
	
}

CVector::CVector(float x, float y, float z) {
	mX = x;
	mY = y;
	mZ = z;
}

void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

float CVector::X() const
{
	return mX;
}

float CVector::Y() const
{
	return mY;
}

float CVector::Z() const
{
	return mZ;
}

float CVector::Length() const {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);//sqrt関数で平方根を返す
}

float CVector::Dot(const CVector& v) const {
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

CVector CVector::Normalize() const {
	//ベクトルの大きさで割ったベクトルを返す（長さ１のベクトル）
	return *this * (1.0f / Length());
}

CVector CVector::Cross(const CVector& v) const {
	return CVector(mY * v.mZ - mZ * v.mY, mZ * v.mX - mX * v.mZ, mX * v.mY - mY * v.mX);
}

CVector CVector::operator*(const float& f) const {
	return CVector(mX * f, mY * f, mZ * f);
}

void CVector::X(float f)
{
	mX = f;
}
void CVector::Y(float f)
{
	mY = f;
}
void CVector::Z(float f)
{
	mZ = f;
}