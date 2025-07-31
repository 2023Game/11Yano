#include "CGameOver.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "COverUI.h"
#include "CPlayer.h"

//�R���X�g���N�^
CGameOver::CGameOver()
	: CSceneBase(EScene::eTitle)
{
}

//�f�X�g���N�^
CGameOver::~CGameOver()
{

}

//�V�[���ǂݍ���
void CGameOver::Load()
{
	// �^�C�g����ʂ̓J�[�\���\��
	CInput::ShowCursor(true);
	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//�����Ń^�C�g����ʂɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eOver);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpOverUI = new COverUI();
	AddTask(mpOverUI);
}

//�V�[���̍X�V����
void CGameOver::Update()
{
	// �^�C�g����ʂ�
	if (mpOverUI->IsEnd())
	{
		if (mpOverUI->IsContinue())
		{
			CSceneManager::Instance()->LoadScene(EScene::eGame);
		}
		// �Q�[���J�n�Ȃ�΁A�Q�[���V�[����ǂݍ���
		if (mpOverUI->IsStartTitle())
		{
			CSceneManager::Instance()->LoadScene(EScene::eTitle);
		}
		// �Q�[���I���Ȃ�΁A�A�v�������
		else if (mpOverUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}

CXCharacter* CGameOver::CameraTarget() const
{
	return nullptr;
}
