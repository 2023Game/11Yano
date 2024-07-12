#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"

CCollider::CCollider()
	:mpParent(nullptr)
	,mpMatrix(&mMatrix)
	,mType(EType::ESPHERE)
	,mRadius(0)
{
	CCollisionManager::Instance()->Add(this);
}

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) 
	:CCollider()
{
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

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//面の法線を外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//三角の頂点から線分支店へのベクトルを求める
	CVector v0sv = sv - v[0];
	//三角の頂点から線分終点へのベクトルを求める
	CVector v0ev = ev - v[0];
	//線分画面と交差しているか内積で確認
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差していない
	if (dots * dote >= 0.0f) {
		//衝突していない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//好転の計算
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));
	//好転が三角形なら衝突している
	// 頂点１頂点２ベクトルと頂点１交点ベクトルとの外積を求め
	// 法線との内積がマイナスなら三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//衝突していない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点２頂点3ベクトルと頂点２交点ベクトルの外積を求め
	// 法線との内積がマイナスなら三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点３頂点１ベクトルと頂点３交点ベクトルとの外積を求め
	// 法線との内積がマイナスなら三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//交差しているので調整池計算
	if (dots < 0.0f) {
		//視点が裏面
		*a = normal * -dots;
	}
	else {
		//終点が裏面
		*a = normal * -dote;
	}
	return true;
}

CCollider::EType CCollider::Type() {
	return mType;
}

bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this);//いったん削除
	CCollisionManager::Instance()->Add(this);//追加
}

void CCollider::ChangePriority()
{
	//自分の座標ｘ親の変更行列を掛けてワールド座標を求める
	CVector pos = mPosition * *mpMatrix;
	//ベクトルの長さが優先度
	CCollider::ChangePriority(pos.Length());
}

void CCollider::Matrix(CMatrix* m) {
	mpMatrix = m;
}