#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CSound;
class COverUI;

//�^�C�g���V�[��
class CGameOver :public CSceneBase
{
public:
	//�R���X�g���N�^
	CGameOver();
	//�f�X�g���N�^
	~CGameOver();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();
	//�J�����^�[�Q�b�g�̐ݒ�
	CXCharacter* CameraTarget() const;

private:
	COverUI* mpOverUI;
};