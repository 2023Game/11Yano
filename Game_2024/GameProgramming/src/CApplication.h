#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CInput.h"
#include <vector>
#include "CCharacterManager.h"
#include "CSound.h"
#include "CVector.h"
#include "CModel.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CColliderTriangle.h"
#include "CColliderMesh.h"
#include "CUi.h"
//#include "CAngle.h"

class CApplication
{
private:
	//CAngle mAngle;
	static CUi* spUi;//UI�N���X�̃|�C���^
	CColliderMesh mColliderMesh;
	//���f���r���[�̋t�s��
	static CMatrix mModelViewInverse;
	CModel mModelGround;//�����䂩
	CPlayer mPlayer;
	CModel mBackGround; //�w�i���f��
	CModel mModel;
	CVector mEye;
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[
	static CCharacterManager mCharacterManager;
	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CInput mInput;
public:
	~CApplication();
	static CUi* Ui();//UI�N���X�̃C���X�^���X�擾
	static const CMatrix& ModelViewInverse();
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};