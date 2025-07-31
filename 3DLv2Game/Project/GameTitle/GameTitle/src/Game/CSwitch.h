#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CSound.h"
#include "CInteractObject.h"

class CHackGame2;

class CSwitch : public CInteractObject
{
public:
	CSwitch(const CVector& pos, const CVector& angle, const CVector& size);
	~CSwitch();

	void Interact() override;
	void Update() override;
	void Render() override;
	bool IsClear() const;

	void KillObj();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	CModel* mpModel;
	CColliderLine* mpColliderLine;

	CSound* mpSE;

	CHackGame2* mpHackGame;
	bool mIsHack;
	bool mIsClear;
	bool mIsPlayed;
};