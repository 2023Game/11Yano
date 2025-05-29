#pragma once
#include "CTask.h"
#include "CImage.h"
#include <vector>
#include <string>

class CFont;

class CHackGame : public CTask
{
public:
	void Start();
	CHackGame();
	~CHackGame();

	void Open();
	void Close();
	bool IsOpened() const;

	void Update() override;
	void Render() override;

	bool IsClear() const;
	
private:
	CImage* mpBackground;
	bool mIsOpened;
	

	CFont* mpLogoFont;	// ���S�̃t�H���g
	CText* mpTypeLogo;	// �^�C�s���O���S
	char mText; // �^�C�s���O�Q�[���̃e�L�X�g

	int mInputNum;

	bool mIsClear;
	CImage* mpPlayer;//��ŏ���
};