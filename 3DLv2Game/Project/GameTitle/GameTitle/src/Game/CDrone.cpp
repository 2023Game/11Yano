#include "CDrone.h"
#include "CDebugFieldOfView.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Primitive.h"
#include "CNavNode.h"
#include "CNavManager.h"
#include "CField.h"
#include "CBullet.h"
#include <cmath>

#define FOV_ANGLE 45.0f // ����͈͂̊p�x
#define FOV_LENGTH 30.0f // ����͈͂̔��a
#define EYE_HEIGHT -40.0f // ���_�̍���
#define WALK_SPEED 10.0f // ���s���x
#define RUN_SPEED 10.0f // ���s���x
#define ROTATE_SPEED 6.0f // ��]���x
#define PATROL_INTERVAL 3.0f // ���̏���|�C���g�Ɉړ��J�n����܂ł̎���
#define PATROL_NEAR_DIST 10.0f // ����J�n���ɑI������鏄��|�C���g�̍ŒZ����
#define IDLE_TIME 5.0f // �ҋ@��Ԃ̎���
#define ATTACK_LANGE 35.0f // �U���͈�
#define BULLET_TIME 7.0f // �e�̔��ˊԊu

CDrone::CDrone(std::vector<CVector> patrolPoints)
	: CXCharacter(ETag::eEnemy, ETaskPriority::eDefault)
	, mFovAngle(FOV_ANGLE)
	, mFovLength(FOV_LENGTH)
	, mFovHeight(EYE_HEIGHT)
	, mpDebugFov(nullptr)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mNextPatrolIndex(-1)
	, mNextMoveIndex(0)
	, mBulletTime(0.0f)
{
	mpModel = CResourceManager::Get<CModel>("Drone");
	// CXCharacter�̏�����
	//Init(model);

	// ����͈͂̃f�o�b�O�\���N���X���쐬
	mpDebugFov = new CDebugFieldOfView(this, mFovAngle, mFovLength, CDebugFieldOfView::EType::eCone);

	// �o�H�T���p�m�[�h���쐬
	mpNavNode = new CNavNode(Position(), true);
	mpNavNode->SetColor(CColor::blue);

	mpLostPlayerNode = new CNavNode(CVector::zero, true);

	// ����|�C���g�Ɍo�H�T���p�̃m�[�h��z�u
	for (CVector point : patrolPoints)
	{
		CNavNode* node = new CNavNode(point, true);
		mPatrolPoints.push_back(node);
	}
}

CDrone::~CDrone()
{
	// ����͈͂̃f�o�b�O�\�������݂�����폜
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

void CDrone::DeleteObject(CObjectBase* obj)
{
	// �폜���ꂽ�I�u�W�F�N�g������͈͂̃f�o�b�O�\���ł���΃|�C���^����ɂ���
	if (obj == mpDebugFov)
	{
		mpDebugFov = nullptr;
	}
}

void CDrone::Update()
{
	// ���݂̏�Ԃɍ��킹�čX�V������ؑ�
	switch (mState)
	{
	case EState::eIdle: UpdateIdle(); break;
	case EState::ePatrol: UpdatePatrol(); break;
	case EState::eChase: UpdateChase(); break;
	case EState::eLost: UpdateLost(); break;
	case EState::eAttack: UpdateAttack(); break;
	}

	//CXCharacter::Update();

	// �o�H�T���p�m�[�h�����݂�������W�X�V
	if (mpNavNode != nullptr)
	{
		mpNavNode->SetPos(Position());
	}

	if (mpDebugFov != nullptr)
	{
		//���݂̏�Ԃɍ��킹�Ď���͈͂̐F��ύX
		mpDebugFov->SetColor(GetStateColor(mState));
	}
}

void CDrone::Render()
{
	mpModel->Render(Matrix());

	if (mState == EState::ePatrol)
	{
		float rad = 1.0f;
		// ����|�C���g��`��
		int size = mPatrolPoints.size();
		for (int i = 0; i < size; i++)
		{
			CMatrix m;
			m.Translate(mPatrolPoints[i]->GetPos() + CVector(0.0f, rad * 2.0f, 0.0f));
			CColor c = i == mNextPatrolIndex ? CColor::red : CColor::cyan;
			Primitive::DrawSphere(m, rad, c);
		}
	}

	// �v���C���[�����������ʒu�Ƀf�o�b�O�\��
	if (mState == EState::eLost)
	{
		// �v���C���[�����������ʒu�Ƀf�o�b�O�\��
		float rad = 2.0f;
		CMatrix m;
		m.Translate(mpLostPlayerNode->GetPos() + CVector(0.0f, rad, 0.0f));
		Primitive::DrawWireSphere(m, rad, CColor::blue);
	}

	CPlayer* player = CPlayer::Instance();
	CField* field = CField::Instanse();
	if (player != nullptr && field != nullptr)
	{
		CVector offsetPos = CVector(0.0f, EYE_HEIGHT, 0.0f);
		CVector playerPos = player->Position() + offsetPos;
		CVector selfPos = Position() + offsetPos;

		// �v���C���[�Ƃ̊ԂɎՕ��������݂���ꍇ
		CHitInfo hit;
		if (field->CollisionRay(selfPos, playerPos, &hit))
		{
			// �Փ˂����ʒu�܂ŐԐ��`��
			Primitive::DrawLine
			(
				selfPos, hit.cross,
				CColor::red,
				2.0f
			);
		}
		else
		{
			Primitive::DrawLine
			(
				selfPos, playerPos,
				CColor::green,
				2.0f
			);
		}
	}
}

void CDrone::ChangeState(EState state)
{
	//���łɓ�����Ԃł���Ώ������Ȃ�
	if (state == mState) return;

	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

bool CDrone::IsFoundPlayer() const
{
	// �v���C���[�����݂��Ȃ��ꍇ�͎���͈͊O�Ƃ���
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;

	// �v���C���[���W�擾
	CVector playerPos = player->Position();
	// �������g�̍��W���擾
	CVector pos = Position();
	// ���g����v���C���[�܂ł̃x�N�g�������߂�
	CVector vec = playerPos - pos;
	//vec.Y(0.0f); // �v���C���[�Ƃ̍����̍����l�����Ȃ�

	// �@����p�x�������߂�
	// �x�N�g���𐳋K�����Ē�����1�ɂ���
	CVector dir = vec.Normalized();
	// ���g�̐��ʕ����x�N�g�����擾
	CVector forward = CVector(0.0f,-1.0f,0.0f);
	// �v���C���[�܂ł̃x�N�g���Ǝ��g�̐��ʕ����x�N�g���̓��ς����߂Ċp�x���o��
	float dot = CVector::Dot(dir, forward);
	// ����p�x�̃��W�A�������߂�
	float angleR = Math::DegreeToRadian(mFovAngle);
	// ���߂����ςƎ���p�x�Ŏ���͈͓������f����
	if (dot < cosf(angleR)) return false;

	// �A���싗���������߂�
	// �v���C���[�܂ł̋����Ǝ��싗���Ŏ���͈͓������f����
	float dist = vec.Length();
	float length = std::sqrt(mFovLength * mFovLength + mFovHeight * mFovHeight); // ����͈͉~���̕���̒���
	if (dist > length) return false;

	// �v���C���[�Ƃ̊ԂɎՕ������Ȃ����m�F
	if (!IsLookPlayer()) return false;

	//���ׂĂ̏������N���A���Ă���̂Ŏ���͈͓��ł���
	return true;
}

bool CDrone::IsLookPlayer() const
{
	// �v���C���[�����݂��Ȃ��ꍇ�͌����Ȃ�
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;
	// �t�B�[���h�����݂��Ȃ��ꍇ(�Օ������Ȃ�)�͌�����
	CField* field = CField::Instanse();
	if (field == nullptr) return true;

	CVector offsetPos = CVector(0.0f, EYE_HEIGHT, 0.0f);
	// �v���C���[���W�擾
	CVector playerPos = player->Position();
	// �����̍��W�擾
	CVector selfPos = Position() + offsetPos;

	CHitInfo hit;
	// �Օ��������݂����ꍇ�v���C���[�������Ȃ�
	if (field->CollisionRay(selfPos, playerPos, &hit)) return false;

	return true;
}

bool CDrone::CanAttackPlayer() const
{
	// �v���C���[�����Ȃ��ꍇ��false
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return false;

	// �v���C���[�܂ł̋������U���͈͊O�ł����false
	CVector playerPos = player->Position();
	CVector vec = playerPos - Position();
	//vec.Y(0.0f);
	float dist = vec.Length();
	if (dist > ATTACK_LANGE) return false;


	return true;
}

bool CDrone::MoveTo(const CVector& targetPos, float speed)
{
	// �ړI�n�܂ł̃x�N�g�������߂�
	CVector pos = Position();
	CVector vec = targetPos - pos;
	vec.Y(0.0f);
	// �ړ������x�N�g�������߂�
	CVector moveDir = vec.Normalized();

	// �W���W���Ɉړ������֌�����
	CVector forward = CVector::Slerp
	(
		VectorZ(),
		moveDir,
		ROTATE_SPEED * Times::DeltaTime()
	);
	Rotation(CQuaternion::LookRotation(moveDir));

	// ����̈ړ����������߂�
	float moveDist = speed * Times::DeltaTime();
	//�ړI�n�܂ł̎c�苗�������߂�
	float remainDist = vec.Length();
	// �c��̋������ړ��������Z��
	if (remainDist <= moveDist)
	{
		// �ړI�n�܂ňړ�����
		pos = CVector(targetPos.X(), pos.Y(), targetPos.Z());
		Position(pos);
		return true; // �ړI�n�̓��������̂�true
	}

	// �c��̋������ړ�������蒷���ꍇ�͈ړ��������ړI�n�ֈړ�
	pos += moveDir * moveDist;
	Position(pos);

	// �ړI�n�ɓ������Ȃ�����
	return false;
}

void CDrone::ChangePatrolPoint()
{
	// ����|�C���g��ݒ肳��Ă��Ȃ��ꍇ�������Ȃ�
	int size = mPatrolPoints.size();
	if (size == 0) return;

	// ����J�n���ł���Έ�ԋ߂�����|�C���g��I��
	if (mNextPatrolIndex == -1)
	{
		int nearIndex = -1; // ��ԋ߂�����|�C���g�̔ԍ�
		float nearDist = 0.0f; // ��ԋ߂�����|�C���g�܂ł̋���
		// ���ׂĂ̏���|�C���g�̋����𒲂׈�ԋ߂�����|�C���g��T��
		for (int i = 0; i < size; i++)
		{
			CVector point = mPatrolPoints[i]->GetPos();
			CVector vec = point - Position();
			vec.Y(0.0f);
			float dist = vec.Length();
			// ����|�C���g���߂�����ꍇ�̓X���[
			if (dist < PATROL_NEAR_DIST) continue;
			// ��ԍŏ��̏���|�C���g�������͌��݈�ԋ߂�����|�C���g��肳��ɋ߂��ꍇ
			// ����|�C���g�̔ԍ���u��������
			if (nearIndex < 0 || dist < nearDist)
			{
				nearIndex = i;
				nearDist = dist;
			}
		}
		mNextPatrolIndex = nearIndex;
	}
	// ���񒆂̏ꍇ���̏���|�C���g���w�肷��
	else
	{
		mNextPatrolIndex++;
		if (mNextPatrolIndex >= size) mNextPatrolIndex -= size;
	}

	// ���ɏ��񂷂�|�C���g�����܂�����
	if (mNextMoveIndex >= 0)
	{
		CNavManager* navMgr = CNavManager::Instance();
		if (navMgr != nullptr)
		{
			for (CNavNode* node : mPatrolPoints)
			{
				node->SetPos(node->GetPos());
			}
			//����|�C���g�܂ł̍ŒZ�o�H�����߂�
			if (navMgr->Navigate(mpNavNode, mPatrolPoints[mNextPatrolIndex], mMoveRoute))
			{
				// ���̖ړI�n�̃C���f�b�N�X��ݒ�
				mNextMoveIndex = 1;
			}
		}
	}
}

void CDrone::UpdateIdle()
{
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}

	if (mElapsedTime < IDLE_TIME)
	{
		mElapsedTime += Times::DeltaTime();
	}
	else
	{
		// �ҋ@���Ԍo�߂����珄���Ԃֈڍs
		ChangeState(EState::ePatrol);
	}
}

void CDrone::UpdatePatrol()
{
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}


	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// ����J�n���̏���|�C���g�����߂�
	case 0:
		mNextPatrolIndex = -1;
		ChangePatrolPoint();
		mStateStep++;
		break;
		// ����|�C���g�܂ňړ�
	case 1:
	{
		CNavNode* moveNode = mMoveRoute[mNextMoveIndex];
		if (MoveTo(moveNode->GetPos(), WALK_SPEED))
		{
			// �ړ����I���Ύ��̃m�[�h�֐ؑ�
			mNextMoveIndex++;
			// �Ō�̃m�[�h�������ꍇ�͎��̃X�e�b�v�֐i��
			if (mNextMoveIndex >= mMoveRoute.size())
			{
				mStateStep++;
			}
		}
		break;
	}
	// �ړ���̑ҋ@
	case 2:
		if (mElapsedTime < PATROL_INTERVAL)
		{
			mElapsedTime += Times::DeltaTime();
		}
		else
		{
			ChangePatrolPoint();
			mStateStep = 1;
			mElapsedTime = 0.0f;
		}
		break;
	}
}

void CDrone::UpdateChase()
{
	// �v���C���[��ǐ�
	CPlayer* player = CPlayer::Instance();
	CVector targetPos = player->Position();

	if (!IsFoundPlayer())
	{
		// ���������ʒu�Ƀm�[�h��z�u
		mpLostPlayerNode->SetPos(targetPos);
		ChangeState(EState::eLost);
		return;
	}
	// �v���C���[�ɍU���ł���Ȃ�U����Ԃֈڍs
	if (CanAttackPlayer())
	{
		ChangeState(EState::eAttack);
		return;
	}

	// �o�H�T���Ǘ��N���X�����݂���Ƃ�
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		// ���g�̃m�[�h����v���C���[�̃m�[�h�܂ł̍ŒZ�o�H�����߂�
		CNavNode* playerNode = player->GetNavNode();
		if (navMgr->Navigate(mpNavNode, playerNode, mMoveRoute))
		{
			targetPos = mMoveRoute[1]->GetPos();
		}
	}

	if (MoveTo(targetPos, RUN_SPEED))
	{

	}
}

void CDrone::UpdateLost()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr == nullptr)
	{
		ChangeState(EState::eIdle);
		return;
	}
	// �v���C���[����������ǐՏ�Ԃֈڍs
	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
		return;
	}

	switch (mStateStep)
	{
		// ���������ʒu�܂ł̍ŒZ�o�H�����߂�
	case 0:
		if (navMgr->Navigate(mpNavNode, mpLostPlayerNode, mMoveRoute))
		{
			mNextMoveIndex = 1;
			mStateStep++;
		}
		else
		{
			ChangeState(EState::eIdle);
		}

		break;
	case 1:
		// ���������ʒu�܂ňړ�
		if (MoveTo(mMoveRoute[mNextMoveIndex]->GetPos(), RUN_SPEED))
		{
			mNextMoveIndex++;
			if (mNextMoveIndex >= mMoveRoute.size())
			{
				// �ړ����I���Αҋ@��Ԃ�
				ChangeState(EState::eIdle);
			}
		}
		break;
	}
}

void CDrone::UpdateAttack()
{
	mBulletTime -= 1.0f;
	CPlayer* player = CPlayer::Instance();
	// �v���C���[���W�擾
	CVector playerPos = player->Position();
	// �������g�̍��W���擾
	CVector pos = Position();
	// ���g����v���C���[�܂ł̃x�N�g�������߂�
	CVector vec = playerPos - pos;
	if (mBulletTime <= 0)
	{
		// �e�ۂ𐶐�
		new CBullet
		(
			// ���ˈʒu
			Position() + CVector(0.0f, 0.0f, 0.0f),
			vec,	// ���˕���
			200.0f,	// �ړ�����
			200.0f		// �򋗗�
		);
		mBulletTime = BULLET_TIME;
	}

	if (!CanAttackPlayer())
	{
		if (!IsFoundPlayer())
		{
			ChangeState(EState::eLost);
			return;
		}
		ChangeState(EState::eChase);
	}
}

std::string CDrone::GetStateStr(EState state) const
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

CColor CDrone::GetStateColor(EState state) const
{
	switch (mState)
	{
	case EState::eIdle: return CColor::green;
	case EState::ePatrol: return CColor::green;
	case EState::eChase: return CColor::red;
	case EState::eLost: return CColor::yellow;
	case EState::eAttack: return CColor::magenta;
	}
	return CColor::white;
}
