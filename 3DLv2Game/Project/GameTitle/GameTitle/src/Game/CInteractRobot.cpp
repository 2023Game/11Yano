#include "CInteractRobot.h"
#include "CInput.h"
#include "CDebugFieldOfView.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Primitive.h"
#include "CField.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CHackGame.h"
#include "CBullet.h"

#define ROBOT_HEIGHT 16.0f
#define ROBOT_WIDTH 10.0f
#define MOVE_SPEED	  0.375f * 2.0f // �ړ����x
#define GRAVITY	  0.0625f // �d��
#define FOV_ANGLE 45.0f // ����͈͂̊p�x
#define FOV_LENGTH 100.0f // ����͈͂̋���
#define EYE_HEIGHT 10.0f // ���_�̍���
#define WALK_SPEED 10.0f // ���s���x
#define RUN_SPEED 20.0f // ���s���x
#define ROTATE_SPEED 6.0f // ��]���x
#define ATTACK_LANGE 40.0f // �U���͈�
#define PATROL_INTERVAL 3.0f // ���̏���|�C���g�Ɉړ��J�n����܂ł̎���
#define PATROL_NEAR_DIST 10.0f // ����J�n���ɑI������鏄��|�C���g�̍ŒZ����
#define IDLE_TIME 5.0f // �ҋ@��Ԃ̎���


// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CInteractRobot::AnimData CInteractRobot::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// T�|�[�Y
	{ "Character\\Robot\\anim\\idle.x",		true,	460.0f	},	// �ҋ@
	{ "Character\\Robot\\anim\\walk.x",		true,	78.0f	},	// ���s
	{ "Character\\Robot\\anim\\run.x",		true,	44.0f	},	// ���s
	{ "Character\\Robot\\anim\\attack.x",		true,	186.0f	},	// �U��
	{ "Character\\Robot\\anim\\down.x",		false,	59.0f	},	// �|���
	{ "Character\\Robot\\anim\\sit.x",		false,	0.0f	},	// ����

};

// �R���X�g���N�^
CInteractRobot::CInteractRobot()
	: mState(EState::eIdle)
	, mMoveSpeedY(0.0f)
	, mIsGrounded(false)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mFovAngle(FOV_ANGLE)
	, mFovLength(FOV_LENGTH)
	, mpDebugFov(nullptr)
	, mNextPatrolIndex(-1)
	, mNextMoveIndex(0)
	, mpHackGame(nullptr)
	, mIsHack(false)
	, mIsClear(false)
{
	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Robot");

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

	mpColliderLine = new CColliderLine
	(
		this, ELayer::eInteractObj,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ROBOT_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eInteractSearch });

	float width = ROBOT_WIDTH * 0.5f;
	float posY = ROBOT_HEIGHT * 0.5f;
	mpColliderLineX = new CColliderLine
	(
		this, ELayer::eField,
		CVector(-width, posY, 0.0f),
		CVector(width, posY, 0.0f)
	);
	mpColliderLineX->SetCollisionLayers({ ELayer::eField });
	mpColliderLineZ = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, posY, -width),
		CVector(0.0f, posY, width)
	);
	mpColliderLineZ->SetCollisionLayers({ ELayer::eField });

	mpHackGame = new CHackGame();
	mInteractStr = "�I���ɂ���";
}

CInteractRobot::~CInteractRobot()
{
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderLineX);
	SAFE_DELETE(mpColliderLineZ);

	// ����͈͂̃f�o�b�O�\�������݂�����ꏏ�ɍ폜
	if (mpDebugFov != nullptr)
	{
		mpDebugFov->SetOwner(nullptr);
		mpDebugFov->Kill();
	}

	// �o�H�T���p�m�[�h�̔j��
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		SAFE_DELETE(mpNavNode);
		SAFE_DELETE(mpLostPlayerNode);

		// ����|�C���g�ɔz�u�����m�[�h�����ׂč폜
		auto itr = mPatrolPoints.begin();
		auto end = mPatrolPoints.end();
		while (itr != end)
		{
			CNavNode* del = *itr;
			itr = mPatrolPoints.erase(itr);
			delete del;
		}
	}
}

void CInteractRobot::DeleteObject(CObjectBase* obj)
{
	// �폜���ꂽ�I�u�W�F�N�g������͈͂̃f�o�b�O�\���ł���΃|�C���^����ɂ���
	if (obj == mpDebugFov)
	{
		mpDebugFov = nullptr;
	}
}

//�X�V����
void CInteractRobot::Update()
{

	mMoveSpeedY -= GRAVITY;
	CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);

	// �ړ�
	Position(Position() + moveSpeed);

	// �v���C���[���ړ������֌�����
	CVector current = VectorZ();
	CVector target = moveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// �E�N���b�N�Œe�۔���
	if (CInput::PushKey(VK_RBUTTON))
	{
		// �e�ۂ𐶐�
		new CBullet
		(
			// ���ˈʒu
			Position() + CVector(0.0f, 10.0f, 0.0f) + VectorZ() * 20.0f,
			VectorZ(),	// ���˕���
			1000.0f,	// �ړ�����
			1000.0f		// �򋗗�
		);
	}

	if (!IsClear())
	{
		//// ���݂̏�Ԃɍ��킹�čX�V������ؑ�
		//switch (mState)
		//{
		//
		//case EState::ePatrol: UpdatePatrol(); break;
		//case EState::eChase: UpdateChase(); break;
		//case EState::eLost: UpdateLost(); break;
		//case EState::eAttack: UpdateAttack(); break;
		//}
		mState = EState::eIdle;

		CXCharacter::Update();

		CDebugPrint::Print("��� : %s\n", GetStateStr(mState).c_str());
	}
	else if (IsClear())
	{
		mIsClear = true;
		mState = EState::eIdle;
	}

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
}

void CInteractRobot::Render()
{
	CXCharacter::Render();
}

void CInteractRobot::Interact()
{
	mIsHack = mIsHack;
	mInteractStr = mIsHack ? "�I�t�ɂ���" : "�I���ɂ���";
	if (CInput::PushKey('F'))
	{
		mpHackGame->Open();
	}
}

bool CInteractRobot::IsClear() const
{
	if (!mpHackGame->IsClear()) return false;

	return true;
}

// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
CVector CInteractRobot::CalcMoveVec() const
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
void CInteractRobot::UpdateMove()
{
	mMoveSpeed = CVector::zero;

	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = CalcMoveVec();
	// ���߂��ړ��x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		mMoveSpeed += move * MOVE_SPEED;

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


void CInteractRobot::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			// �⓹�Ŋ���Ȃ��悤�ɁA�����߂��x�N�g����X��Z�̒l��0�ɂ���
			CVector adjust = hit.adjust;
			adjust.X(0.0f);
			adjust.Z(0.0f);

			Position(Position() + adjust * hit.weight);
		}
	}
	else if (self == mpColliderLineX || self == mpColliderLineZ)
	{
		if (other->Layer() == ELayer::eField)
		{
			// �⓹�Ŋ���Ȃ��悤�ɁA�����߂��x�N�g����X��Z�̒l��0�ɂ���
			CVector adjust = hit.adjust;
			adjust.Y(0.0f);

			// �����߂��x�N�g���̕����W���ړ�
			Position(Position() + adjust * hit.weight);
		}
	}
}

void CInteractRobot::ChangeAnimation(EAnimType type)
{
	int index = (int)type;
	if (!(0 <= index && index < (int)EAnimType::Num)) return;
	const AnimData& data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

void CInteractRobot::ChangeState(EState state)
{
	//���łɓ�����Ԃł���Ώ������Ȃ�
	if (state == mState) return;

	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

std::string CInteractRobot::GetStateStr(EState state) const
{
	switch (mState)
	{
	case EState::eIdle: return "�ҋ@";
	case EState::ePatrol: return "����";
	case EState::eChase: return "�ǐ�";
	case EState::eLost: return "������";
	case EState::eAttack: return "�U��";
	}
	return std::string();
}

