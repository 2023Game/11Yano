#include "BGMData.h"

// BGM�f�[�^�̃e�[�u��
const BGMData BGM_DATA[] =
{
	//BGM�̎��			���\�[�X�p�X				�x�[�X����	���[�v	���[�v�J�n	���[�v�I��
	{ EBGMType::eTitle,	"Sound\\BGM\\kyuutai.wav",	0.0625f,		true,	0,			0		},
	{ EBGMType::eGame,	"Sound\\BGM\\cyber08.wav",		0.0625f,		true,	0,			2801203	},
	{ EBGMType::eMenu,	"Sound\\BGM\\cyber07.wav",		0.0625f,		true,	0,			0		},
	{ EBGMType::eOver,	"Sound\\BGM\\gameover.wav",		0.0825f,		true,	0,			0		},
};

// BGM�f�[�^��
const int BGM_DATA_COUNT = ARRAY_SIZE(BGM_DATA);