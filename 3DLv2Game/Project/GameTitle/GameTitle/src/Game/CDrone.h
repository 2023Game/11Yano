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

	bool IsPlayerChase() const override;
	bool IsPlayerLost() const override;

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
	// �v���C���[�������Ă��邩(��Q�����Ȃ���)
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


	/*�@��ԊǗ� */
	EState mState;
	int mStateStep; // ��ԓ��̃X�e�b�v�Ǘ�
	float mElapsedTime; // �o�ߎ��Ԍv���p
	bool mStop; // �@�\��~�t���O

	/*�@�m�[�h�n�@*/
	CNavNode* mpLostPlayerNode; // �v���C���[�����������ʒu�̃m�[�h
	std::vector<CNavNode*> mPatrolPoints; // ����|�C���g�̃��X�g
	int mNextPatrolIndex; // ���ɏ��񂷂�|�C���g�̔ԍ�
	std::vector<CNavNode*> mMoveRoute;// ���߂��ŒZ�o�H�L���p
	int mNextMoveIndex; // ���Ɉړ�����m�[�h�̃C���f�b�N�X�l

	/*�@����͈́@*/
	float mFovAngle; // ����͈͂̊p�x
	float mFovLength; // ����͈͂̋���
	float mFovHeight; // ����͈͂̍���


	CModel* mpModel;
	CDebugFieldOfView* mpDebugFov; // ����͈͂̃f�o�b�O�\��
	float mBulletTime; // �e�̔��ˊԊu
	
};

#endif