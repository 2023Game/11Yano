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

//タイトルシーン
class CGameScene :public CSceneBase
{
public:
	//インスタンスのポインタの取得
	static CGameScene* Instance();
	//コンストラクタ
	CGameScene();
	//デストラクタ
	~CGameScene();
	//シーン読み込み
	void Load();
	// エネミー生成
	void CreateEnemy();
	//シーンの更新処理
	void Update();
	CXCharacter* CameraTarget() const;
	//カメラ切替
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
