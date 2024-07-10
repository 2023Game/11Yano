#pragma once
#include "CTexture.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include <vector>
#include "CSound.h"
#include "CVector.h"
#include "CModel.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CColliderTriangle.h"
#include "CColliderMesh.h"
#include "CUi.h"
#include "CModelX.h"
#include "CXPlayer.h"

class CApplication
{
private:
	CXPlayer mXPlayer;//�L�����N�^�̃C���X�^���X
	CMatrix mMatrix;
	CModelX mModelX;
	static CUi* spUi;//UI�N���X�̃|�C���^
	CColliderMesh mColliderMesh;
	//���f���r���[�̋t�s��
	static CMatrix mModelViewInverse;
	CModel mModelC5;//C5���f��
	CPlayer mPlayer;
	CModel mBackGround; //�w�i���f��
	CModel mModel;
	CVector mEye;
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
//	CCharacter mRectangle;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CEnemy* mpEnemy;
//	CBullet* mpBullet;
	CInput mInput;
	CFont mFont;
	//CCharacter�̃|�C���^�̉ϒ��z��
//	std::vector<CCharacter*> mCharacters;
public:
	~CApplication();
	static CUi* Ui();//UI�N���X�̃C���X�^���X�擾
	static const CMatrix& ModelViewInverse();
	static CTexture* Texture();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};