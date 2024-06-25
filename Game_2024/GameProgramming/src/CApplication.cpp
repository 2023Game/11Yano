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
#include "CGround.h"
//#include "CAngle.h"
#include <math.h>

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define MODEL_OBJ "res\\Maru.obj","res\\Maru.mtl" //モデルデータの指定
#define MODEL_BACKGROUND "res\\Stage1.obj", "res\\Stage1.mtl"
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
	mModelGround.Load(MODEL_GROUND);
	new CGround(&mModelGround, CVector(0.0f, 1.0f, -10.0f), CVector(), CVector());
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
	mPlayer.Position(CVector(-30.0f, 2.5f, 0.0f));
	mPlayer.Rotation(CVector(0.0f, 270.0f, 0.0f));
	CMatrix matrix;
	matrix.Point();
	mBackGround.Load(MODEL_BACKGROUND);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load(MODEL_OBJ);
	//new CAngle(&mModel, CVector(-30.0f, 1.5f, 5.0f), CVector(), CVector());
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	mColliderMesh.Set(nullptr, nullptr, &mModelGround);
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
	e = mPlayer.Position() + CVector(6.0f, 2.0f, 0.0f); 
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
	mModelGround.Render();

	CTaskManager::Instance()->Render();
	CCollisionManager::Instance()->Render();
	spUi->Render();//UIの描画


	//落ちたらリスタート
	if (mPlayer.Position().Y() < -10.0f)
	{
		mPlayer.Position(CVector(0.0f, 1.5f, 0.0f));
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