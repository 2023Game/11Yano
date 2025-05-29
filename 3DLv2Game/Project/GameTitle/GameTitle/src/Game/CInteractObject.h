#pragma once
#include "CXCharacter.h"

class CInteractObject : public CXCharacter
{
public: 
	CInteractObject(
		ETaskPriority prio = ETaskPriority::eDefault,
		int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eDefault);
	virtual ~CInteractObject();

	// ���ׂ���Ԃ�
	virtual bool CanInteract() const;
	virtual void Interact() = 0;

	// ���ׂ���e�̃e�L�X�g��Ԃ�
	std::string GetInteractStr() const;

	// �f�o�b�O�\���p�̖��O���擾
	std::string GetDebugName() const;
	// �f�o�b�O�\���p�̖��O��ݒ�
	void SetDebugName(std::string name);
protected:
	std::string mInteractStr; // ���ׂ���e�̃e�L�X�g

#if _DEBUG
	std::string mDebugName;
#endif
};