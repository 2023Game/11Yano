#include "CGameScene.h"
#include "CSceneManager.h"
#include "CField.h"
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
#include "CDoor.h"

CGameScene* CGameScene::spInstance = nullptr;

CGameScene* CGameScene::Instance()
{
	return spInstance;
}

//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
	, mpHackGame(nullptr)
	, mpTarget(nullptr)
{
	//インスタンスの設定
	spInstance = this;
}

//デストラクタ
CGameScene::~CGameScene()
{
	if (CNavManager::Instance())
	{
		delete CNavManager::Instance();
	}
}

//シーン読み込み
void CGameScene::Load()
{
	// ゲーム画面はカーソル非表示
	CInput::ShowCursor(false);
	// 背景色設定
	System::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	CResourceManager::Load<CModel>("Field", "Field\\stage1.obj");
	CResourceManager::Load<CModel>("Door", "Field\\Object\\door\\door.obj");
	CResourceManager::Load<CModel>("Goal", "Field\\Object\\goal.obj");
	CResourceManager::Load<CModel>("Intercom", "Field\\Object\\door\\intercom\\intercom.obj");
	CResourceManager::Load<CModelX>("Player", "Character\\Mryotaisu\\Mryotaisu.x");
	CResourceManager::Load<CModelX>("Robot", "Character\\Robot\\Robot.x");
	CResourceManager::Load<CModel>("Drone", "Field\\Object\\Cube.obj");
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	CResourceManager::Load<CSound>("Hack", "Sound\\SE\\hack.wav");
	CResourceManager::Load<CSound>("Boot", "Sound\\SE\\boot.wav");
	CResourceManager::Load<CSound>("Shot", "Sound\\SE\\shot.wav");


	// ゲームBGMを読み込み
	CBGMManager::Instance()->Play(EBGMType::eGame);

	// 経路探索管理クラスを作成
	CNavManager* navMgr = new CNavManager();

	CField* field = new CField();

	player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(153.0f, 10.30f, 132.0f);
	player->SetScene(this);

	mpTarget = player;

	CRobot* robot = new CRobot
	(
		{
			CVector(167.0f, 10.0f, 76.0f),
			CVector(114.0f, 10.0f, 76.0f),
			CVector(114.0f, 10.0f, -31.0f),
			CVector(167.0f, 10.0f, -31.0f),
		}
	);
	robot->Position(167.0f, 10.30f, 76.0f);

	CRobot* robot2 = new CRobot
	(
		{
			CVector(107.0f, 10.0f, -31.0f),
			CVector(52.0f, 10.0f, -31.0f),
			CVector(52.0f, 10.0f, 76.0f),
			CVector(107.0f, 10.0f, 76.0f),
		}
	);
	robot2->Position(107.0f, 10.0f, -31.0f);

	CRobot* robot3 = new CRobot
	(
		{
			CVector(43.0f, 10.0f, 76.0f),
			CVector(-15.0f, 10.0f, 76.0f),
			CVector(-15.0f, 10.0f, -31.0f),
			CVector(43.0f, 10.0f, -31.0f),
		}
	);
	robot3->Position(43.0f, 10.0f, 76.0f);

	CDrone* drone = new CDrone
	(
		{
			CVector(-15.0f, 40.0f, -94.0f),
		}
	);
	drone->Position(-15.0f, 40.0f, -94.0f);
	CDrone* drone2 = new CDrone
	(
		{
			CVector(-75.0f, 40.0f, -121.0f),
			CVector(-75.0f, 40.0f, -69.0f),
		}
	);
	drone2->Position(-75.0f, 40.0f, -121.0f);
	CDrone* drone3 = new CDrone
	(
		{
			CVector(63.0f, 40.0f, -69.0f),
			CVector(63.0f, 40.0f, -121.0f),
		}
	);
	drone3->Position(68.0f, 40.0f, -69.0f);

	mDrones.push_back(drone);
	mDrones.push_back(drone2);
	mDrones.push_back(drone3);

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

	robotCamera = new CGameCamera2
	(
		atPos + CVector(0.0f, 0.0f, 20.0f),
		atPos
	);
	robotCamera->SetFollowTargetTf(mpTarget);
	robotCamera->SetCurrent(false);

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

}

//シーンの更新処理
void CGameScene::Update()
{
	
}

CXCharacter* CGameScene::CameraTarget() const
{
	return mpTarget;
}

std::list<CDrone*> CGameScene::GetDrones() const
{
	return mDrones;
}
