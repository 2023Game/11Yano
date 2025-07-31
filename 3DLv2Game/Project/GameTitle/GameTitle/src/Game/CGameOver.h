#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CSound;
class COverUI;

//タイトルシーン
class CGameOver :public CSceneBase
{
public:
	//コンストラクタ
	CGameOver();
	//デストラクタ
	~CGameOver();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
	//カメラターゲットの設定
	CXCharacter* CameraTarget() const;

private:
	COverUI* mpOverUI;
};