//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CBullet.h"
#include "CFlamethrower.h"
#include "CSlash.h"
#include "Maths.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CColliderSphere.h"
#include "CInteractObject.h"
#include "CSceneBase.h"
#include "CTaskManager.h"

// �v���C���[�̃C���X�^���X
CPlayer* CPlayer::spInstance = nullptr;

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// T�|�[�Y
	{ "Character\\Mryotaisu\\anim\\idle.x",		true,	500.0f	},	// �ҋ@
	{ "Character\\Mryotaisu\\anim\\walk.x",		true,	62.0f	},	// ���s
	//{ "Character\\Mryotaisu\\anim\\sneak.x",		true,	54.0f	},	// ���Ⴊ�ݕ��s
	//{ "Character\\Player\\anim\\jump_start.x",	false,	25.0f	},	// �W�����v�J�n
	//{ "Character\\Player\\anim\\jump.x",		true,	1.0f	},	// �W�����v��
	//{ "Character\\Player\\anim\\jump_end.x",	false,	26.0f	},	// �W�����v�I��
};

#define PLAYER_HEIGHT	 12.0f
#define PLAYER_WIDTH	  5.0f
#define MOVE_SPEED		  0.375f * 2.0f
#define MOVE_SPEED2		  0.775f * 2.0f
#define GRAVITY			  0.0625f



// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mMoveSpeedY(0.0f)
	, mIsPlayedSlashSE(false)
	, mIsSpawnedSlashEffect(false)
	, mIsDash(false)
	, mpCollider(nullptr)
	, mIsGrounded(false)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Player");

	// �e�[�u�����̃A�j���[�V�����f�[�^��ǂݍ���
	int size = ARRAY_SIZE(ANIM_DATA);
	for (int i = 0; i < size; i++)
	{
		const AnimData& data = ANIM_DATA[i];
		if (data.path.empty()) continue;
		model->AddAnimationSet(data.path.c_str());
	}
	// CXCharacter�̏�����
	Init(model);

	// �ŏ��͑ҋ@�A�j���[�V�������Đ�
	ChangeAnimation(EAnimType::eIdle);

	mpColliderCapsule = new CColliderCapsule
	(
		this, ELayer::ePlayer,
		CVector(0.0f, 2.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f),
		2.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eField, ELayer::eBullet });

	mpCollider = new CColliderSphere
	(
		this, ELayer::eInteractSearch,
		20.0f
	);
	mpCollider->SetCollisionTags({ ETag::eInteractObject });
	mpCollider->SetCollisionLayers({ ELayer::eInteractObj, ELayer::eNextStage, ELayer::eGoal, ELayer::ePlayer });


	// UI
	mpImage = new CImage
	(
		"UI/NextStage.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault,
		false
	);

	mpImage->SetCenter(mpImage->GetSize() * 0.5f);
	mpImage->SetPos(CVector2(930.0f, 350.0f));

	mpImage->SetEnable(false);
	mpImage->SetShow(false);

	// �o�H�T���p�m�[�h���쐬
	mpNavNode = new CNavNode(Position(), true);
	mpNavNode->SetColor(CColor::red);

}

CPlayer::~CPlayer()
{
	SAFE_DELETE(mpColliderCapsule);
	SAFE_DELETE(mpCollider);

	if (mpNavNode != nullptr)
	{
		mpNavNode = nullptr;
	}
	if (spInstance != nullptr)
	{
		spInstance = nullptr;
	}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// �A�j���[�V�����؂�ւ�
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

CInteractObject* CPlayer::GetNearInteractObj() const
{
	CInteractObject* nearObj = nullptr;
	float nearDist = 0.0f;
	CVector pos = Position();
	for (CInteractObject* obj : mNearInteractObjs)
	{
		if (!obj->CanInteract()) continue;

		float dist = (obj->Position() - pos).LengthSqr();
		if (nearObj == nullptr || dist < nearDist)
		{
			nearObj = obj;
			nearDist = dist;
		}
	}
	return nearObj;
}

// �ҋ@
void CPlayer::UpdateIdle()
{
	// �ڒn���Ă����
	if (mIsGrounded)
	{
		CInteractObject* obj = GetNearInteractObj();
		if (obj != nullptr)
		{
			if (CInput::PushKey('F'))
			{
				obj->Interact();
			}
		}
	}
}


// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
CVector CPlayer::CalcMoveVec() const
{
	CVector move = CVector::zero;

	// �L�[�̓��̓x�N�g�����擾
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Y(-1.0f);
	else if (CInput::Key('S'))	input.Y(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (input.LengthSqr() > 0.0f)
	{
		// ������x�N�g��(�ݒu���Ă���ꍇ�́A�n�ʂ̖@��)
		CVector up = mIsGrounded ? mGroundNormal : CVector::up;
		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
		CCamera* mainCamera = CCamera::MainCamera();
		CVector camForward = mainCamera->VectorZ();
		camForward.Y(0.0f);
		camForward.Normalize();
		// �J�����̐��ʕ����x�N�g���Ə�����x�N�g���̊O�ς���
		// �������̈ړ��x�N�g�������߂�
		CVector moveSide = CVector::Cross(up, camForward);
		// �������̈ړ��x�N�g���Ə�����x�N�g���̊O�ς���
		// ���ʕ����̈ړ��x�N�g�������߂�
		CVector moveForward = CVector::Cross(moveSide, up);

		// ���߂��e�����̈ړ��x�N�g������A
		// �ŏI�I�ȃv���C���[�̈ړ��x�N�g�������߂�
		move = moveForward * input.Y() + moveSide * input.X();
		move.Normalize();
	}

	return move;
}

// �ړ��̍X�V����
void CPlayer::UpdateMove()
{
	mMoveSpeed = CVector::zero;

	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = CalcMoveVec();
	// ���߂��ړ��x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		if (mIsDash == true)
		{
			mMoveSpeed += move * MOVE_SPEED2;
		}
		else
		{
			mMoveSpeed += move * MOVE_SPEED;
		}


		// �ҋ@��Ԃł���΁A���s�A�j���[�V�����ɐ؂�ւ�
		if (mState == EState::eIdle)
		{
			ChangeAnimation(EAnimType::eWalk);
		}
	}
	// �ړ��L�[����͂��Ă��Ȃ�
	else
	{
		// �ҋ@��Ԃł���΁A�ҋ@�A�j���[�V�����ɐ؂�ւ�
		if (mState == EState::eIdle)
		{
			ChangeAnimation(EAnimType::eIdle);
		}
	}
}

// �X�V
void CPlayer::Update()
{

	if (mpScene->CameraTarget() == this)
	{
		// ��Ԃɍ��킹�āA�X�V������؂�ւ���
		switch (mState)
		{
			// �ҋ@���
		case EState::eIdle:
			UpdateIdle();
			break;
		}

		// �ҋ@���ƃW�����v���́A�ړ��������s��
		if (mState == EState::eIdle)
		{
			UpdateMove();
		}

		mMoveSpeedY -= GRAVITY;
		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);

		// �ړ�
		Position(Position() + moveSpeed);

		// �v���C���[���ړ������֌�����
		CVector current = VectorZ();
		CVector target = moveSpeed;
		target.Y(0.0f);
		target.Normalize();
		CVector forward = CVector::Slerp(current, target, 0.4f);
		Rotation(CQuaternion::LookRotation(forward));

		if (CInput::Key(VK_SHIFT) || CInput::Key(VK_LBUTTON))
		{
			mIsDash = true;
		}
		else
		{
			mIsDash = false;
		}
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);
		mState = EState::eIdle;
	}
	// �uP�v�L�[����������A�Q�[�����I��
	if (CInput::PushKey('P'))
	{
		System::ExitGame();
	}

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();


	mIsGrounded = false;

	//CDebugPrint::Print("Position:%f:%f:%f\n", Position().X(), Position().Y(), Position().Z());

	CDebugPrint::Print("FPS:%f\n", Times::FPS());

	mNearInteractObjs.clear();
}

// �Փˏ���
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eField)
		{
			CVector adjust = hit.adjust;
			CVector normal = adjust.Normalized();
			float dot = CVector::Dot(normal, CVector::up);

			// ���i�܂��͍�j�Ɣ���
			if (dot > 0.7f)
			{
				// ������݂̂̉����߂��iX,Z�����͌Œ�j
				adjust.X(0.0f);
				adjust.Z(0.0f);
				Position(Position() + adjust * hit.weight);

				if (mMoveSpeedY < 0.0f)
				{
					mMoveSpeedY = 0.0f;
				}
				mIsGrounded = true;
				mGroundNormal = normal;
			}
			// �ǂƔ��肳�ꂽ
			else
			{
				// �������iX,Z�j���������߂�
				adjust.Y(0.0f);
				Position(Position() + adjust * hit.weight);
			}
		}
		if (other->Layer() == ELayer::eBullet)
		{
			// ���S����
		}
	}
	if (self == mpCollider)
	{
		CInteractObject* obj = dynamic_cast<CInteractObject*>(other->Owner());
		if (obj != nullptr)
		{
			mNearInteractObjs.push_back(obj);
#if _DEBUG
			CDebugPrint::Print("%s:%s\n",
				obj->GetDebugName().c_str(),
				obj->GetInteractStr().c_str());
#endif
		}

		if (other->Layer() == ELayer::eNextStage)
		{
			mpImage->Load("UI/NextStage.png", false);

			mpImage->SetEnable(true);
			mpImage->SetShow(true);
		}
		if (other->Layer() == ELayer::eGoal)
		{
			mpImage->Load("UI/exit.png", false);

			mpImage->SetEnable(true);
			mpImage->SetShow(true);
		}
		if(other->Layer() == ELayer::eInteractObj)
		{
			mpImage->Load("UI/hacking.png", false);

			mpImage->SetEnable(true);
			mpImage->SetShow(true);
		}
		
	}
	else
	{
		mpImage->SetEnable(false);
		mpImage->SetShow(false);
	}
}

// �`��
void CPlayer::Render()
{
	CXCharacter::Render();
	mpImage->Render();
}

