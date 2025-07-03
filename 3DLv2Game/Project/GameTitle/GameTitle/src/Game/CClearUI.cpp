#include "CClearUI.h"
#include "CFont.h"
#include "CText.h"
#include "CImage.h"
#include "Maths.h"
#include "CInput.h"
#include "CFade.h"
#include "CExpandButton.h"
#include "Easing.h"

// �uCLICK TO START�v�̓_�Ŏ���
#define START_TEXT_BLINK_TIME 1.0f
// �uCLICK TO START�v�̓_�ŊԊu
#define START_TEXT_INTERVAL_TIME 3.0f
// �^�C�g�����j���[�̃A�j���[�V��������
#define OPEN_ANIM_TIME 0.25f
// �^�C�g�����j���[�̃A�j���[�V������̑҂�����
#define OPENED_WAIT_TIME 0.5f

// �R���X�g���N�^
CClearUI::CClearUI()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mState(EState::eOpen)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mIsEnd(false)
{
	// �^�C�g�����S�̃t�H���g�f�[�^�𐶐�
	mpLogoFont = new CFont("res\\Font\\DonguriDuel.ttf");
	mpLogoFont->SetFontSize(128);
	mpLogoFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpLogoFont->SetLineLength(WINDOW_WIDTH);

	// �^�C�g�����S�̃e�L�X�g�𐶐�
	mpTitleLogo = new CText
	(
		mpLogoFont, 128,
		CVector2(0.0f, 150.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(0.11f, 0.1f, 0.1f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTitleLogo->SetText("GAME CLEAR");
	mpTitleLogo->SetEnableOutline(true);
	mpTitleLogo->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	// �^�C�g����ʂ̔w�i�C���[�W�𐶐�
	mpTitleBg = new CImage
	(
		"UI/clear_back.png",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpTitleBg->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// [TITLE]�{�^���𐶐�
	btn1 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.5f, 450.0f),
		CVector2(181.0f, 47.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	// �{�^���̉摜��ǂݍ���
	btn1->LoadButtonImage("UI/title0.png", "UI/title1.png");
	// �{�^���N���b�N���ɌĂяo�����R�[���o�b�N�֐���ݒ�
	btn1->SetOnClickFunc(std::bind(&CClearUI::OnClickTitle, this));
	// �{�^���͍ŏ��͖��������āA�X�P�[���l��0�ɂ��Ă���
	btn1->SetEnable(false);
	btn1->SetScale(0.0f);
	// �{�^�����X�g�ɒǉ�
	mButtons.push_back(btn1);

	// [QUIT]�{�^���𐶐�
	btn2 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.5f, 550.0f),
		CVector2(181.0f, 47.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	btn2->LoadButtonImage("UI/title_quit0.png", "UI/title_quit1.png");
	btn2->SetOnClickFunc(std::bind(&CClearUI::OnClickQuit, this));
	btn2->SetEnable(false);
	btn2->SetScale(0.0f);
	mButtons.push_back(btn2);
}

// �f�X�g���N�^
CClearUI::~CClearUI()
{
	SAFE_DELETE(mpLogoFont);
	SAFE_DELETE(mpTitleLogo);
	SAFE_DELETE(mpTitleBg);

	int size = mButtons.size();
	for (int i = 0; i < size; i++)
	{
		CButton* btn = mButtons[i];
		mButtons[i] = nullptr;
		SAFE_DELETE(btn);
	}
	mButtons.clear();
}

// �^�C�g����ʏI����
bool CClearUI::IsEnd() const
{
	return mIsEnd;
}

bool CClearUI::IsStartTitle() const
{
	// �I�����ڂ�1�ڂȂ�΁A�Q�[���I��
	return mSelectIndex == 0;
}

// �Q�[�����I�����邩
bool CClearUI::IsExitGame() const
{
	// �I�����ڂ�2�ڂȂ�΁A�Q�[���I��
	return mSelectIndex == 1;
}

// ��Ԑ؂�ւ�
void CClearUI::ChangeState(EState state)
{
	if (state == mState) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

void CClearUI::OnClickTitle()
{
	if (mIsEnd) return;

	mSelectIndex = 0;
	mIsEnd = true;
}

// [QUIT]�N���b�N���̃R�[���o�b�N�֐�
void CClearUI::OnClickQuit()
{
	if (mIsEnd) return;

	mSelectIndex = 1;
	mIsEnd = true;
}


// ���j���[���J��
void CClearUI::UpdateOpen()
{
	switch (mStateStep)
	{
		// �X�e�b�v0�F���j���[�̓���A�j���[�V����
	case 0:
		if (mElapsedTime < OPEN_ANIM_TIME)
		{
			// �X�P�[���l����U1.0���傫�����āA1.0�֖߂�C�[�W���O�A�j���[�V����
			float scale = Easing::BackOut(mElapsedTime, OPEN_ANIM_TIME, 0.0f, 1.0f, 2.0f);
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(scale);
			}
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(1.0f);
			}
			mStateStep++;
			mElapsedTime = 0.0f;
		}
		break;
		// �X�e�b�v1�F���j���[�����̑҂�
	case 1:
		if (mElapsedTime < OPENED_WAIT_TIME)
		{
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			// ��莞�ԑ҂�����A�{�^�����I���ɂ��ă^�b�`�ł���悤�ɂ���
			// �i��^�b�`��h�����߂̑҂����ԁj
			for (CExpandButton* btn : mButtons)
			{
				btn->SetEnable(true);
			}
			ChangeState(EState::eSelect);
		}
		break;
	}
}

// ���j���[�I��
void CClearUI::UpdateSelect()
{
}

// �t�F�[�h�A�E�g
void CClearUI::UpdateFadeOut()
{
}

// �X�V
void CClearUI::Update()
{
	switch (mState)
	{
		// �ҋ@���
	case EState::eIdle:
		break;
		// ���j���[���J��
	case EState::eOpen:
		UpdateOpen();
		break;
		// ���j���[�I��
	case EState::eSelect:
		UpdateSelect();
		break;
		// �t�F�[�h�A�E�g
	case EState::eFadeOut:
		UpdateFadeOut();
		break;
	}

	mpTitleLogo->Update();
	mpTitleBg->Update();
	for (CButton* btn : mButtons)
	{
		btn->Update();
	}
}

// �`��
void CClearUI::Render()
{
	// �`�揇�F
	// �w�i���^�C�g�����S���uCLICK TO START�v�����j���[�{�^��

	// �w�i�`��
	mpTitleBg->Render();
	// �^�C�g�����S�`��
	mpTitleLogo->Render();


	// �ҋ@��ԈȊO�́A���j���[�{�^����\��
	if (mState != EState::eIdle)
	{

		for (CButton* btn : mButtons)
		{
			btn->Render();
		}
	}
}
