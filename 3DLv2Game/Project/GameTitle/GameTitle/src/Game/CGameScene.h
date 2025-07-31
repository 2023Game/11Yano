#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
#include "CXCharacter.h"
#include "CDrone.h"
#include "CImage.h"
#include "CCharaBase.h"

class CGameMenu;
class CSound;
class CHackGame;

//�^�C�g���V�[��
class CGameScene :public CSceneBase
{
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CGameScene* Instance();
	//�R���X�g���N�^
	CGameScene();
	//�f�X�g���N�^
	~CGameScene();
	//�V�[���ǂݍ���
	void Load();
	// �G�l�~�[����
	void CreateEnemy();
	//�V�[���̍X�V����
	void Update();
	CXCharacter* CameraTarget() const;
	//�J�����ؑ�
	void ChangeCamera();
	std::list<CDrone*> GetDrones() const;
	std::list<CCharaBase*> GetEnemys() const;
private:
	static CGameScene* spInstance;
	std::list<CDrone*> mDrones;
	std::list<CCharaBase*> mEnemys;
	CPlayer* player;
	CInteractRobot* irobot;
	CGameCamera2* mainCamera;
	CGameCamera2* robotCamera;
	CHackGame* mpHackGame;
	CXCharacter* mpTarget;
	CImage* mpImage;
};
