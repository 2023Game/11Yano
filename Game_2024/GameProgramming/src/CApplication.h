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
	static CUi* spUi;//UIクラスのポインタ
	CColliderMesh mColliderMesh;
	//モデルビューの逆行列
	static CMatrix mModelViewInverse;
	CModel mModelGround;//うごゆか
	CPlayer mPlayer;
	CModel mBackGround; //背景モデル
	CModel mModel;
	CVector mEye;
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//ゲームオーバー
	static CCharacterManager mCharacterManager;
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};
	EState mState;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CInput mInput;
public:
	~CApplication();
	static CUi* Ui();//UIクラスのインスタンス取得
	static const CMatrix& ModelViewInverse();
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};