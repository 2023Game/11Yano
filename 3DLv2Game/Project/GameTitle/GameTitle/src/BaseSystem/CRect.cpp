#include "CRect.h"

// コンストラクタ（引数なし）
CRect::CRect()
	: CRect(CVector2::zero, CVector2(100.0f, 100.0f))
{
}

// コンストラクタ（xywh）
CRect::CRect(float x, float y, float w, float h)
	: CRect(CVector2(x, y), CVector2(w, h))
{
}

// コンストラクタ（pos + size）
CRect::CRect(const CVector2& pos, const CVector2& size)
	: mPosition(pos)
	, mSize(size)
{
}

// デストラクタ
CRect::~CRect()
{
}

// 矩形情報の設定
void CRect::Set(float x, float y, float w, float h)
{
	Set(CVector2(x, y), CVector2(w, h));
}

// 矩形情報の設定（CVector2）
void CRect::Set(const CVector2& pos, const CVector2& size)
{
	SetPos(pos);
	SetSize(size);
}

// 矩形の開始位置を設定
void CRect::SetPos(float x, float y)
{
	SetPos(CVector2(x, y));
}

// 矩形の開始位置を設定（CVector2）
void CRect::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

// 矩形の開始位置を取得
const CVector2& CRect::GetPos() const
{
	return mPosition;
}

// 矩形のサイズを設定
void CRect::SetSize(float w, float h)
{
	SetSize(CVector2(w, h));
}

// 矩形のサイズを設定（CVector2）
void CRect::SetSize(const CVector2& size)
{
	mSize = size;
}

// 矩形のサイズを取得
const CVector2& CRect::GetSize() const
{
	return mSize;
}

float CRect::X() const
{
	return mPosition.X();
}

void CRect::X(float x)
{
	mPosition.X(x);
}

float CRect::Y() const
{
	return mPosition.Y();
}

void CRect::Y(float y)
{
	mPosition.Y(y);
}

float CRect::W() const
{
	return mSize.X();
}

void CRect::W(float w)
{
	mSize.X(w);
}

float CRect::H() const
{
	return mSize.Y();
}

void CRect::H(float h)
{
	mSize.Y(h);
}

float CRect::Left() const
{
	return mPosition.X();
}

float CRect::Right() const
{
	return mPosition.X() + mSize.X();
}

float CRect::Top() const
{
	return mPosition.Y();
}

float CRect::Bottom() const
{
	return mPosition.Y() + mSize.Y();
}

bool CRect::Collision(CRect* r, float* ax, float* ay)
{
	if (X() < r->X())
		*ax = r->X() - X() - W() - r->W();
	else
		*ax = X() - r->X() - W() - r->W();
	//0以上は衝突しない
	if (*ax >= 0.0f)
		return false;
	if (Y() < r->Y())
		*ay = r->Y() - Y() - H() - r->H();
	else
		*ay = Y() - r->Y() - H() - r->H();
	//0以上は衝突しない
	if (*ay >= 0.0f)
		return false;

	//Yが短いか判定
	if (*ax < *ay)
	{//Y修正、Xは0
		*ax = 0.0f;
		//上の時
		if (Y() > r->Y())
			*ay = -*ay;
	}
	else
	{//X修正、Yは0
		*ay = 0.0f;
		//上の時
		if (X() > r->X())
			*ax = -*ax;
	}
	return true;
}