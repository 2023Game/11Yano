#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
enum class ELayer
{
	eNone = -1,
	eTest,
	eField,
	ePlayer,
	eAction,
	eInteractObj,
	eInteractSearch,

	eAttackCol,
};
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
