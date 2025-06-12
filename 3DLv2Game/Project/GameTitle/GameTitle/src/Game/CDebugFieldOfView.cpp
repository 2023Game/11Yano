#include "CDebugFieldOfView.h"
#include "Primitive.h"
#include "glut.h"

CDebugFieldOfView::CDebugFieldOfView(CObjectBase* owner,
	float fovAngle, float fovLength, EType type)
	: CObjectBase(ETag::eDebug, ETaskPriority::eDebugFov, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mFovAngle(fovAngle)
	, mFovLength(fovLength)
	, mType(type)
{
}

CDebugFieldOfView::~CDebugFieldOfView()
{
	// 表示対象が存在する場合は自身が削除されたことを表示対象に伝える
	if (mpOwner != nullptr)
	{
		mpOwner->DeleteObject(this);
	}
}

void CDebugFieldOfView::SetOwner(CObjectBase* owner)
{
	mpOwner = owner;
}

void CDebugFieldOfView::Set(float angle, float length, EType type)
{
	mFovAngle = angle;
	mFovLength = length;
	mType = type;
}

void CDebugFieldOfView::Update()
{
}

void CDebugFieldOfView::Render()
{
	switch (mType)
	{
	case EType::eSector:
		// 表示対象がいない場合は描画処理を行わない
		if (mpOwner == nullptr) return;

		// デプステストをオフ
		glDisable(GL_DEPTH_TEST);

		// 強制的に半透明にする
		mColor.A(0.3f);
		// 視野範囲の扇形を描画
		Primitive::DrawSector
		(
			mpOwner->Matrix(),// 表示対象の行列
			-mFovAngle, mFovAngle, // -視野角度～＋視野角度の範囲を設定
			mFovLength, // 視野距離
			mColor // 扇形の色
		);
		// デプステストの状態を戻す
		glEnable(GL_DEPTH_TEST);
		break;
	case EType::eCone:
		// 表示対象がいない場合は描画処理を行わない
		if (mpOwner == nullptr) return;

		// デプステストをオフ
		glDisable(GL_DEPTH_TEST);

		// 強制的に半透明にする
		mColor.A(0.3f);
		// 視野範囲の円錐を描画
		Primitive::DrawCone
		(
			mpOwner->Position() + CVector(0.0f, -30.0f, 0.0f), // 円錐の底面中心を設定
			mpOwner->Position(),// 円錐の頂点
			mFovLength, // 底面の半径
			mColor // 色
		);
		// デプステストの状態を戻す
		glEnable(GL_DEPTH_TEST);
		break;
	}
}
