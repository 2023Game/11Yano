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
#include "CGameUI.h"
#include "CFade.h"

CGameScene* CGameScene::spInstance = nullptr;

CGameScene* CGameScene::Instance()
{
	return spInstance;
}

//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
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
	mDrones.clear();

	mEnemys.clear();
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

	CResourceManager::Load<CModel>("Field",		 "Field\\stage.obj");
	CResourceManager::Load<CModel>("Door",		 "Field\\Object\\door\\door.obj");
	CResourceManager::Load<CModel>("Goal",		 "Field\\Object\\goal.obj");
	CResourceManager::Load<CModel>("Intercom",	 "Field\\Object\\door\\intercom\\intercom.obj");
	CResourceManager::Load<CModelX>("Player",	 "Character\\Mryotaisu\\Mryotaisu.x");
	CResourceManager::Load<CModelX>("Robot",	 "Character\\Robot\\Robot.x");
	CResourceManager::Load<CModel>("Drone",		 "Character\\Drone\\Drone.obj");
	CResourceManager::Load<CTexture>("Laser",	 "Effect\\laser.png");
	CResourceManager::Load<CSound>("Hack",		 "Sound\\SE\\hack.wav");
	CResourceManager::Load<CSound>("Boot",		 "Sound\\SE\\boot.wav");
	CResourceManager::Load<CSound>("Shot",		 "Sound\\SE\\shot.wav");
	CResourceManager::Load<CSound>("View",		 "Sound\\SE\\view.wav");
	CResourceManager::Load<CSound>("Damage",	 "Sound\\SE\\damage.wav");
	CResourceManager::Load<CSound>("Die",		 "Sound\\SE\\die.wav");


	// ゲームBGMを読み込み
	CBGMManager::Instance()->Play(EBGMType::eGame);

	// 経路探索管理クラスを作成
	CNavManager* navMgr = new CNavManager();
	// フィールド生成
	CField* field = new CField();
	// UI生成
	CGameUI* gameUI = new CGameUI();

	// プレイヤー生成
	player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(-132.0f, 0.0f, -115.0f);
	player->SetScene(this);

	mpTarget = player;

	// 操作可能ロボットの生成
	irobot = new CInteractRobot();
	irobot->Scale(1.0f, 1.0f, 1.0f);
	irobot->Position(132.0f, 0.0f, -50.0f);
	irobot->Rotate(CVector(0.0f, 180.0f, 0.0f));
	irobot->SetScene(this);

	CreateEnemy();

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

}

void CGameScene::CreateEnemy()
{
	CRobot* robot = new CRobot
	(
		{
			CVector(-142.0f, 0.0f, -56.0f),
			CVector(-114.0f, 0.0f, -56.0f),
			CVector(-114.0f, 0.0f, 25.0f),
			CVector(-142.0f, 0.0f, 25.0f),
		}, CVector(0.0f, 0.0f, 0.0f)
	);
	robot->Position(-142.0f, 0.30f, -56.0f);

	CRobot* robot2 = new CRobot
	(
		{
			CVector(-103.0f, 0.0f, 25.0f),
			CVector(-75.0f, 0.0f, 25.0f),
			CVector(-75.0f, 0.0f, -56.0f),
			CVector(-103.0f, 0.0f, -56.0f),
		}, CVector(0.0f,0.0f,0.0f)
	);
	robot2->Position(-103.0f, 0.30f, 25.0f);

	CRobot* robot3 = new CRobot
	(
		{
			CVector(-64.0f, 0.0f, -56.0f),
			CVector(-38.0f, 0.0f, -56.0f),
			CVector(-38.0f, 0.0f, 25.0f),
			CVector(-64.0f, 0.0f, 25.0f),
		}, CVector(0.0f,0.0f,0.0f)
	);
	robot3->Position(-64.0f, 0.30f, -76.0f);

	CRobot* robot4 = new CRobot
	(
		{
			CVector(-1.0f, 0.0f, 121.0f),
			CVector(98.0f, 0.0f, 121.0f)
		}, CVector(0.0f, 0.0f, 0.0f)
		);
	robot4->Position(-1.0f, 0.0f, 121.0f);

	CRobot* robot5 = new CRobot
	(
		{
			CVector(93.0f, 0.0f, -90.0f)
		}, CVector(0.0f, 180.0f, 0.0f)
	);
	robot5->Position(93.0f, 0.0f, -90.0f);

	CRobot* robot6 = new CRobot
	(
		{
			CVector(60.0f, 0.0f, -145.0f)
		}, CVector(0.0f, 0.0f, 0.0f)
	);
	robot6->Position(60.0f, 0.0f, -145.0f);

	CRobot* robot7 = new CRobot
	(
		{
			CVector(27.0f, 0.0f, -90.0f)
		}, CVector(0.0f, 180.0f, 0.0f)
	);
	robot7->Position(27.0f, 0.0f, -90.0f);

	CRobot* robot8 = new CRobot
	(
		{
			CVector(40.0f, 0.0f, -6.0f)
		}, CVector(0.0f, 270.0f, 0.0f)
	);
	robot8->Position(40.0f, 0.0f, -6.0f);

	CRobot* robot9 = new CRobot
	(
		{
			CVector(40.0f, 0.0f, -31.0f)
		}, CVector(0.0f, 270.0f, 0.0f)
	);
	robot9->Position(40.0f, 0.0f, -31.0f);


	// ドローン
	CDrone* drone = new CDrone
	(
		{
			CVector(-35.0f, 25.0f, 132.0f),
		}
	);
	drone->Position(-35.0f, 25.0f, 132.0f);
	CDrone* drone2 = new CDrone
	(
		{
			CVector(-100.0f, 25.0f, 88.0f),
			CVector(-58.0f, 25.0f, 88.0f),
		}
	);
	drone2->Position(-100.0f, 25.0f, 86.0f);
	CDrone* drone3 = new CDrone
	(
		{
			CVector(81.5f, 25.0f, 10.0f),
			CVector(81.5f, 25.0f, -51.0f),
		}
	);
	drone3->Position(81.5f, 25.0f, 10.0f);

	// スイッチで停止させるドローン
	mDrones.push_back(drone);
	mDrones.push_back(drone2);

	// 敵キャラ管理
	mEnemys.push_back(robot);
	mEnemys.push_back(robot2);
	mEnemys.push_back(robot3);
	mEnemys.push_back(robot4);
	mEnemys.push_back(robot5);
	mEnemys.push_back(robot6);
	mEnemys.push_back(robot7);
	mEnemys.push_back(robot8);
	mEnemys.push_back(robot9);
	mEnemys.push_back(drone);
	mEnemys.push_back(drone2);
	mEnemys.push_back(drone3);

}

//シーンの更新処理
void CGameScene::Update()
{
	for (auto it = mEnemys.begin(); it != mEnemys.end(); )
	{
		CCharaBase* enemy = *it;
		if (enemy == nullptr || enemy->IsKill())
		{
			it = mEnemys.erase(it); // 要素を削除
		}
		else
		{
			++it;
		}
	}

	if (irobot->IsClear())
	{
		if (CInput::PushKey('F') && !player->IsInteract())
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

CXCharacter* CGameScene::CameraTarget() const
{
	return mpTarget;
}

void CGameScene::ChangeCamera()
{
	if (mpTarget == irobot)
	{
		CFade::FadeIn(0.5f);

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

std::list<CDrone*> CGameScene::GetDrones() const
{
	return mDrones;
}

std::list<CCharaBase*> CGameScene::GetEnemys() const
{
	return mEnemys;
}

