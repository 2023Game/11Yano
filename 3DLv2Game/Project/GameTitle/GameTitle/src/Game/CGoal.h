#pragma once
#include "CInteractObject.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CImage.h"

class CHackGame;

class CGoal : public CInteractObject
{
public:
	CGoal(const CVector& pos, const CVector& angle, const CVector& size, ELayer layer);
	~CGoal();

	void Interact() override;

	void Update() override;
	void Render() override;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	CModel* mpModel;
	CColliderLine* mpColliderLine;
	ELayer mpLayer;

	CImage* mpImage;
	bool mIsAction;

};