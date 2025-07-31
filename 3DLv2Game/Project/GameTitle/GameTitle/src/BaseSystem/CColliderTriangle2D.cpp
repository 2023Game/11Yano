#include "CColliderTriangle2D.h"
#include "glut.h"
#include "Maths.h"
#include "CColor.h"
#include "CMatrix2.h"

// コンストラクタ
CColliderTriangle2D::CColliderTriangle2D(CObjectBase* owner, ELayer layer,
	const CVector2& v0, const CVector2& v1, const CVector2& v2,
	bool isKinematic, float weight)
	: CCollider(owner, layer, EColliderType::eTriangle, isKinematic, weight)
{
	// 三角形の頂点を設定
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// 三角形コライダーの設定
void CColliderTriangle2D::Set(CObjectBase* owner, ELayer layer,
	const CVector2& v0, const CVector2& v1, const CVector2& v2)
{
	CCollider::Set(owner, layer);

	// 三角形の頂点を設定
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// 三角形の頂点を取得
void CColliderTriangle2D::Get(CVector2* v0, CVector2* v1, CVector2* v2) const
{
	*v0 = mWV[0];
	*v1 = mWV[1];
	*v2 = mWV[2];
}

// コライダー描画
void CColliderTriangle2D::Render()
{
	glPushMatrix();

	// 2D変換行列を適用（仮に Matrix2().M() が float[16] を返す場合）
	glMultMatrixf(Matrix2().M());

	// アルファブレンドを有効にする
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

	CColor col = CColor::red;
	if (!IsEnable()) col = CColor::gray;
	col.A(0.2f);
	float* c = (float*)&col;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glBegin(GL_TRIANGLES);
	glVertex2f(mV[0].X(), mV[0].Y());
	glVertex2f(mV[1].X(), mV[1].Y());
	glVertex2f(mV[2].X(), mV[2].Y());
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPopMatrix();
}

// コライダーの情報を更新
void CColliderTriangle2D::UpdateCol()
{
	// 行列を反映した各頂点の座標を計算
	CMatrix2 m = Matrix2();
	mWV[0] = mV[0] * m;
	mWV[1] = mV[1] * m;
	mWV[2] = mV[2] * m;

	// バウンディングボックスを更新
	mBounds2D = CBounds2D::GetTriangleBounds(mWV[0], mWV[1], mWV[2]);
}