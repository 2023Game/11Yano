#pragma once
//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CRideableObject.h"
#include "CSound.h"
#include "CColliderSphere.h"
#include "CImage.h"

class CInteractObject;
class CGameScene;
/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CXCharacter
{
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CPlayer* Instance();

	// �R���X�g���N�^
	CPlayer();
	// �f�X�g���N�^
	~CPlayer();

	void SetScene(CGameScene* scene) { mpScene = scene; }
	// �X�V
	void Update();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �`��
	void Render();

	bool IsPlaying() const;

private:
	// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
	CVector CalcMoveVec() const;

	// �ҋ@���
	void UpdateIdle();


	// �ړ��̍X�V����
	void UpdateMove();

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTPose,		// T�|�[�Y
		eIdle,		// �ҋ@
		eWalk,		// ���s
		eSneak,     // ���Ⴊ��


		Num
	};
	// �A�j���[�V�����؂�ւ�
	void ChangeAnimation(EAnimType type);

	// �v���C���[�̃C���X�^���X
	static CPlayer* spInstance;

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

	// �v���C���[�̏��
	enum class EState
	{
		eIdle,		// �ҋ@
		eSneak,     // ���Ⴊ��
	};
	EState mState;	// �v���C���[�̏��

	CVector mMoveSpeed;	// �O�㍶�E�̈ړ����x
	float mMoveSpeedY;	// �d�͂�W�����v�ɂ��㉺�̈ړ����x

	bool mIsDash;
	

	CColliderCapsule* mpColliderCapsule; // �v���C���[�̃R���C�_
	CColliderSphere* mpCollider;
	CTransform* mpRideObject;

	CInteractObject* GetNearInteractObj() const;
	std::list<CInteractObject*> mNearInteractObjs;

	CSound* mpSlashSE;
	bool mIsPlayedSlashSE;
	bool mIsSpawnedSlashEffect;

	CImage* mpUIHack;

	bool mIsPlaying;

	CGameScene* mpScene;

};
