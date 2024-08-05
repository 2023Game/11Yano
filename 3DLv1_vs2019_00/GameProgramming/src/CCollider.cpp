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
	const CVector& position, float radius, ETag tag)
	:CCollider()
{
	mTag = tag;//タグの設定
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

CCollider::ETag CCollider::Tag() {
	return mTag;
}

//CalcCalcPointLineDist(点, 始点, 終点, 線上の最短点, 割合)
//点と線（始点、終点を通る直線）の最短距離を求める
float CalcPointLineDist(const CVector& p, const CVector& s, const CVector& e, CVector* mp, float* t)
{
	*t = 0.0f; //割合の初期化
	CVector v = e - s; //始点から終点へのベクトルを求める
	float dvv = v.Dot(v); //ベクトルの長さの2乗を求める
	if (dvv > 0.0f) {
		*t = v.Dot(p - s) / dvv; //線上の垂線となる点の割合を求める
		// 上の式の説明
		// dot(v, p-sp) は |v||p-sp|cosΘ
		// dvvは|v|の２乗
		// 上の計算で、tは |p-sp|cosΘ / |v|となる。
		// つまりtは「dotで投影した長さ÷vの長さ」という割合になる
	}
	*mp = s + v * *t; //線上の垂線となる点を求める
	return (p - *mp).Length(); //垂線の長さを返す
}

//CalcLineLineDist(始点1, 終点1, 始点2, 終点2, 交点1, 交点2, 比率1, 比率2)
//2線間の最短距離を返す
float CalcLineLineDist(
	const CVector& s1, //始点1
	const CVector& e1, //終点1
	const CVector& s2, //始点2
	const CVector& e2, //終点2
	CVector* mp1, //交点1
	CVector* mp2, //交点2
	float* t1, //比率1
	float* t2  //比率2
)
{
	CVector v1 = e1 - s1;
	CVector v2 = e2 - s2;
	//2直線が平行
	if (v1.Cross(v2).Length() < 0.000001f) {
		//線分1の始点から直線2までの最短距離問題に帰着する
		*t1 = 0.0f;
		*mp1 = s1;
		float dist = CalcPointLineDist(*mp1, s2, e2, mp2, t2);
		return dist;
	}
	//2直線が平行でない
	float dv1v2 = v1.Dot(v2);
	float dv1v1 = v1.Dot(v1);
	float dv2v2 = v2.Dot(v2);
	CVector vs2s1 = s1 - s2;
	//比率1を求める
	*t1 = (dv1v2 * v2.Dot(vs2s1) - dv2v2 * v1.Dot(vs2s1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	//交点1を求める
	*mp1 = s1 + v1 * *t1;
	//比率2を求める
	*t2 = v2.Dot(*mp1 - s2) / dv2v2;
	//交点2を求める
	*mp2 = s2 + v2 * *t2;
	//最短距離を返す
	return (*mp2 - *mp1).Length();
}

//0～1の間にクランプ(値を強制的にある範囲内にすること)
void clamp0to1(float& v) {
	if (v < 0.0f)  v = 0.0f;
	else if (v > 1.0f)  v = 1.0f;
}

//2線分間の最短距離
float CalcSegmentSegmentDist
(
	const CVector& s1, const CVector& e1, //線分1
	const CVector& s2, const CVector& e2, //線分2
	CVector* mp1, //最短線の端点1(始点や終点になることもある)
	CVector* mp2 //最短線の端点2(始点や終点になることもある)
)
{
	float dist = 0, t1, t2;
	
	//とりあえず2直線間の最短距離,mp1,mp2,t1,t2を求めてみる
	dist = CalcLineLineDist(s1, e1, s2, e2, mp1, mp2, &t1, &t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2が両方とも線分内にあった
		return dist;
	}
	//mp1,mp2の両方、またはどちらかが線分内になかったので次へ
	//mp1,t1を求め直す ⇒ 
	//t2を0～1にクランプしてmp2からs1.vに垂線を降ろしてみる
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	dist = CalcPointLineDist(*mp2, s1, e1, mp1, &t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1が線分内にあった
		return dist;
	}
	//mp1が線分内になかったので次へ

	//mp2,t2を求め直す ⇒ 
	//t1を0～1にクランプしてmp1からs2.vに垂線を降ろしてみる
	clamp0to1(t1);
	*mp1 = s1 + (e1 - s1) * t1;
	dist = CalcPointLineDist(*mp1, s2, e2, mp2, &t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2が線分内にあった
		return dist;
	}
	//mp2が線分内になかったので次へ

	//t2をクランプしてmp2を再計算すると、mp1からmp2までが最短
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	return (*mp2 - *mp1).Length();
}

bool CCollider::CollisionCapsuleCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	CVector mp1, mp2;
	float radius = m->mRadius + o->mRadius;

	*adjust = CVector();
	if (CalcSegmentSegmentDist(m->V(0), m->V(1), o->V(0), o->V(1), &mp1, &mp2) < radius)
	{
		*adjust = mp1 - mp2;
		float len = radius - adjust->Length();
		*adjust = adjust->Normalize() * len;
		return true;
	}
	return false;
}
