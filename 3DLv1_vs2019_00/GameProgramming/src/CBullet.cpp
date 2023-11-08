#include "CBullet.h"

void CBullet::Set(float w, float d) {
	mScale = CVector(1.0f, 1.0f, 1.0f);//�X�P�[���ݒ�
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));//�@���ݒ�
}

void CBullet::Update() {
	CTransform::Update();
	mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
}

void CBullet::Render() {
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	mT.Render(mMatrix);
}