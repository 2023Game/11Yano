#include "CHackGame3.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CBlock.h"

CHackGame3::CHackGame3()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
	, mIsClear(false)
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
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	SetEnable(false);
	SetShow(false);
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

	const int ROWS = 9;
	const int COLS = 12;

	int maze[ROWS][COLS] = {
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,1,0,1,0,1},
		{1,1,1,1,1,1,0,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (maze[row][col] == 1)
			{

				new CBlock(300 + 50 * col, 150 + 50 * row);
			}
		}
	}

	mpTaisu = new CMryotaisu(CVector2(200.0f, 300.0f));
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
	mpBackground->Render();
}

bool CHackGame3::IsClear() const
{
	return mIsClear;
}
