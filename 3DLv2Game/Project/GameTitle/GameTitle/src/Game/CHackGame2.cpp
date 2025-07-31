#include "CHackGame2.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CFont.h"
#include "CText.h"
#include "CPlayer2D.h"
#include "CEnemy2D.h"




CHackGame2::CHackGame2()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
	, mIsClear(false)

{
	// ”wŒi¶¬
	mpBackground = new CImage
	(
		"UI/space.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// ƒtƒHƒ“ƒgƒf[ƒ^‚ð¶¬
	mpFont = new CFont("res\\Font\\DotGothic16-Regular.ttf");
	mpFont->SetFontSize(40);
	mpFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpFont->SetLineLength(WINDOW_WIDTH);

	// ƒ^ƒCƒsƒ“ƒOƒƒS‚ÌƒeƒLƒXƒg‚ð¶¬
	mpLogos = new CText
	(
		mpFont, 40,
		CVector2(0.0f, 100.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(1.0f, 1.0f, 1.0f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpLogos->SetText("WASD : ˆÚ“®   SPACE : UŒ‚");
	mpLogos->SetPos(0.0f, 100.0f);
	mpLogos->SetEnableOutline(true);
	mpLogos->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	mpSE = CResourceManager::Get<CSound>("Hack");
	

	SetEnable(false);
	SetShow(false);
}

CHackGame2::~CHackGame2()
{
}

void CHackGame2::Open()
{
	mIsClear = false;
	mIsOpened = true;
	mpSE->Play(0.3f, true);
	SetEnable(true);
	SetShow(true);
	
	mpPlayer = new CPlayer2D(CVector2(400.0f,300.0f));
	mpEnemy = new CEnemy2D(CVector2(900.0f,200.0f), 1.0f);
	mpEnemy2 = new CEnemy2D(CVector2(900.0f, 500.0f), 1.8f);
	mpEnemy3 = new CEnemy2D(CVector2(1000.0f, 350.0f), 2.6f);
	
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

void CHackGame2::Close()
{
	mIsOpened = false;
	SetEnable(false);
	SetShow(false);
	if (!mpPlayer->IsKill()) {
		mpPlayer->Kill();
	}
	if (!mpEnemy->IsKill()) {
		mpEnemy->Kill();
	}
	if (!mpEnemy2->IsKill()) {
		mpEnemy2->Kill();
	}
	if (!mpEnemy3->IsKill()) {
		mpEnemy3->Kill();
	}

	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
}

bool CHackGame2::IsOpened() const
{
	return mIsOpened;
}

void CHackGame2::Update()
{
	mpBackground->Update();

	mpLogos->Update();

	if (mpEnemy->Killed() && mpEnemy2->Killed() && mpEnemy3->Killed())
	{
		mIsClear = true;
		Close();
		return;
	}
	if (mpPlayer->Killed())
	{
		Close();
		return;
	}
}

void CHackGame2::Render()
{
	// ”wŒi•`‰æ
	mpBackground->Render();
	mpLogos->Render();
	mpPlayer->Render();
}

bool CHackGame2::IsClear() const
{
	return mIsClear;
}
