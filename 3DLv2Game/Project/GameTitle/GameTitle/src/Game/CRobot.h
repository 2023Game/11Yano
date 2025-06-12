#ifndef CROBOT_H
#define CROBOT_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"

// ����͈͂̃f�o�b�O�\���N���X�̑O�錾
class CDebugFieldOfView;
class CNavNode;

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CRobot : public CXCharacter
{
public:
	// �R���X�g���N�^
	CRobot(std::vector<CVector> patrolPoints);
	~CRobot();
	void DeleteObject(CObjectBase* obj);
	// �X�V����
	void Update() override;
	void Render() override;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	
	enum class EAnimType
	{
		None = -1,

		eTpose,
		eIdle,
		eWalk,
		eRun,
		eAttack,
		eDie,

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
		eIdle,		// �ҋ@
		ePatrol,    //  ����
		eChase,     // �v���C���[��ǂ�������
		eLost,      // �v���C���[��������
		eAttack,	// �U��
		eDie,       // ��
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);

	// �v���C���[������͈͓��ɓ��������ǂ���
	bool IsFoundPlayer() const;
	// �v���C���[�������Ă��邩
	bool IsLookPlayer() const;
	// �v���C���[���U���ł��邩
	bool CanAttackPlayer() const;
	
	// �w�肵���ʒu�܂ňړ�����
	bool MoveTo(const CVector& targetPos, float speed);
	// ���ɏ��񂷂�|�C���g��ύX
	void ChangePatrolPoint();

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

	CColliderCapsule* mpColliderCapsule; // �c�����̐����R���C�_
	//CColliderLine* mpColliderLineX; // ������(X)�̐����R���C�_
	//CColliderLine* mpColliderLineZ; // ������(Z)�̐����R���C�_

	std::vector<CNavNode*> mMoveRoute;// ���߂��ŒZ�o�H�L���p
	int mNextMoveIndex; // ���Ɉړ�����m�[�h�̃C���f�b�N�X�l

	float mBulletTime;

	bool mDie;
};

#endif
