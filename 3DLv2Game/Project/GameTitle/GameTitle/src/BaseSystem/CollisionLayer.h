#pragma once
#include <initializer_list>

// 衝突判定レイヤー
enum class ELayer
{
	eNone = -1,
	eTest,
	eField,
	ePlayer,
	eEnemy,
	eAction,
	eInteractObj,
	eInteractSearch,
	eNextStage,
	eGoal,
	eBullet,
	eAttackCol,
	e2D,
	eRange,
};
// 衝突判定レイヤーの初期化リスト
using Layers = std::initializer_list<ELayer>;
