#include "Primitive.h"
#include <glut.h>
#include "CMatrix.h"
#include "Maths.h"

// 線分を描画（3D）
void Primitive::DrawLine(const CVector& s, const CVector& e,
	const CColor& color, float lineWidth, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	// ブレンド処理を有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE赤色設定
	float c[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glLineWidth(lineWidth);
	// 線分を描画
	glBegin(GL_LINES);
	glVertex3f(s.X(), s.Y(), s.Z());
	glVertex3f(e.X(), e.Y(), e.Z());
	glEnd();
	glLineWidth(1.0f);

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理を無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

// 線分を描画（2D）
void Primitive::DrawLine2D(const CVector2& s, const CVector2& e,
	const CColor& color, float lineWidth, EBlend blend)
{
}

// 球を描画
void Primitive::DrawSphere(const CMatrix& m, float rad,
	const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	CMatrix sm;
	sm.Scale(rad, rad, rad);
	// 描画行列を反映
	glMultMatrixf((sm * m).M());

	// ブレンド処理を有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE赤色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	const int cut = 32;
	CVector* vertex = new CVector[cut * cut * 4];
	float* s = new float[cut + 1];
	float* c = new float[cut + 1];
	for (int i = 0; i <= cut; ++i)
	{
		s[i] = sinf((float)M_PI * 2 * i / cut);
		c[i] = cosf((float)M_PI * 2 * i / cut);
	}

	int idx = 0;
	for (int i = 0; i < cut; ++i)
	{
		const float& is1 = s[i];
		const float& is2 = s[i + 1];
		const float& ic1 = c[i];
		const float& ic2 = c[i + 1];
		for (int j = 0; j < cut; ++j)
		{
			const float& js1 = s[j];
			const float& js2 = s[j + 1];
			const float& jc1 = c[j];
			const float& jc2 = c[j + 1];

			vertex[idx] = CVector(js1 * is1, ic1, jc1 * is1);
			vertex[idx + 1] = CVector(js2 * is1, ic1, jc2 * is1);
			vertex[idx + 2] = CVector(js2 * is2, ic2, jc2 * is2);
			vertex[idx + 3] = CVector(js1 * is2, ic2, jc1 * is2);
			idx += 4;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glDrawArrays(GL_QUADS, 0, cut * cut * 4);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] vertex;
	delete[] s;
	delete[] c;

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理を無効化
	Blend::DisableBlend();
	// アルファブレンド無効
	glDisable(GL_BLEND);

	// 描画前の行列に戻す
	glPopMatrix();
}

// ワイヤーフレームの球を描画
void Primitive::DrawWireSphere(const CMatrix& m, float rad,
	const CColor& color, EBlend blend)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	DrawSphere(m, rad, color, blend);
	glPolygonMode(GL_FRONT, GL_FILL);
}

// 三角形を描画
void Primitive::DrawTriangle(const CVector& v0, const CVector& v1, const CVector& v2,
	const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	// ブレンド処理を有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE赤色設定
	float c[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	// 三角形を描画
	glBegin(GL_TRIANGLES);
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());
	glEnd();

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理を無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

// 板ポリゴンを描画
void Primitive::DrawQuad(const CMatrix& m, const CVector2& size,
	const CColor& color, EBlend blend)
{
	// 板ポリゴンの4頂点
	static const CVector v[4] =
	{
		{ -0.5f, 0.0f, -0.5f },
		{ -0.5f, 0.0f,  0.5f },
		{  0.5f, 0.0f,  0.5f },
		{  0.5f, 0.0f, -0.5f },
	};

	// 現在の行列を退避しておく
	glPushMatrix();

	// 描画行列反映
	glMultMatrixf(m.M());

	// ブレンド処理を有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE赤色設定
	float c[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	// 板ポリゴンを描画
	glBegin(GL_QUADS);
	glVertex3f(v[0].X() * size.X(), v[0].Y(), v[0].Z() * size.Y());
	glVertex3f(v[1].X() * size.X(), v[1].Y(), v[1].Z() * size.Y());
	glVertex3f(v[2].X() * size.X(), v[2].Y(), v[2].Z() * size.Y());
	glVertex3f(v[3].X() * size.X(), v[3].Y(), v[3].Z() * size.Y());
	glEnd();

	// ライトオン
	glEnable(GL_LIGHTING);
	// アルファブレンド無効
	glDisable(GL_BLEND);
	// ブレンド処理を無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

// カプセルを描画
void Primitive::DrawCapsule(const CVector& sp, const CVector& ep, float rad,
	const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	float height = CVector::Distance(sp, ep);

	// ブレンド処理を有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE赤色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	const int cut = 32;
	int vtxCnt = cut * cut * 4 + cut * 8;
	CVector* vertex = new CVector[vtxCnt];
	float* s = new float[cut + 1];
	float* c = new float[cut + 1];
	for (int i = 0; i <= cut; ++i)
	{
		s[i] = sinf((float)M_PI * 2 * i / cut);
		c[i] = cosf((float)M_PI * 2 * i / cut);
	}

	CVector up = (ep - sp).Normalized();
	CVector sd = CVector::Cross(up, CVector::up).Normalized();
	if (sd.LengthSqr() == 0.0f)
	{
		sd = CVector::Cross(up, CVector::forward).Normalized();
	}
	CVector fw = CVector::Cross(sd, up).Normalized();

	int idx = 0;
	// 始点と終点
	for (int i = 0; i < 2; ++i)
	{
		CVector offset = i == 0 ? sp : ep;
		for (int j = 0; j < cut / 2; ++j)
		{
			float sj0 = s[j + 0] * (i == 0 ? -1.0f : 1.0f);
			float sj1 = s[j + 1] * (i == 0 ? -1.0f : 1.0f);
			float cj0 = c[j + 0];
			float cj1 = c[j + 1];
			for (int k = 0; k < cut; ++k)
			{
				float sk0 = s[k + 0];
				float sk1 = s[k + 1];
				float ck0 = c[k + 0];
				float ck1 = c[k + 1];
				vertex[idx + 0] = offset + (sd * sk0 * cj0 + up * sj0 + fw * ck0 * cj0) * rad;
				vertex[idx + 1] = offset + (sd * sk1 * cj0 + up * sj0 + fw * ck1 * cj0) * rad;
				vertex[idx + 2] = offset + (sd * sk1 * cj1 + up * sj1 + fw * ck1 * cj1) * rad;
				vertex[idx + 3] = offset + (sd * sk0 * cj1 + up * sj1 + fw * ck0 * cj1) * rad;
				idx += 4;
			}
		}
	}

	// 円柱
	for (int i = 0; i < cut; ++i)
	{
		float si0 = s[i + 0];
		float si1 = s[i + 1];
		float ci0 = c[i + 0];
		float ci1 = c[i + 1];
		vertex[idx + 0] = sp + (sd * si0 + fw * ci0) * rad;
		vertex[idx + 1] = sp + (sd * si1 + fw * ci1) * rad;
		vertex[idx + 2] = ep + (sd * si1 + fw * ci1) * rad;
		vertex[idx + 3] = ep + (sd * si0 + fw * ci0) * rad;

		vertex[idx + 4] = ep + (sd * si0 + fw * ci0) * rad;
		vertex[idx + 5] = ep + (sd * si1 + fw * ci1) * rad;
		vertex[idx + 6] = sp + (sd * si1 + fw * ci1) * rad;
		vertex[idx + 7] = sp + (sd * si0 + fw * ci0) * rad;

		idx += 8;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glDrawArrays(GL_QUADS, 0, vtxCnt);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] vertex;
	delete[] s;
	delete[] c;

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理を無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

// ワイヤーフレームのカプセルを描画
void Primitive::DrawWireCapsule(const CVector& sp, const CVector& ep, float rad,
	const CColor& color, EBlend blend)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	DrawCapsule(sp, ep, rad, color, blend);
	glPolygonMode(GL_FRONT, GL_FILL);
}

// 扇形を描画
void Primitive::DrawSector(const CMatrix& m, float startAngle, float endAngle,
	float rad, const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	CMatrix sm;
	sm.Scale(rad, rad, rad);
	// 描画行列を反映
	glMultMatrixf((sm * m).M());

	// ブレンド処理有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	float start = Math::DegreeToRadian(startAngle);
	float end = Math::DegreeToRadian(endAngle);

	const int cut = 45;
	CVector* vertex = new CVector[cut * 3];
	float* s = new float[cut + 1];
	float* c = new float[cut + 1];
	for (int i = 0; i <= cut; ++i)
	{
		s[i] = sinf(Math::Lerp(start, end, (float)i / cut));
		c[i] = cosf(Math::Lerp(start, end, (float)i / cut));
	}

	int idx = 0;
	for (int i = 0; i < cut; ++i)
	{
		const float& is1 = s[i];
		const float& is2 = s[i + 1];
		const float& ic1 = c[i];
		const float& ic2 = c[i + 1];
		vertex[idx] = CVector::zero;
		vertex[idx + 1] = CVector(is1, 0.0f, ic1);
		vertex[idx + 2] = CVector(is2, 0.0f, ic2);
		idx += 3;
	}

	// 扇形を描画
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glDrawArrays(GL_TRIANGLES, 0, cut * 3);
	glDisableClientState(GL_VERTEX_ARRAY);

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();

	delete[] vertex;
	delete[] s;
	delete[] c;
}

// ボックスの頂点データ
CVector boxVtx[8] =
{
	CVector(0.5f, -0.5f, -0.5f),
	CVector(0.5f, -0.5f,  0.5f),
	CVector(-0.5f, -0.5f,  0.5f),
	CVector(-0.5f, -0.5f, -0.5f),

	CVector(-0.5f,  0.5f, -0.5f),
	CVector(-0.5f,  0.5f,  0.5f),
	CVector(0.5f,  0.5f,  0.5f),
	CVector(0.5f,  0.5f, -0.5f),
};

// ボックス描画用のインデックスデータ
int boxIdx[24] =
{
	0, 1, 2, 3,
	4, 5, 6, 7,
	7, 6, 1, 0,
	5, 4, 3, 2,
	0, 3, 4, 7,
	6, 5, 2, 1,
};

// ワイヤーボックス描画用のインデックスデータ
int boxWireIdx[24] =
{
	0, 1, 1, 2, 2, 3, 3, 0,
	4, 5, 5, 6, 6, 7, 7, 4,
	0, 7, 1, 6, 2, 5, 3, 4,
};


// ボックスを描画
void Primitive::DrawBox(const CVector& center, const CVector& size, const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	CMatrix tm;
	tm.Translate(center);
	CMatrix sm;
	sm.Scale(size);
	// 描画行列を反映
	glMultMatrixf((sm * tm).M());

	// ブレンド処理有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	// 扇形を描画
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, boxVtx);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, boxIdx);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

// ワイヤーフレームのボックスを描画
void Primitive::DrawWireBox(const CVector& center, const CVector& size, const CColor& color, EBlend blend)
{
	// 現在の行列を退避しておく
	glPushMatrix();

	CMatrix tm;
	tm.Translate(center);
	CMatrix sm;
	sm.Scale(size);
	// 描画行列を反映
	glMultMatrixf((sm * tm).M());

	// ブレンド処理有効化
	Blend::EnableBlend(blend);
	// ライトオフ
	glDisable(GL_LIGHTING);

	// DIFFUSE色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	// 扇形を描画
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, boxVtx);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, boxWireIdx);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// ライトオン
	glEnable(GL_LIGHTING);
	// ブレンド処理無効化
	Blend::DisableBlend();

	// 描画前の行列に戻す
	glPopMatrix();
}

void Primitive::DrawCone(const CVector& sp, const CVector& ep, float rad, const CColor& color, EBlend blend)
{
	glPushMatrix();

	float height = CVector::Distance(sp, ep);

	// ブレンド処理有効化
	Blend::EnableBlend(blend);
	glDisable(GL_LIGHTING);

	// 色設定
	float col[] = { color.R(), color.G(), color.B(), color.A() };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	glColor4fv(col);

	const int cut = 32;
	int vtxCnt = cut * 3 + cut; // 側面用三角形 + 底面用ファン
	CVector* vertex = new CVector[vtxCnt];

	// 単位円の座標テーブル
	float* s = new float[cut + 1];
	float* c = new float[cut + 1];
	for (int i = 0; i <= cut; ++i) {
		s[i] = sinf((float)M_PI * 2 * i / cut);
		c[i] = cosf((float)M_PI * 2 * i / cut);
	}

	// up = 頂点方向
	CVector up = (ep - sp).Normalized();
	CVector sd = CVector::Cross(up, CVector::up).Normalized();
	if (sd.LengthSqr() == 0.0f) {
		sd = CVector::Cross(up, CVector::forward).Normalized();
	}
	CVector fw = CVector::Cross(sd, up).Normalized();

	int idx = 0;

	// 側面
	for (int i = 0; i < cut; ++i) {
		float si0 = s[i];
		float ci0 = c[i];
		float si1 = s[(i + 1) % cut];
		float ci1 = c[(i + 1) % cut];

		// 底面の2点（円周）
		CVector p0 = sp + (sd * si0 + fw * ci0) * rad;
		CVector p1 = sp + (sd * si1 + fw * ci1) * rad;

		// 三角形（円周2点 → 頂点）
		vertex[idx++] = p0;
		vertex[idx++] = p1;
		vertex[idx++] = ep;
	}

	//  底面（円形）
	for (int i = 0; i < cut; ++i) {
		float si0 = s[i];
		float ci0 = c[i];

		vertex[idx++] = sp + (sd * si0 + fw * ci0) * rad;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex);

	// 側面の三角形群
	glDrawArrays(GL_TRIANGLES, 0, cut * 3);

	// 底面（三角ファン）
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(sp.X(), sp.Y(), sp.Z()); // 中心
	for (int i = 0; i <= cut; ++i) {
		CVector v = vertex[cut * 3 + (i % cut)];
		glVertex3f(v.X(), v.Y(), v.Z());
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] vertex;
	delete[] s;
	delete[] c;

	glEnable(GL_LIGHTING);
	Blend::DisableBlend();
	glPopMatrix();
}