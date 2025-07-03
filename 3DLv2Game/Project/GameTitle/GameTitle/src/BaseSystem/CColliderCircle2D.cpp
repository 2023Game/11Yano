#include "CColliderCircle2D.h"
#include <glut.h>
#include "CColor.h"

CColliderCircle2D::CColliderCircle2D(CObjectBase* owner, ELayer layer, float radius, bool isKinematic, float weight)
	: CCollider(owner, layer, EColliderType::eCircle, isKinematic, weight)
	, mRadius(radius)
	, mpOwner(owner)
{
}

void CColliderCircle2D::Set(CObjectBase* owner, ELayer layer, float radius)
{
	CCollider::Set(owner, layer);

	// 半径を設定
	mRadius = radius;
}

void CColliderCircle2D::Get(CVector2* pos, float* rad) const
{
	*pos = mWPos;
	*rad = mWRadius;
}

void CColliderCircle2D::Render()
{
	glPushMatrix();

	glTranslatef(mWPos.X(), mWPos.Y(), 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

	CColor col = CColor::red;
	if (!IsEnable()) col = CColor::gray;
	col.A(0.3f);

	glColor4f(col.R(), col.G(), col.B(), col.A());

	const int segments = 64;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = cosf(theta) * mWRadius;
		float y = sinf(theta) * mWRadius;
		glVertex2f(x, y);
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void CColliderCircle2D::UpdateCol()
{

	mWPos = mpOwner->Position2D();
	mWRadius = mRadius;


	// バウンディングボックスを更新
	mBounds2D = CBounds2D::GetCircleBounds(mWPos, mWRadius);
}
