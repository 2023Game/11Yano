#include "CEnemy3.h"
#include "CEffect.h"
#include "CCollisionManager.h"

#define OBJ "res\\f16.obj" //���f���̃t�@�C��
#define MTL "res\\f16.mtl" //���f���̃}�e���A���t�@�C��

CModel CEnemy3::sModel;

CEnemy3::CEnemy3()
	:CCharacter3(1)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
{
	//���f�����Ȃ��Ƃ��ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
}

CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3()
{
	//�ʒu�A��]�A�g�k�̐ݒ�
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	CTransform::Update();//�s��̍X�V
}

void CEnemy3::Update()
{

}

void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (CCollider::Collision(m, o)) {
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă���Ɩ���
			//mEnabled=false;
		}
		break;
	case CCollider::EType::ETRIANGLE:
		CVector adjust;//�����r
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փˎs����܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}