#include "CApplication.h"
#include "glut.h" //OpenGL
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMaterial.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include <math.h>

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define MODEL_OBJ "res\\Col.obj","res\\Col.mtl" //モデルデータの指定
#define MODEL_BACKGROUND "res\\BS1.obj", "res\\BS1.mtl"
#define MODEL_GROUND "res\\Yuka.obj", "res\\Yuka.mtl"//うごゆか

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	Clear = false;
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.63f, 0.63f, 0.63f));
	mPlayer.Position(CVector(0.0f, 2.5f, 0.0f));
	mPlayer.Rotation(CVector(0.0f, 0.0f, 0.0f));
	CMatrix matrix;
	matrix.Point();
	mBackGround.Load(MODEL_BACKGROUND);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load(MODEL_OBJ);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	spUi = new CUi();//UIクラスの生成
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();
	//CCollisionManager::Instance()->Collision();
	CTaskManager::Instance()->Collision();
	CVector v0, v1, v2, n; //頂点1，2，3，法線データの作成
	n.Set(0.0f, 1.0f, 0.0f); //法線を上向きで設定する
	v0.Set(0.0f, 0.0f, 0.5f); //頂点1の座標
	v1.Set(1.0f, 0.0f, 0.0f); //頂点2の座標
	v2.Set(0.0f, 0.0f, -0.5f); //頂点3の座標


	CVector e, c, u; //視点、注意点、上方向
	e = mPlayer.Position() + CVector(6.0f, 3.0f, 0.0f); 
	c = mPlayer.Position();
	u = CVector(0.0f, 1.0f, 0.0f);
	//カメラ設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//モデルビュー行列取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//逆行列の取得
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	CTaskManager::Instance()->Delete();
	mBackGround.Render();

	CTaskManager::Instance()->Render();
	CCollisionManager::Instance()->Render();
	if (Clear == false)
	{
		spUi->Time(mTime++);
	}
	
	spUi->Render();//UIの描画

	//落ちたらリスタート
	if (mPlayer.Position().Y() < -14.0f)
	{
		mPlayer.Position(CVector(0.0f, 1.5f, 0.0f));
	}
	if (mPlayer.Position().Y() <= -8.0f && mPlayer.Position().X()<-32.0f && mPlayer.Position().X() > -33.0f)
	{
		Clear = true;
		spUi->Clear();
	}
}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse() {
	return mModelViewInverse;
}

CUi* CApplication::spUi = nullptr;

CUi* CApplication::Ui()
{
	return spUi;//インスタンスのポインタを返す
}

CApplication::~CApplication()
{
	delete spUi;
}