#include "CColliderLine.h"
#include "CCollisionManager.h"

CColliderLine::CColliderLine(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1) {
	Set(parent, matrix, v0, v1);
}

void CColliderLine::Set(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1) {
	mType = EType::ELINE;//�����R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�������_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
}

void CColliderLine::Render() {
	glPushMatrix();//�s��ޔ�
	glMultMatrixf(mpMatrix->M());//�s��K�p
	glEnable(GL_BLEND);//�A���t�@�u�����h�L��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//�u�����h���@�w��
	glDisable(GL_LIGHTING);//���C�g�I�t
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);
	//�����`��
	glBegin(GL_LINES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glEnd();
	glEnable(GL_LIGHTING);//���C�g�I��
	glDisable(GL_ALPHA);//�A���t�@�u�����h����
	glPopMatrix();//�s�񕜋A
}

void CColliderLine::ChangePriority()
{
	//mV[0}��mV[1]�̒��S�����߂�
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//�x�N�g���̒������D��x
	CCollider::ChangePriority(pos.Length());
}