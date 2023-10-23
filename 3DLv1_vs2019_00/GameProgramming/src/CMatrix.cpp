#define _USE_MATH_DEFINES

#include "CMatrix.h"
#include <stdio.h>
#include <math.h>

void CMatrix::Point() {
	printf("%10f %10f %10f %10f\n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f %10f %10f %10f\n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f %10f %10f %10f\n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f\n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
}

CMatrix::CMatrix() {
	Identity();
}

CMatrix CMatrix::Identity() {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) //‚·‚×‚Ä‚Ì—v‘f‚É‚O‚ð‘ã“ü
		{
			mM[i][j] = 0.0f;
		}
	}
	mM[0][0] = 1.0f; mM[1][1] = 1.0f; mM[2][2] = 1.0f; mM[3][3] = 1.0f;
	return *this; //‚±‚Ìs—ñ‚ð•Ô‚·
}

CMatrix CMatrix::Scale(float sx, float sy, float sz)
{
	Identity();
	mM[0][0] = sx; mM[1][1] = sy; mM[2][2] = sz; mM[3][3] = 1.0f;
	return *this;
}

float CMatrix::M(int r, int c) const
{
	return mM[r][c];
}

CMatrix CMatrix::RotateY(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[0][0] = mM[2][2] = cosf(rad);
	mM[0][2] = -sinf(rad);
	mM[2][0] = -mM[0][2];
	return *this;
}
CMatrix CMatrix::RotateZ(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[0][0] = mM[1][1] = cosf(rad);
	mM[0][1] = sinf(rad);
	mM[1][0] = -mM[0][1];
	return *this;
}

CMatrix CMatrix::RotateX(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
	return *this;
}