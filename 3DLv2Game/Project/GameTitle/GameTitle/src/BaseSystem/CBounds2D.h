#pragma once

// �o�E���f�B���O�{�b�N�X���
class CBounds2D
{
public:
	// �R���X�g���N�^
	CBounds2D();
	// �f�X�g���N�^
	~CBounds2D();


	void SetRange(const CVector2& min, const CVector2& max);
	/// ���S�ʒu�ƃT�C�Y�Őݒ�
	/// </summary>
	/// <param name="center">���S�ʒu</param>
	/// <param name="size">�T�C�Y</param>
	void SetPos(const CVector2& center, const CVector2& size);

	// �ŏ��ʒu��ݒ�
	void Min(const CVector2& min);
	// �ŏ��ʒu���擾
	const CVector2& Min() const;
	// �ő�ʒu��ݒ�
	void Max(const CVector2& max);
	// �ő�ʒu���擾
	const CVector2& Max() const;

	// ���S�ʒu��ݒ�
	void Center(const CVector2& center);
	// ���S�ʒu���擾
	CVector2 Center() const;
	// �T�C�Y��ݒ�
	void Size(const CVector2& size);
	// �T�C�Y���擾
	CVector2 Size() const;

	/// <summary>
	/// 2�̃o�E���f�B���O�{�b�N�X���������邩�ǂ���
	/// </summary>
	/// <param name="b0">1�ڂ̃o�E���f�B���O�{�b�N�X</param>
	/// <param name="b1">2�ڂ̃o�E���f�B���O�{�b�N�X</param>
	/// <returns>true�Ȃ�΁A�������Ă���</returns>
	static bool Intersect(const CBounds2D& b0, const CBounds2D& b1);

	
	/// <summary>
	/// �~�̃o�E���f�B���O�{�b�N�X���擾
	/// </summary>
	/// <param name="pos">�~�̍��W</param>
	/// <param name="rad">�~�̔��a</param>
	/// <returns>�o�E���f�B���O�{�b�N�X</returns>
	static CBounds2D GetCircleBounds(const CVector2& pos, float rad);
	
private:
	CVector2 mMin;	// �ŏ��ʒu
	CVector2 mMax;	// �ő�ʒu

};
