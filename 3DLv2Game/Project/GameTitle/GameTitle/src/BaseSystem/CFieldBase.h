#pragma once

class CFieldBase
{
public:
	CFieldBase();
	~CFieldBase();
	//�C���X�^���X�̃|�C���^�̎擾
	static CFieldBase* Instance();

	// ���C�ƃt�B�[���h�I�u�W�F�N�g�Ƃ̏Փ˔���
	virtual bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit);
private:
	static CFieldBase* spInstance;
};