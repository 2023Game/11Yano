#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CClearUI.h"

//�R���X�g���N�^
CClearScene::CClearScene()
	: CSceneBase(EScene::eTitle)
{
}

//�f�X�g���N�^
CClearScene::~CClearScene()
{

}

//�V�[���ǂݍ���
void CClearScene::Load()
{
	// �^�C�g����ʂ̓J�[�\���\��
	CInput::ShowCursor(true);
	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//�����Ń^�C�g����ʂɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpClearUI = new CClearUI();
	AddTask(mpClearUI);
}

//�V�[���̍X�V����
void CClearScene::Update()
{
	// �^�C�g����ʂ�
	if (mpClearUI->IsEnd())
	{
		// �Q�[���J�n�Ȃ�΁A�Q�[���V�[����ǂݍ���
		if (mpClearUI->IsStartTitle())
		{
			CSceneManager::Instance()->LoadScene(EScene::eTitle);
		}
		// �Q�[���I���Ȃ�΁A�A�v�������
		else if (mpClearUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}

CXCharacter* CClearScene::CameraTarget() const
{
	return nullptr;
}
