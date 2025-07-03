#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
#include "CXCharacter.h"
#include "CImage.h"
class CGameMenu;
class CSound;
class CHackGame;

//�^�C�g���V�[��
class CGameScene2 :public CSceneBase
{
public:
	//�R���X�g���N�^
	CGameScene2();
	//�f�X�g���N�^
	~CGameScene2();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();
	//�J�����ؑ�
	void ChangeCamera();
	CXCharacter* CameraTarget() const;

private:
	CPlayer* player;
	CInteractRobot* irobot;
	CGameCamera2* mainCamera;
	CGameCamera2* robotCamera;
	CGameMenu* mpGameMenu;
	CHackGame* mpHackGame;
	CXCharacter* mpTarget;
	CImage* mpImage;
	CImage* mpImage2;
};
