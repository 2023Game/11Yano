#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CClearUI.h"

//コンストラクタ
CClearScene::CClearScene()
	: CSceneBase(EScene::eTitle)
{
}

//デストラクタ
CClearScene::~CClearScene()
{

}

//シーン読み込み
void CClearScene::Load()
{
	// タイトル画面はカーソル表示
	CInput::ShowCursor(true);
	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//ここでタイトル画面に必要な
	//リソースの読み込みやクラスの生成を行う

	// タイトルBGMを再生
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpClearUI = new CClearUI();
	AddTask(mpClearUI);
}

//シーンの更新処理
void CClearScene::Update()
{
	// タイトル画面が
	if (mpClearUI->IsEnd())
	{
		// ゲーム開始ならば、ゲームシーンを読み込む
		if (mpClearUI->IsStartTitle())
		{
			CSceneManager::Instance()->LoadScene(EScene::eTitle);
		}
		// ゲーム終了ならば、アプリを閉じる
		else if (mpClearUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}

CXCharacter* CClearScene::CameraTarget() const
{
	return nullptr;
}
