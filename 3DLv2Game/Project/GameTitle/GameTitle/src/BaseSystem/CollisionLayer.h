#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
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
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
