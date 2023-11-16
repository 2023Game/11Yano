#include "CCollider.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) {
	mpParent = parent;//親設定
	mpMatrix = matrix;//親行列設定
	mPosition = position;//位置
	mRadius = radius;//半径設定
}

CCharacter3* CCollider::Parent() {
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	CVector pos = mPosition * *mpMatrix;//コライダの中心座標計算
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());//中心座標へ移動
	float c[] = { 1.0f,0.0f,0.0f,1.0f };//DIFFUSE赤色設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glutWireSphere(mRadius, 16, 16);//球描画
	glPopMatrix();
}