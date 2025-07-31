#include "CGameOver.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "COverUI.h"
#include "CPlayer.h"

//コンストラクタ
CGameOver::CGameOver()
	: CSceneBase(EScene::eTitle)
{
}

//デストラクタ
CGameOver::~CGameOver()
{

}

//シーン読み込み
void CGameOver::Load()
{
	// タイトル画面はカーソル表示
	CInput::ShowCursor(true);
	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//ここでタイトル画面に必要な
	//リソースの読み込みやクラスの生成を行う

	// タイトルBGMを再生
	CBGMManager::Instance()->Play(EBGMType::eOver);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpOverUI = new COverUI();
	AddTask(mpOverUI);
}

//シーンの更新処理
void CGameOver::Update()
{
	// タイトル画面が
	if (mpOverUI->IsEnd())
	{
		if (mpOverUI->IsContinue())
		{
			CSceneManager::Instance()->LoadScene(EScene::eGame);
		}
		// ゲーム開始ならば、ゲームシーンを読み込む
		if (mpOverUI->IsStartTitle())
		{
			CSceneManager::Instance()->LoadScene(EScene::eTitle);
		}
		// ゲーム終了ならば、アプリを閉じる
		else if (mpOverUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}

CXCharacter* CGameOver::CameraTarget() const
{
	return nullptr;
}
