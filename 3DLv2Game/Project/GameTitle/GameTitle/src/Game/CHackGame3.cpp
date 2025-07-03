#include "CHackGame3.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"

CHackGame3::CHackGame3()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
	, mIsClear(false)
{
	// ”wŒi¶¬
	mpBackground = new CImage
	(
		"UI/hack_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

CHackGame3::~CHackGame3()
{
}

void CHackGame3::Open()
{
	SetEnable(true);
	SetShow(true);
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

void CHackGame3::Close()
{
	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
}

bool CHackGame3::IsOpened() const
{
	return mIsOpened;
}

void CHackGame3::Update()
{
}

void CHackGame3::Render()
{
}

bool CHackGame3::IsClear() const
{
	return mIsClear;
}
