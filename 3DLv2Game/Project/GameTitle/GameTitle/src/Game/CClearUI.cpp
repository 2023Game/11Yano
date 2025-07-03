#include "CClearUI.h"
#include "CFont.h"
#include "CText.h"
#include "CImage.h"
#include "Maths.h"
#include "CInput.h"
#include "CFade.h"
#include "CExpandButton.h"
#include "Easing.h"

// 「CLICK TO START」の点滅時間
#define START_TEXT_BLINK_TIME 1.0f
// 「CLICK TO START」の点滅間隔
#define START_TEXT_INTERVAL_TIME 3.0f
// タイトルメニューのアニメーション時間
#define OPEN_ANIM_TIME 0.25f
// タイトルメニューのアニメーション後の待ち時間
#define OPENED_WAIT_TIME 0.5f

// コンストラクタ
CClearUI::CClearUI()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mState(EState::eOpen)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mIsEnd(false)
{
	// タイトルロゴのフォントデータを生成
	mpLogoFont = new CFont("res\\Font\\DonguriDuel.ttf");
	mpLogoFont->SetFontSize(128);
	mpLogoFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpLogoFont->SetLineLength(WINDOW_WIDTH);

	// タイトルロゴのテキストを生成
	mpTitleLogo = new CText
	(
		mpLogoFont, 128,
		CVector2(0.0f, 150.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(0.11f, 0.1f, 0.1f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTitleLogo->SetText("GAME CLEAR");
	mpTitleLogo->SetEnableOutline(true);
	mpTitleLogo->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	// タイトル画面の背景イメージを生成
	mpTitleBg = new CImage
	(
		"UI/clear_back.png",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTitleBg->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// [TITLE]ボタンを生成
	btn1 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.5f, 450.0f),
		CVector2(181.0f, 47.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	// ボタンの画像を読み込み
	btn1->LoadButtonImage("UI/title0.png", "UI/title1.png");
	// ボタンクリック時に呼び出されるコールバック関数を設定
	btn1->SetOnClickFunc(std::bind(&CClearUI::OnClickTitle, this));
	// ボタンは最初は無効化して、スケール値を0にしておく
	btn1->SetEnable(false);
	btn1->SetScale(0.0f);
	// ボタンリストに追加
	mButtons.push_back(btn1);

	// [QUIT]ボタンを生成
	btn2 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.5f, 550.0f),
		CVector2(181.0f, 47.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	btn2->LoadButtonImage("UI/title_quit0.png", "UI/title_quit1.png");
	btn2->SetOnClickFunc(std::bind(&CClearUI::OnClickQuit, this));
	btn2->SetEnable(false);
	btn2->SetScale(0.0f);
	mButtons.push_back(btn2);
}

// デストラクタ
CClearUI::~CClearUI()
{
	SAFE_DELETE(mpLogoFont);
	SAFE_DELETE(mpTitleLogo);
	SAFE_DELETE(mpTitleBg);

	int size = mButtons.size();
	for (int i = 0; i < size; i++)
	{
		CButton* btn = mButtons[i];
		mButtons[i] = nullptr;
		SAFE_DELETE(btn);
	}
	mButtons.clear();
}

// タイトル画面終了か
bool CClearUI::IsEnd() const
{
	return mIsEnd;
}

bool CClearUI::IsStartTitle() const
{
	// 選択項目が1つ目ならば、ゲーム終了
	return mSelectIndex == 0;
}

// ゲームを終了するか
bool CClearUI::IsExitGame() const
{
	// 選択項目が2つ目ならば、ゲーム終了
	return mSelectIndex == 1;
}

// 状態切り替え
void CClearUI::ChangeState(EState state)
{
	if (state == mState) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

void CClearUI::OnClickTitle()
{
	if (mIsEnd) return;

	mSelectIndex = 0;
	mIsEnd = true;
}

// [QUIT]クリック時のコールバック関数
void CClearUI::OnClickQuit()
{
	if (mIsEnd) return;

	mSelectIndex = 1;
	mIsEnd = true;
}


// メニューを開く
void CClearUI::UpdateOpen()
{
	switch (mStateStep)
	{
		// ステップ0：メニューの入場アニメーション
	case 0:
		if (mElapsedTime < OPEN_ANIM_TIME)
		{
			// スケール値を一旦1.0より大きくして、1.0へ戻るイージングアニメーション
			float scale = Easing::BackOut(mElapsedTime, OPEN_ANIM_TIME, 0.0f, 1.0f, 2.0f);
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(scale);
			}
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(1.0f);
			}
			mStateStep++;
			mElapsedTime = 0.0f;
		}
		break;
		// ステップ1：メニュー入場後の待ち
	case 1:
		if (mElapsedTime < OPENED_WAIT_TIME)
		{
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			// 一定時間待ったら、ボタンをオンにしてタッチできるようにする
			// （誤タッチを防ぐための待ち時間）
			for (CExpandButton* btn : mButtons)
			{
				btn->SetEnable(true);
			}
			ChangeState(EState::eSelect);
		}
		break;
	}
}

// メニュー選択
void CClearUI::UpdateSelect()
{
}

// フェードアウト
void CClearUI::UpdateFadeOut()
{
}

// 更新
void CClearUI::Update()
{
	switch (mState)
	{
		// 待機状態
	case EState::eIdle:
		break;
		// メニューを開く
	case EState::eOpen:
		UpdateOpen();
		break;
		// メニュー選択
	case EState::eSelect:
		UpdateSelect();
		break;
		// フェードアウト
	case EState::eFadeOut:
		UpdateFadeOut();
		break;
	}

	mpTitleLogo->Update();
	mpTitleBg->Update();
	for (CButton* btn : mButtons)
	{
		btn->Update();
	}
}

// 描画
void CClearUI::Render()
{
	// 描画順：
	// 背景→タイトルロゴ→「CLICK TO START」かメニューボタン

	// 背景描画
	mpTitleBg->Render();
	// タイトルロゴ描画
	mpTitleLogo->Render();


	// 待機状態以外は、メニューボタンを表示
	if (mState != EState::eIdle)
	{

		for (CButton* btn : mButtons)
		{
			btn->Render();
		}
	}
}
