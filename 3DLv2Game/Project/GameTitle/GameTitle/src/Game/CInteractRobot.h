#pragma once
#ifndef CINTERACTROBOT_H
#define CINTERACTROBOT_H
#include "CInteractObject.h"
#include "CColliderCapsule.h"
#include "CImage.h"
#include "CColliderSphere.h"
#include "CCollider.h"

// ����͈͂̃f�o�b�O�\���N���X�̑O�錾
class CDebugFieldOfView;
class CNavNode;
class CHackGame2;
class CSceneBase;

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CInteractRobot : public CInteractObject
{
public:
	// �R���X�g���N�^
	CInteractRobot();
	~CInteractRobot();
	void DeleteObject(CObjectBase* obj);
	// �X�V����
	void Update() override;
	void Render() override;
	void Interact() override;
	bool IsClear() const;
	void SetScene(CSceneBase* scene) { mpScene = scene; }

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
	CVector CalcMoveVec() const;

	// �ړ��̍X�V����
	void UpdateMove();

	enum class EAnimType
	{
		None = -1,

		eTpose,
		eIdle,
		eWalk,
		eRun,
		eAttack,
		eDown,
		eWait,

		Num
	};
	void ChangeAnimation(EAnimType type);

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

	// �G�̏��
	enum class EState
	{
		eWait,       // �ҋ@��
		ePlay,   // ���쒆
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);

	// �w�肵���ʒu�܂ňړ�����
	bool MoveTo(const CVector& targetPos, float speed);
	// ���ɏ��񂷂�|�C���g��ύX
	void CHangePatrolPoint();

	// �ҋ@��Ԏ��̍X�V����
	void UpdateIdle();
	// ���񒆂̍X�V����
	void UpdatePatrol();
	// �ǐՒ��̍X�V����
	void UpdateChase();
	// �����������̍X�V����
	void UpdateLost();
	// �U�����̍X�V����
	void UpdateAttack();

	// ��Ԃ̕�������擾
	std::string GetStateStr(EState state) const;
	//��Ԃ̐F���擾
	CColor GetStateColor(EState state) const;

	CVector mMoveSpeed;	// �O�㍶�E�̈ړ����x
	float mMoveSpeedY;	// �d�͂�W�����v�ɂ��㉺�̈ړ����x

	bool mIsGrounded;	// �ڒn���Ă��邩�ǂ���
	CVector mGroundNormal;	// �ڒn���Ă���n�ʂ̖@��

	EState mState;	// �G�̏��
	int mStateStep; // ��ԓ��̃X�e�b�v�Ǘ�
	float mElapsedTime; // �o�ߎ��Ԍv���p

	float mFovAngle; // ����͈͂̊p�x
	float mFovLength; // ����͈͂̋���
	CDebugFieldOfView* mpDebugFov; // ����͈͂̃f�o�b�O�\��

	CNavNode* mpLostPlayerNode; // �v���C���[�����������ʒu�̃m�[�h

	// ����|�C���g�̃��X�g
	std::vector<CNavNode*> mPatrolPoints;
	int mNextPatrolIndex; // ���ɏ��񂷂�|�C���g�̔ԍ�

	CColliderCapsule* mpColliderCapsule;
	CColliderSphere* mpColliderSphere;
	CVector mpTargetPos;
	bool mIsTarget;
	CObjectBase* mpTarget;

	std::vector<CNavNode*> mMoveRoute;// ���߂��ŒZ�o�H�L���p
	int mNextMoveIndex; // ���Ɉړ�����m�[�h�̃C���f�b�N�X�l

	CHackGame2* mpHackGame;
	bool mIsHack;
	bool mIsClear;

	float mBulletTime;

	CSceneBase* mpScene;
	CImage* mpImage;
};

#endif
