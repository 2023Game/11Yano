#pragma once
#include "CObjectBase.h"
#include "CImage.h"
#include "CColliderCircle2D.h"
#include "CSound.h"

class CMryotaisu : public CObjectBase
{
public:
	CMryotaisu(const CVector2& pos);
	~CMryotaisu();
	void Update();
	void Render();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	CSound* mpSE;
	CImage* mpImage;
	CVector2 mPosition;
	CColliderCircle2D* mpCollider;

};