#include "CMatrix.h"
#include <stdio.h>

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