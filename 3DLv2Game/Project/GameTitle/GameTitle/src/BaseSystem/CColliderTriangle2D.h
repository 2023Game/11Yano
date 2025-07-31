#pragma once
#include "CCollider.h"

/// <summary>
/// �O�p�`�R���C�_�[
/// </summary>
class CColliderTriangle2D : public CCollider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�O�p�`�̒��_ 0</param>
	/// <param name="v1">�O�p�`�̒��_ 1</param>
	/// <param name="v2">�O�p�`�̒��_ 2</param>
	/// <param name="isKinematic">true�Ȃ�΁A�Փˎ��ɉ����߂��̉e�����󂯂Ȃ�</param>
	/// <param name="weight">�R���C�_�[�̏d��</param>
	CColliderTriangle2D(CObjectBase* owner, ELayer layer,
		const CVector2& v0, const CVector2& v1, const CVector2& v2,
		bool isKinematic = false, float weight = 1.0f);

	/// <summary>
	/// �O�p�`�R���C�_�[�̐ݒ�
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�O�p�`�̒��_ 0</param>
	/// <param name="v1">�O�p�`�̒��_ 1</param>
	/// <param name="v2">�O�p�`�̒��_ 2</param>
	void Set(CObjectBase* owner, ELayer layer,
		const CVector2& v0, const CVector2& v1, const CVector2& v2);

	/// <summary>
	/// �O�p�`�̒��_���擾
	/// </summary>
	/// <param name="v0">���_1�i�[�p</param>
	/// <param name="v1">���_2�i�[�p</param>
	/// <param name="v2">���_3�i�[�p</param>
	void Get(CVector2* v0, CVector2* v1, CVector2* v2) const;

	// �R���C�_�[�`��
	void Render() override;

protected:
	// �R���C�_�[�̏����X�V
	void UpdateCol() override;

private:
	CVector2 mV[3];	// �O�p�`�̒��_�̔z��
	CVector2 mWV[3];	// �O�p�`�̒��_�̃��[���h���W
};
