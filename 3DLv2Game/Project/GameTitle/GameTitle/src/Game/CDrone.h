#ifndef CDRONE_H
#define CDRONE_H
#include "CXCharacter.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CDebugFieldOfView;
class CNavNode;

class CDrone : public CXCharacter
{
public:
	CDrone(std::vector<CVector> patrolPoints);
	~CDrone();
	void DeleteObject(CObjectBase* obj);
	void Update() override;
	void Render() override;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	void Stop();
private:
	// �G�̏��
	enum class EState
	{
		eIdle,		// �ҋ@
		ePatrol,    //  ����
		eChase,     // �v���C���[��ǂ�������
		eLost,      // �v���C���[��������
		eAttack,	// �U��
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

	
	CColliderMesh* mpColliderMesh;

	// ��Ԃ̕�������擾
	std::string GetStateStr(EState state) const;
	//��Ԃ̐F���擾
	CColor GetStateColor(EState state) const;

	EState mState;
	int mStateStep; // ��ԓ��̃X�e�b�v�Ǘ�
	float mElapsedTime; // �o�ߎ��Ԍv���p
	CDebugFieldOfView* mpDebugFov; // ����͈͂̃f�o�b�O�\��

	CNavNode* mpLostPlayerNode; // �v���C���[�����������ʒu�̃m�[�h

	// ����|�C���g�̃��X�g
	std::vector<CNavNode*> mPatrolPoints;
	int mNextPatrolIndex; // ���ɏ��񂷂�|�C���g�̔ԍ�

	float mFovAngle; // ����͈͂̊p�x
	float mFovLength; // ����͈͂̋���
	float mFovHeight; // ����͈͂̍���

	std::vector<CNavNode*> mMoveRoute;// ���߂��ŒZ�o�H�L���p
	int mNextMoveIndex; // ���Ɉړ�����m�[�h�̃C���f�b�N�X�l

	CModel* mpModel;
	float mBulletTime;
	bool mStop;
};

#endif