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
	mpParent = parent;//�e�ݒ�
	mpMatrix = matrix;//�e�s��ݒ�
	mPosition = position;//�ʒu
	mRadius = radius;//���a�ݒ�
}

CCharacter3* CCollider::Parent() {
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	CVector pos = mPosition * *mpMatrix;//�R���C�_�̒��S���W�v�Z
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());//���S���W�ֈړ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };//DIFFUSE�ԐF�ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glutWireSphere(mRadius, 16, 16);//���`��
	glPopMatrix();
}

CCollider::~CCollider() {
	CCollisionManager::Instance()->Remove(this);
}

bool CCollider::Collision(CCollider* m, CCollider* o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	mpos = mpos - opos;//���S���璆�S�̃x�N�g�������߂�
	if (m->mRadius + o->mRadius > mpos.Length()) {
		return true;//�Փ˂��Ă���
	}
	return false;//�Փ˂��Ă��Ȃ�
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//�ʂ̖@�����O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//�O�p�̒��_��������x�X�ւ̃x�N�g�������߂�
	CVector v0sv = sv - v[0];
	//�O�p�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = ev - v[0];
	//������ʂƌ������Ă��邩���ςŊm�F
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������Ă��Ȃ�
	if (dots * dote >= 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�D�]�̌v�Z
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));
	//�D�]���O�p�`�Ȃ�Փ˂��Ă���
	// ���_�P���_�Q�x�N�g���ƒ��_�P��_�x�N�g���Ƃ̊O�ς�����
	// �@���Ƃ̓��ς��}�C�i�X�Ȃ�O�p�`�̊O
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_�Q���_3�x�N�g���ƒ��_�Q��_�x�N�g���̊O�ς�����
	// �@���Ƃ̓��ς��}�C�i�X�Ȃ�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_�R���_�P�x�N�g���ƒ��_�R��_�x�N�g���Ƃ̊O�ς�����
	// �@���Ƃ̓��ς��}�C�i�X�Ȃ�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�������Ă���̂Œ����r�v�Z
	if (dots < 0.0f) {
		//���_������
		*a = normal * -dots;
	}
	else {
		//�I�_������
		*a = normal * -dote;
	}
	return true;
}

CCollider::EType CCollider::Type() {
	return mType;
}

bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//�ʂ̖@�����O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//���R���C�_�����[���h���W�ō쐬
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &line, a);
}

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this);//��������폜
	CCollisionManager::Instance()->Add(this);//�ǉ�
}

void CCollider::ChangePriority()
{
	//�����̍��W���e�̕ύX�s����|���ă��[���h���W�����߂�
	CVector pos = mPosition * *mpMatrix;
	//�x�N�g���̒������D��x
	CCollider::ChangePriority(pos.Length());
}

void CCollider::Matrix(CMatrix* m) {
	mpMatrix = m;
}