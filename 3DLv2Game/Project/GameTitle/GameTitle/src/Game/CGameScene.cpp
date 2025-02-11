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

//�R���X�g���N�^
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
	, mpHackGame(nullptr)
{
}

//�f�X�g���N�^
CGameScene::~CGameScene()
{
}

//�V�[���ǂݍ���
void CGameScene::Load()
{
	// �Q�[����ʂ̓J�[�\����\��
	CInput::ShowCursor(false);
	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	CResourceManager::Load<CModel>("Field", "Field\\Company.mini.obj");
	CResourceManager::Load<CModel>("Door", "Field\\Object\\door\\scifi_door.obj");
	CResourceManager::Load<CModel>("Intercom", "Field\\Object\\door\\intercom\\intercom.obj");
	CResourceManager::Load<CModel>("FieldCylinder", "Field\\Object\\cylinder.obj");
	CResourceManager::Load<CModel>("Wall", "Field\\Object\\wall\\Wall.obj");
	CResourceManager::Load<CModel>("WallCol", "Field\\Object\\wall\\WallCol.obj");
	CResourceManager::Load<CModelX>("Player", "Character\\Mryotaisu\\Mryotaisu.x");
	CResourceManager::Load<CModelX>("Robot", "Character\\Robot\\Robot_Blue.x");
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	CResourceManager::Load<CTexture>("LightningBolt", "Effect\\lightning_bolt.png");
	CResourceManager::Load<CModel>("Slash", "Effect\\slash.obj");
	CResourceManager::Load<CSound>("SlashSound", "Sound\\SE\\slash.wav");

	// �Q�[��BGM��ǂݍ���
	//CBGMManager::Instance()->Play(EBGMType::eGame);

	// �o�H�T���Ǘ��N���X���쐬
	new CNavManager();

	new CField();

	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(216.0f, 10.30f, 192.0f);

	CRobot* robot = new CRobot
	(
		{
			CVector(233.0f, 10.0f, -105.0f),
			CVector(233.0f, 10.0f, 102.0f),
			CVector(129.0f, 10.0f, 102.0f),
			CVector(129.0f, 10.0f, -105.0f),
		}
	);
	robot->Position(233.0f, 10.30f, -105.0f);

	CRobot* robot2 = new CRobot
	(
		{
			CVector(122.0f, 10.0f, -105.0f),
			CVector(122.0f, 10.0f, 102.0f),
			CVector(12.0f, 10.0f, 102.0f),
			CVector(12.0f, 10.0f, -105.0f),
		}
	);
	robot2->Position(122.0f, 10.0f, 102.0f);

	CRobot* robot3 = new CRobot
	(
		{
			CVector(3.0f, 10.0f, -105.0f),
			CVector(3.0f, 10.0f, 102.0f),
			CVector(-100.0f, 10.0f, 102.0f),
			CVector(-100.0f, 10.0f, -105.0f),
		}
	);
	robot3->Position(3.0f, 10.0f, -105.0f);

	// CGameCamera�̃e�X�g
	//CGameCamera* mainCamera = new CGameCamera
	//(
	//	//CVector(5.0f, -15.0f, 180.0f),
	//	CVector(0.0f, 50.0f, 75.0f),
	//	player->Position()
	//);

	// CGameCamera2�̃e�X�g
	CVector atPos = player->Position() + CVector(0.0f, 10.0f, 0.0f);
	CGameCamera2* mainCamera = new CGameCamera2
	(
		atPos + CVector(0.0f, 0.0f, 40.0f),
		atPos
	);

	mainCamera->SetFollowTargetTf(player);

	// �Q�[�����j���[���쐬
	mpGameMenu = new CGameMenu();

}

//�V�[���̍X�V����
void CGameScene::Update()
{
	// BGM�Đ����łȂ���΁ABGM���Đ�
	//if (!mpGameBGM->IsPlaying())
	//{
	//	mpGameBGM->PlayLoop(-1, 1.0f, false, 1.0f);
	//}

	if (CInput::PushKey('H'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}
