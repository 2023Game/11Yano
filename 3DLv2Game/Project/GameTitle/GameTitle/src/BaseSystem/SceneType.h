#pragma once

//シーンの種類
enum class EScene
{
	eNone,	//どのシーンにも所属していない

	eTitle,	//タイトルシーン
	eGame,	//ゲームシーン
	eGame2,
	eGame3,
	eGameOver, // ゲームオーバー
	eClear,    // クリアシーン

	eBootMenu,	//起動時メニュー
	eColTest,	//衝突判定テスト
};
