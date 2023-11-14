#include "CCharacter3.h"
#include "CApplication.h"



void CCharacter3::Model(CModel* m) {
	mpModel = m;
}

void CCharacter3::Render() {
	mpModel->Render(mMatrix);
}

CCharacter3::~CCharacter3() {
	CApplication::TaskManager()->Remove(this);
}

CCharacter3::CCharacter3() 
	:mpModel(nullptr)
{
	CApplication::TaskManager()->Add(this);
}