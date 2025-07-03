#pragma once
#include "CTask.h"
#include "CExpandButton.h"

class CFont;
class CImage;
class CExpandButton;

class CClearUI : public CTask
{
public:
	// コンストラクタ
	CClearUI();
	// デストラクタ
	~CClearUI();

	// タイトル画面終了か
	bool IsEnd() const;
	// タイトル画面に移行するか
	bool IsStartTitle() const;

	// ゲームを終了するか
	bool IsExitGame() const;

	// 更新
	void Update() override;
	// 描画
	void Render() override;

private:
	// メニューを開く
	void UpdateOpen();
	// メニュー選択
	void UpdateSelect();
	// フェードアウト
	void UpdateFadeOut();

	// タイトルの状態
	enum class EState
	{
		eIdle,		// 待機状態
		eOpen,		// メニューを開く
		eSelect,	// メニュー選択
		eStageSelect, // ステージセレクトメニュー
		eFadeOut,	// フェードアウト
	};
	// 状態切り替え
	void ChangeState(EState state);

	// [TITLE]クリック時のコールバック関数
	void OnClickTitle();

	// [QUIT]クリック時のコールバック関数
	void OnClickQuit();

	EState mState;		// 現在の状態
	int mStateStep;		// 状態内でのステップ管理用
	float mElapsedTime;	// 経過時間計測用
	bool mIsEnd;		// タイトル画面終了フラグ
	int mSelectIndex;	// 現在選択している項目

	CFont* mpLogoFont;	// タイトルロゴのフォント
	CText* mpTitleLogo;	// タイトルロゴ
	CImage* mpTitleBg;	// タイトル背景イメージ

	CExpandButton* btn1;
	CExpandButton* btn2;

	std::vector<CExpandButton*> mButtons;
};
