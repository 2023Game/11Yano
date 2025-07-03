#pragma once
#include "CTask.h"
#include "CExpandButton.h"

class CFont;
class CImage;
class CExpandButton;

class CClearUI : public CTask
{
public:
	// �R���X�g���N�^
	CClearUI();
	// �f�X�g���N�^
	~CClearUI();

	// �^�C�g����ʏI����
	bool IsEnd() const;
	// �^�C�g����ʂɈڍs���邩
	bool IsStartTitle() const;

	// �Q�[�����I�����邩
	bool IsExitGame() const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	// ���j���[���J��
	void UpdateOpen();
	// ���j���[�I��
	void UpdateSelect();
	// �t�F�[�h�A�E�g
	void UpdateFadeOut();

	// �^�C�g���̏��
	enum class EState
	{
		eIdle,		// �ҋ@���
		eOpen,		// ���j���[���J��
		eSelect,	// ���j���[�I��
		eStageSelect, // �X�e�[�W�Z���N�g���j���[
		eFadeOut,	// �t�F�[�h�A�E�g
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);

	// [TITLE]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickTitle();

	// [QUIT]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickQuit();

	EState mState;		// ���݂̏��
	int mStateStep;		// ��ԓ��ł̃X�e�b�v�Ǘ��p
	float mElapsedTime;	// �o�ߎ��Ԍv���p
	bool mIsEnd;		// �^�C�g����ʏI���t���O
	int mSelectIndex;	// ���ݑI�����Ă��鍀��

	CFont* mpLogoFont;	// �^�C�g�����S�̃t�H���g
	CText* mpTitleLogo;	// �^�C�g�����S
	CImage* mpTitleBg;	// �^�C�g���w�i�C���[�W

	CExpandButton* btn1;
	CExpandButton* btn2;

	std::vector<CExpandButton*> mButtons;
};
