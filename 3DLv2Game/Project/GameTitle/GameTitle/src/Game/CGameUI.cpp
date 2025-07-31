#include "CGameUI.h"
#include "CPlayer.h"
#include "CHackGame.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CRobot.h"
#include <cmath>
#include "CGameScene.h"
#include "CBlackOut.h"
#include "CInteractRobot.h"

CGameUI::CGameUI()
	: mAlphaTimer(0.0f)
{
	SetPauseType(ETaskPauseType::eDefault);

	mpAlert = new CImage
	(
		"UI/red.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);
	mpAlert->SetAlpha(0.0f);
	mpAlert->SetCenter(mpAlert->GetSize() * 0.5f);
	mpAlert->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpAlert->SetShow(true);

	// UI(停電)
	mpBlack = new CImage
	(
		"UI/black_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);
	mpBlack->SetCenter(mpBlack->GetSize() * 0.5f);
	mpBlack->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBlack->SetAlpha(0.8f);
	mpBlack->SetShow(false);

	// UI(ハッキングなど)
	mpInter = new CImage
	(
		"UI/NextStage.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);
	mpInter->SetCenter(mpInter->GetSize() * 0.5f);
	mpInter->SetPos(CVector2(930.0f, 350.0f));
	mpInter->SetShow(false);

	// UI(視野範囲表示)
	mpUI1 = new CImage
	(
		"UI/fieldOfView.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);

	mpUI1->SetCenter(mpUI1->GetSize() * 0.5f);
	mpUI1->SetPos(CVector2(1100.0f, 50.0f));
	mpUI1->SetShow(true);

	// UI(ロボット操作)
	mpUI2 = new CImage
	(
		"UI/robot.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);

	mpUI2->SetCenter(mpUI2->GetSize() * 0.5f);
	mpUI2->SetPos(CVector2(1100.0f, 120.0f));
	mpUI2->SetShow(false);
}

CGameUI::~CGameUI()
{
	if (mpInter != nullptr)
	{
		mpInter = nullptr;
	}
	if (mpUI1 != nullptr)
	{
		mpUI1 = nullptr;
	}

}

void CGameUI::Update()
{

	CInteractRobot* irobot = CInteractRobot::Instance();
	CPlayer* player = CPlayer::Instance();
	CGameScene* scene = CGameScene::Instance();
	std::list<CCharaBase*> enemys = scene->GetEnemys();
	for (CCharaBase* enemy : enemys)
	{
		if (enemy == nullptr || enemy->IsKill()) continue;

		if (enemy->IsPlayerChase())
		{
			UpdateAlert();
		}
		else if (enemy->IsPlayerLost())
		{
			mpAlert->SetAlpha(0.0f);
		}
	}

	if (scene->CameraTarget() == irobot && irobot->IsClear())
	{
		mpUI1->Load("UI/return.png", false);
		mpUI2->Load("UI/fire.png", false);
		mpUI2->SetShow(true);
	}
	else if (scene->CameraTarget() == player && irobot->IsClear())
	{
		mpUI1->Load("UI/fieldOfView.png", false);
		mpUI2->Load("UI/robot.png", false);
		mpUI2->SetShow(true);
	}

	// UI管理
	if (player->Instance() != nullptr)
	{
		switch (player->SetImage())
		{
		case 0:
			mpInter->SetShow(false);
			mpUI1->SetShow(true);
			break;
		case 1:
			mpInter->Load("UI/NextStage.png");
			mpInter->SetShow(true);
			mpUI1->SetShow(true);
			break;
		case 2:
			mpInter->Load("UI/exit.png");
			mpInter->SetShow(true);
			mpUI1->SetShow(true);
			break;
		case 3:
			mpInter->Load("UI/hacking.png");
			// ポーズ中(ハッキング中)はUI非表示
			if (CTaskManager::Instance()->IsPaused())
			{
				mpInter->SetShow(false);
				mpUI1->SetShow(false);
			}
			else
			{
				mpInter->SetShow(true);
				mpUI1->SetShow(true);
			}
			break;
		}
	}

	// 停電処理
	CBlackOut* black = CBlackOut::Instance();
	if (black->IsBlack())
	{
		mpBlack->SetShow(true);
	}
	else if (!black->IsBlack())
	{
		mpBlack->SetShow(false);
	}
}

void CGameUI::Render()
{
}

void CGameUI::UpdateAlert()
{
	const float blinkSpeed = 2.0f; // 秒間何回点滅するか
	mAlphaTimer += Times::DeltaTime() * blinkSpeed * 3.1415f; // ラジアン換算
	if (mAlphaTimer > 3.1415f * 2.0f) mAlphaTimer -= 3.1415f * 2.0f;

	// sin 波でアルファ値0〜0.4の範囲を作る
	float alpha = (std::sin(mAlphaTimer) + 1.0f) * 0.2f;
	mpAlert->SetAlpha(alpha);
}
