#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

class CFont;

class CHackGame2 : public CTask
{
public:
	void Start();
	CHackGame2();
	~CHackGame2();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool mIsClear;
private:
	CImage* mpBackground;
	bool mIsOpened;


	CFont* mpLogoFont;	// ���S�̃t�H���g
	CText* mpTypeLogo;	// �^�C�s���O���S
	char mText; // �^�C�s���O�Q�[���̃e�L�X�g

	int mInputNum;
};