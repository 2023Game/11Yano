#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
class CSound;
class CClearUI;

//�^�C�g���V�[��
class CClearScene :public CSceneBase
{
public:
	//�R���X�g���N�^
	CClearScene();
	//�f�X�g���N�^
	~CClearScene();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();
	//�J�����^�[�Q�b�g�̐ݒ�
	CXCharacter* CameraTarget() const;

private:
	CClearUI* mpClearUI;
};