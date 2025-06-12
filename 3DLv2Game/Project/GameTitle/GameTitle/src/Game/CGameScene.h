#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
#include "CXCharacter.h"
class CGameMenu;
class CSound;
class CHackGame;

//タイトルシーン
class CGameScene :public CSceneBase
{
public:
	//コンストラクタ
	CGameScene();
	//デストラクタ
	~CGameScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
	//カメラ切替
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
};
