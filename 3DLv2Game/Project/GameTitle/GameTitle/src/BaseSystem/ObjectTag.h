#pragma once
#include <initializer_list>

// オブジェクト識別用のタグ
enum class ETag
{
	eNone = -1,

	eField,	// フィールドを構成するオブジェクト
	eRideableObject,	// 乗ることができるオブジェクト
	eInteractObject, 
	eItem,	// アイテムのオブジェクト

	ePlayer,// プレイヤー
	eEnemy,	// エネミー

	eBullet,// 弾丸
	eFlame,	// 炎
	eSlash,	// 斬撃

	ePlayer2D,
	eEnemy2D,
	eBullet2D,
	eClear,

	eCamera,// カメラ

	eDebug,// デバッグ用のオブジェクト

	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
