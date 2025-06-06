#include "CBillBoard.h"
#include "CApplication.h"

CBillBoard::CBillBoard() {

}

CBillBoard::CBillBoard(CVector pos, float w, float h) {
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h) {
	mPosition = pos;//位置
	mScale = CVector(1.0f, 1.0f, 1.0f);//大きさ
	//三角形の頂点座標設定
	mT[0].Vertex(CVector(w, h, 0.0f), CVector(-w, -h, 0.0f), CVector(w, -h, 0.0f));
	mT[1].Vertex(CVector(-w, h, 0.0f), CVector(-w, -h, 0.0f), CVector(w, h, 0.0f));
	//法線をZ軸方向
	mT[0].Normal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].Normal(CVector(0.0f, 0.0f, 1.0f));
	//白色を設定
	mMaterial.Diffuse()[0] = 1.0f;
	mMaterial.Diffuse()[1] = 1.0f;
	mMaterial.Diffuse()[2] = 1.0f;
	mMaterial.Diffuse()[3] = 1.0f;
}

void CBillBoard::Update() {
	CTransform::Update();//行列の更新
}

void CBillBoard::Render() {
	Render(&mMaterial);
}

void CBillBoard::Render(CMaterial* mpMaterial) {
	//行列の保存
	glPushMatrix();
	//拡縮、回転、移動
	glMultMatrixf((CApplication::ModelViewInverse() * mMatrix).M());
	//ライトオフ
	glDisable(GL_LIGHTING);
	//描画色の設定
	glColor4fv(mpMaterial->Diffuse());
	//マテリアル適用
	mpMaterial->Enabled();
	//三角形描画
	mT[0].Render();
	mT[1].Render();
	//マテリアル解除
	mpMaterial->Disabled();
	//ライトオン
	glEnable(GL_LIGHTING);
	//行列を戻す
	glPopMatrix();
}

CBillBoard::CBillBoard(CVector pos, float w, float h, int priority)
	:CCharacter3(priority)
{
	Set(pos, w, h);
}