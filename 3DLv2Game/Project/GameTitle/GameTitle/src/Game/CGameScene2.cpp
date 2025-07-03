#include "CGameScene2.h"
#include "CSceneManager.h"
#include "CField2.h"
#include "CPlayer.h"
#include "CRobot.h"
#include "CGameCamera.h"
#include "CGameCamera2.h"
#include "CInput.h"
#include "CGameMenu.h"
#include "CHackGame.h"
#include "CBGMManager.h"
#include "CLineEffect.h"
#include "CNavManager.h"
#include "CInteractRobot.h"
#include "CDrone.h"
#include "CFade.h"
#include "CDoor.h"

//コンストラクタ
CGameScene2::CGameScene2()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
	, mpHackGame(nullptr)
	, mpTarget(nullptr)
{
}

//デストラクタ
CGameScene2::~CGameScene2()
{
	if (CNavManager::Instance())
	{
		delete CNavManager::Instance();
	}
}

//シーン読み込み
void CGameScene2::Load()
{
	// ゲーム画面はカーソル非表示
	CInput::ShowCursor(false);
	// 背景色設定
	System::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	CResourceManager::Load<CModel>("Field2", "Field\\stage2.obj");
	CResourceManager::Load<CModel>("Door", "Field\\Object\\door\\door.obj");
	CResourceManager::Load<CModel>("Goal", "Field\\Object\\goal.obj");
	CResourceManager::Load<CModel>("Intercom", "Field\\Object\\door\\intercom\\intercom.obj");
	CResourceManager::Load<CModelX>("Player", "Character\\Mryotaisu\\Mryotaisu.x");
	CResourceManager::Load<CModelX>("Robot", "Character\\Robot\\Robot.x");
	CResourceManager::Load<CModel>("Drone", "Field\\Object\\Cube.obj");
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	CResourceManager::Load<CTexture>("LightningBolt", "Effect\\lightning_bolt.png");
	CResourceManager::Load<CSound>("Hack", "Sound\\SE\\hack.wav");
	CResourceManager::Load<CSound>("Boot", "Sound\\SE\\boot.wav");
	CResourceManager::Load<CSound>("Shot", "Sound\\SE\\shot.wav");

	// ゲームBGMを読み込み
	CBGMManager::Instance()->Play(EBGMType::eGame);

	// 経路探索管理クラスを作成
	CNavManager* navMgr = new CNavManager();

	CField2* field = new CField2();

	player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(153.0f, 10.30f, 132.0f);
	player->SetScene(this);

	mpTarget = player;

	irobot = new CInteractRobot();
	irobot->Scale(1.0f, 1.0f, 1.0f);
	irobot->Position(-123.0f, 10.30f, -129.0f);
	irobot->SetScene(this);

	CRobot* robot = new CRobot
	(
		{
			CVector(164.0f, 10.30f, 48.0f),
			CVector(125.0f, 10.30f, 48.0f),

		}
	);
	robot->Position(164.0f, 10.30f, 48.0f);


	CRobot* robot2 = new CRobot
	(
		{
			CVector(125.0f, 10.30f, -8.0f),
			CVector(164.0f, 10.30f, -8.0f),
		}
	);
	robot2->Position(125.0f, 10.30f, -8.0f);

	CRobot* robot3 = new CRobot
	(
		{
			CVector(-80.0f, 10.30f, -18.0f),
			CVector(-123.0f, 10.30f, -18.0f),
			CVector(-123.0f, 10.30f, 77.0f),
			CVector(-80.0f, 10.30f, 77.0f),
		}
	);
	robot3->Position(-80.0f, 10.30f, -18.0f);

	CRobot* robot4 = new CRobot
	(
		{
			CVector(-80.0f, 10.30f, -18.0f),
			CVector(-123.0f, 10.30f, -18.0f),
			CVector(-123.0f, 10.30f, 77.0f),
			CVector(-80.0f, 10.30f, 77.0f),
		}
	);
	robot4->Position(-123.0f, 10.30f, 77.0f);

	CRobot* robot5 = new CRobot
	(
		{
			CVector(-43.0f, 10.30f, 14.0f),
		}
	);
	robot5->Position(-46.0f, 10.30f, 14.0f);

	CRobot* robot6 = new CRobot
	(
		{
			CVector(-43.0f, 10.30f, 38.0f),
		}
	);
	robot6->Position(-46.0f, 10.30f, 38.0f);

	CDrone* drone = new CDrone
	(
		{
			CVector(46.0f, 40.0f, -68.0f),
		}
	);
	drone->Position(46.0f, 40.0f, -68.0f);

	CDrone* drone2 = new CDrone
	(
		{
			CVector(91.0f, 40.0f, 148.0f),
			CVector(6.0f, 40.0f, 148.0f),
		}
	);
	drone2->Position(91.0f, 40.0f, 148.0f);

	CDrone* drone3 = new CDrone
	(
		{
			CVector(-97.0f, 40.0f, 136.0f),
			CVector(12.0f, 40.0f, 136.0f),
		}
	);
	drone3->Position(-97.0f, 40.0f, 136.0f);


	// CGameCamera2のテスト
	CVector atPos = mpTarget->Position() + CVector(0.0f, 10.0f, 0.0f);
	mainCamera = new CGameCamera2
	(
		atPos + CVector(0.0f, 0.0f, 20.0f),
		atPos
	);
	mainCamera->AddCollider(field->GetFieldCol());
	std::list<CDoor*> doors = field->GetDoors();
	for (CDoor* door : doors)
	{
		mainCamera->AddCollider(door->GetFieldCol());
	}
	mainCamera->SetFollowTargetTf(mpTarget);
	mainCamera->SetCurrent(true);

	// ゲームメニューを作成
	mpGameMenu = new CGameMenu();

	// UI
	mpImage = new CImage
	(
		"UI/fieldOfView.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);

	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(CVector2(1100.0f, 50.0f));

	mpImage->SetEnable(true);
	mpImage->SetShow(true);

	mpImage2 = new CImage
	(
		"UI/robot.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);

	mpImage2->SetCenter(mpImage2->GetSize() * 0.5f);
	mpImage2->SetPos(CVector2(1100.0f, 100.0f));

	mpImage2->SetEnable(false);
	mpImage2->SetShow(false);

}

//シーンの更新処理
void CGameScene2::Update()
{
	if (irobot->IsClear())
	{
		mpImage2->SetEnable(true);
		mpImage2->SetShow(true);
		if (CInput::PushKey('F'))
		{
			if (mpTarget == player)
			{
				mpTarget = irobot;
				ChangeCamera();
			}
			else if (mpTarget == irobot)
			{
				mpTarget = player;
				ChangeCamera();
			}
		}
	}
}

void CGameScene2::ChangeCamera()
{
	if (mpTarget == irobot)
	{
		CFade::FadeIn(0.5f);

		mpImage->Load("UI/return.png", false);
		mpImage2->Load("UI/fire.png", false);
		

		CVector atPos = mpTarget->Position() + CVector(0.0f, 15.0f, 0.0f);
		mainCamera->LookAt
		(
			atPos + CVector(0.0f, 0.0f, 20.0f),
			atPos,
			CVector::up
		);
		mainCamera->SetFollowTargetTf(mpTarget);
	}
	else if (mpTarget == player)
	{
		CFade::FadeIn(0.5f);

		mpImage->Load("UI/fieldOfView.png", false);
		mpImage2->Load("UI/robot.png", false);

		CVector atPos = mpTarget->Position() + CVector(0.0f, 10.0f, 0.0f);
		mainCamera->LookAt
		(
			atPos + CVector(0.0f, 0.0f, 20.0f),
			atPos,
			CVector::up
		);
		mainCamera->SetFollowTargetTf(mpTarget);
	}
}

CXCharacter* CGameScene2::CameraTarget() const
{
	return mpTarget;
}

