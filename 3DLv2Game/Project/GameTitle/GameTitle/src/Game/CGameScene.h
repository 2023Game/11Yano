#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
class CGameMenu;
class CSound;
class CHackGame;

//�^�C�g���V�[��
class CGameScene :public CSceneBase
{
public:
	//�R���X�g���N�^
	CGameScene();
	//�f�X�g���N�^
	~CGameScene();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();

private:
	CPlayer* player;
	CInteractRobot* irobot;
	CGameCamera2* maincamera;
	CGameMenu* mpGameMenu;
	CHackGame* mpHackGame;
};
