#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CSound;
class CTitleUI;

//タイトルシーン
class CTitleScene :public CSceneBase
{
public:
	//コンストラクタ
	CTitleScene();
	//デストラクタ
	~CTitleScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
	//カメラターゲットの設定
	CXCharacter* CameraTarget() const;

private:
	CTitleUI* mpTitleUI;
};