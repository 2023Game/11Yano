#include "CColliderTriangle2D.h"
#include "glut.h"
#include "Maths.h"
#include "CColor.h"
#include "CMatrix2.h"

// �R���X�g���N�^
CColliderTriangle2D::CColliderTriangle2D(CObjectBase* owner, ELayer layer,
	const CVector2& v0, const CVector2& v1, const CVector2& v2,
	bool isKinematic, float weight)
	: CCollider(owner, layer, EColliderType::eTriangle, isKinematic, weight)
{
	// �O�p�`�̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// �O�p�`�R���C�_�[�̐ݒ�
void CColliderTriangle2D::Set(CObjectBase* owner, ELayer layer,
	const CVector2& v0, const CVector2& v1, const CVector2& v2)
{
	CCollider::Set(owner, layer);

	// �O�p�`�̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// �O�p�`�̒��_���擾
void CColliderTriangle2D::Get(CVector2* v0, CVector2* v1, CVector2* v2) const
{
	*v0 = mWV[0];
	*v1 = mWV[1];
	*v2 = mWV[2];
}

// �R���C�_�[�`��
void CColliderTriangle2D::Render()
{
	glPushMatrix();

	// 2D�ϊ��s���K�p�i���� Matrix2().M() �� float[16] ��Ԃ��ꍇ�j
	glMultMatrixf(Matrix2().M());

	// �A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

	CColor col = CColor::red;
	if (!IsEnable()) col = CColor::gray;
	col.A(0.2f);
	float* c = (float*)&col;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glBegin(GL_TRIANGLES);
	glVertex2f(mV[0].X(), mV[0].Y());
	glVertex2f(mV[1].X(), mV[1].Y());
	glVertex2f(mV[2].X(), mV[2].Y());
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPopMatrix();
}

// �R���C�_�[�̏����X�V
void CColliderTriangle2D::UpdateCol()
{
	// �s��𔽉f�����e���_�̍��W���v�Z
	CMatrix2 m = Matrix2();
	mWV[0] = mV[0] * m;
	mWV[1] = mV[1] * m;
	mWV[2] = mV[2] * m;

	// �o�E���f�B���O�{�b�N�X���X�V
	mBounds2D = CBounds2D::GetTriangleBounds(mWV[0], mWV[1], mWV[2]);
}