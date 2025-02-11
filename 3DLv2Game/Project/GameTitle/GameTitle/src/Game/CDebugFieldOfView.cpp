#include "CDebugFieldOfView.h"
#include "Primitive.h"
#include "glut.h"

CDebugFieldOfView::CDebugFieldOfView(CObjectBase* owner,
	float fovAngle, float fovLength)
	: CObjectBase(ETag::eDebug, ETaskPriority::eDebugFov, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mFovAngle(fovAngle)
	, mFovLength(fovLength)
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

void CDebugFieldOfView::Set(float angle, float length)
{
	mFovAngle = angle;
	mFovLength = length;
}

void CDebugFieldOfView::Update()
{
}

void CDebugFieldOfView::Render()
{
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
}
