#pragma once
#include "CSceneBase.h"
#include "CPlayer.h"
#include "CInteractRobot.h"
#include "CGameCamera2.h"
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

private:
	CPlayer* player;
	CInteractRobot* irobot;
	CGameCamera2* maincamera;
	CGameMenu* mpGameMenu;
	CHackGame* mpHackGame;
};
