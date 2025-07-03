#pragma once
#include "CRect.h"
#include "CTexture.h"

#define VELOCITY 2.0f

class CCharacter2D : public CRect
{
public:
	bool Enabled();
	enum class ETag
	{
		eZero,
		eBullet,
		eEnemy,
		ePlayer,
		eBlock,
	};
	ETag Tag();
	virtual void Collision() {};
	virtual void Collision(CCharacter2D* m, CCharacter2D* o) {};
	virtual void Update() = 0;
	void Texture(CTexture* texture,
		int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
	enum class EState
	{
		eMove,
		eStop,
		eJump,
		eDamage,
	};
	EState State();
	CCharacter2D();
	CTexture* Texture();
protected:
	float mVx;
	float mVy;
	bool mEnabled; //—LŒøƒtƒ‰ƒO
	ETag mTag;
	EState mState;
private:

	CTexture* mpTexture;
	int mLeft, mRight, mBottom, mTop;
};
