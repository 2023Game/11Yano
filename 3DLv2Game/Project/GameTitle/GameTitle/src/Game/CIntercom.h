#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CInteractObject.h"

class CHackGame;

class CIntercom : public CInteractObject
{
public:
	CIntercom(const CVector& pos, const CVector& angle, const CVector& size);
	~CIntercom();

	void Load();
	void Interact() override;
	void Update() override;
	void Render() override;
	bool IsClear() const;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	CModel* mpModel;
	CColliderLine* mpColliderLine;

	CHackGame* mpHackGame;
	bool mIsHack;
	bool mIsClear;
};