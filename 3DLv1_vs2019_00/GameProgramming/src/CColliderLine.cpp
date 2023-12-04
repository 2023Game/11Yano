#include "CColliderLine.h"
#include "CCollisionManager.h"

CColliderLine::CColliderLine(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1) {
	Set(parent, matrix, v0, v1);
}

void CColliderLine::Set(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1) {
	mType = EType::ELINE;//線分コライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//線分頂点設定
	mV[0] = v0;
	mV[1] = v1;
}

void CColliderLine::Render() {
	glPushMatrix();//行列退避
	glMultMatrixf(mpMatrix->M());//行列適用
	glEnable(GL_BLEND);//アルファブレンド有効
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//ブレンド方法指定
	glDisable(GL_LIGHTING);//ライトオフ
	//DIFFUSE赤色設定
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);
	//線分描画
	glBegin(GL_LINES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glEnd();
	glEnable(GL_LIGHTING);//ライトオン
	glDisable(GL_ALPHA);//アルファブレンド無効
	glPopMatrix();//行列復帰
}