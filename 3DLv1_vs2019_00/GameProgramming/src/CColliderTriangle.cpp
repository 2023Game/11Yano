#include "CColliderTriangle.h"
#include "CCollisionManager.h"

CColliderTriangle::CColliderTriangle(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2) {
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2) {
	mType = EType::ETRIANGLE;//�O�p�R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

void CColliderTriangle::Render() {
	glPushMatrix();//�s��ޔ�
	glMultMatrixf(mpMatrix->M());//�s��K�p
	glEnable(GL_BLEND);//�A���t�@�u�����h��L��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//�u�����h���@�w��
	glDisable(GL_LIGHTING);//���C�g�I�t
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);
	//�O�p�`�`��
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();
	
	glEnable(GL_LIGHTING);//���C�g�I��
	glDisable(GL_ALPHA);//�A���t�@�u�����h����
	glPopMatrix();//�s�񕜋A
}