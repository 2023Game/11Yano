#include "CCharacter3.h"
#include "CApplication.h"



void CCharacter3::Model(CModel* m) {
	mpModel = m;
}

void CCharacter3::Render() {
	mpModel->Render(mMatrix);
}

CCharacter3::~CCharacter3() {
	CTaskManager::Instance()->Remove(this);
}

CCharacter3::CCharacter3() 
	:mpModel(nullptr)
{
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority) 
	:mpModel(nullptr)
{
	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}