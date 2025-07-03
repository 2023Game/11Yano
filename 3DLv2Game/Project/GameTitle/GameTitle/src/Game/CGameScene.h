#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
#include "CXCharacter.h"
#include "CDrone.h"
#include "CImage.h"

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
	//�V�[���̍X�V����
	void Update();
	CXCharacter* CameraTarget() const;
	std::list<CDrone*> GetDrones() const;
private:
	static CGameScene* spInstance;
	std::list<CDrone*> mDrones;
	CPlayer* player;
	CInteractRobot* irobot;
	CGameCamera2* mainCamera;
	CGameCamera2* robotCamera;
	CGameMenu* mpGameMenu;
	CHackGame* mpHackGame;
	CXCharacter* mpTarget;
	CImage* mpImage;
};
