#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CSound;
class CClearUI;

//タイトルシーン
class CClearScene :public CSceneBase
{
public:
	//コンストラクタ
	CClearScene();
	//デストラクタ
	~CClearScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
	//カメラターゲットの設定
	CXCharacter* CameraTarget() const;

private:
	CClearUI* mpClearUI;
};