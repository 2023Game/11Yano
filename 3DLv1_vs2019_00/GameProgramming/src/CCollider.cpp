#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) {
	mpParent = parent;//親設定
	mpMatrix = matrix;//親行列設定
	mPosition = position;//位置
	mRadius = radius;//半径設定
	CCollisionManager::Instance()->Add(this);
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

CCollider::~CCollider() {
	CCollisionManager::Instance()->Remove(this);
}

bool CCollider::Collision(CCollider* m, CCollider* o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	mpos = mpos - opos;//中心から中心のベクトルを求める
	if (m->mRadius + o->mRadius > mpos.Length()) {
		return true;//衝突している
	}
	return false;//衝突していない
}