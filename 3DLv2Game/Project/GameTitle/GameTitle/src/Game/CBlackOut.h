#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CSound.h"
#include "CInteractObject.h"

class CHackGame2;

class CBlackOut : public CInteractObject
{
public:
	static CBlackOut* Instance();
	CBlackOut(const CVector& pos, const CVector& angle, const CVector& size);
	~CBlackOut();

	void Interact() override;
	void Update() override;
	void Render() override;
	bool IsClear() const;

	bool IsBlack() const;

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
private:
	static CBlackOut* spInstance;
	CModel* mpModel;
	CColliderLine* mpColliderLine;

	CSound* mpSE;

	CHackGame2* mpHackGame;
	bool mIsHack;
	bool mIsClear;
	bool mIsBlack; // ’â“d‚³‚¹‚é‚©‚Ç‚¤‚©
	bool mIsBlacked; // ’â“d‚µ‚½‚±‚Æ‚ª‚ ‚ê‚Îtrue, ‚Ü‚¾‚µ‚Ä‚È‚¢‚È‚çfalse
	float mTime;
};