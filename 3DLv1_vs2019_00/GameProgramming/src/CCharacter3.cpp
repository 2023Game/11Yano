#include "CCharacter3.h"

void CCharacter3::Model(CModel* m) {
	mpModel = m;
}

void CCharacter3::Render() {
	mpModel->Render(mMatrix);
}