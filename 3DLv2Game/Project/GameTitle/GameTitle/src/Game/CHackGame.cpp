#include "CHackGame.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CFont.h"
#include "CText.h"
#include <ctime>

CHackGame* CHackGame::spInstance = nullptr;

CHackGame* CHackGame::Instance()
{
	return spInstance;
}

CHackGame::CHackGame()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
	, mIsClear(false)
	, mInputNum(0)
{
	spInstance = this;
	// �w�i����
	mpBackground = new CImage
	(
		"UI/hack_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	

	// �^�C�s���O���S�̃t�H���g�f�[�^�𐶐�
	mpLogoFont = new CFont("res\\Font\\KH-Dot-Dougenzaka-12.ttf");
	mpLogoFont->SetFontSize(100);
	mpLogoFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpLogoFont->SetLineLength(WINDOW_WIDTH);

	// �^�C�s���O���S�̃t�H���g�f�[�^�𐶐�
	mpLogoFontBg = new CFont("res\\Font\\KH-Dot-Dougenzaka-12.ttf");
	mpLogoFontBg->SetFontSize(200);
	mpLogoFontBg->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpLogoFontBg->SetLineLength(WINDOW_WIDTH);
	
	mpSE = CResourceManager::Get<CSound>("Hack");

	SetEnable(false);
	SetShow(false);
}

CHackGame::~CHackGame()
{
	if (spInstance != nullptr)
	{
		spInstance = nullptr;
	}
}

void CHackGame::Open()
{
	mpSE->Play(0.3f, true);
	SetEnable(true);
	SetShow(true);

	std::srand((unsigned int)std::time(nullptr));
	int index = std::rand() % mWordList.size();
	mCurrentWord = mWordList[index];

	// �^�C�s���O���S�̃e�L�X�g�𐶐�
	mpTypeLogo = new CText
	(
		mpLogoFont, 50,
		CVector2(0.0f, 0.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(0.0f, 0.0f, 0.0f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTypeLogo->SetText(mCurrentWord.c_str());
	mpTypeLogo->SetPos(0.0f, 200.0f);
	mpTypeLogo->SetEnableOutline(true);
	mpTypeLogo->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	// �ł��Ă��镶��
	mpTypedLogo = new CText(
		mpLogoFontBg, 256,
		CVector2(0.0f, 0.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(1.0f, 1.0f, 0.2f), // ���F
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTypedLogo->SetPos(0.0f, 0.0f);
	mpTypedLogo->SetTextAlignV(ETextAlignV::eMiddle);
	

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
	//mpPlayer->Update();
	mpBackground->Update();
	mpTypeLogo->Update();

	if (mInputNum < mCurrentWord.length())
	{
		char c = mCurrentWord[mInputNum];
		if (CInput::PushKey(c))
		{
			mInputNum++;
		}
	}
	else
	{
		mIsClear = true;
		Close();
	}
	static float caretTimer = 0.0f;
	static bool caretVisible = true;

	caretTimer += Times::DeltaTime(); // �o�ߎ��Ԃ̎擾

	if (caretTimer >= 0.5f) {  // 0.5�b���Ƃɓ_��
		caretTimer = 0.0f;
		caretVisible = !caretVisible;
	}

	std::string typedPart = mCurrentWord.substr(0, mInputNum);
	if (caretVisible) {
		typedPart += '|';
	}
	mpTypedLogo->SetText(typedPart.c_str());
}

void CHackGame::Render()
{
	
	// �w�i�`��
	mpBackground->Render();
	// �^�C�s���O���S�`��
	mpTypeLogo->Render();
	mpTypedLogo->Render();
}

bool CHackGame::IsClear() const
{
	return mIsClear;
}
