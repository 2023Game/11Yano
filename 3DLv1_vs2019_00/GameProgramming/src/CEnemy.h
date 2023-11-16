#pragma once
#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter3.h"
#include "CCollider.h"

class CEnemy : public CCharacter3
{
public:
	void CEnemy::Render() {//�m�F�p�A�폜�\��
		CCharacter3::Render();
		mCollider1.Render();
		mCollider2.Render();
		mCollider3.Render();
	}
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	void Update();
private:
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};

#endif