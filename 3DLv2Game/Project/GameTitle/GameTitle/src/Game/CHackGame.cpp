#include "CHackGame.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CFont.h"
#include "CText.h"

#define MENU_ALPHA 0.5f

CHackGame::CHackGame()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
	, mIsClear(false)
	, mInputNum(1)
{
	// ”wŒi¶¬
	mpBackground = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);

	// ƒ^ƒCƒsƒ“ƒOƒƒS‚ÌƒtƒHƒ“ƒgƒf[ƒ^‚ğ¶¬
	mpLogoFont = new CFont("res\\Font\\KH-Dot-Dougenzaka-12.ttf");
	mpLogoFont->SetFontSize(256);
	mpLogoFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpLogoFont->SetLineLength(WINDOW_WIDTH);

	// ƒ^ƒCƒsƒ“ƒOƒƒS‚ÌƒeƒLƒXƒg‚ğ¶¬
	mpTypeLogo = new CText
	(
		mpLogoFont, 256,
		CVector2(0.0f, 0.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(1.0f, 1.0f, 1.0f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTypeLogo->SetText("TEST");
	mpTypeLogo->SetTextAlignV(ETextAlignV::eMiddle);
	mpTypeLogo->SetEnableOutline(true);
	mpTypeLogo->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	SetEnable(false);
	SetShow(false);
}

CHackGame::~CHackGame()
{
}

void CHackGame::Open()
{
	SetEnable(true);
	SetShow(true);
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

void CHackGame::Close()
{
	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
}

bool CHackGame::IsOpened() const
{
	return mIsOpened;
}

void CHackGame::Update()
{
	mpBackground->Update();
	mpTypeLogo->Update();

	char cord[] = "TEST";
	char c = cord[mInputNum];
	if (CInput::PushKey(c))
	{
		mInputNum++;
	}
	if (c == '\0')
	{
		mIsClear = true;
		Close();
	}
}

void CHackGame::Render()
{
	// ”wŒi•`‰æ
	mpBackground->Render();
	// ƒ^ƒCƒsƒ“ƒOƒƒS•`‰æ
	mpTypeLogo->Render();
}
