#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderLine.h"
#include "CSound.h"

class CTrailEffect;

// eÛNX
class CBullet : public CObjectBase
{
public:
	/// <summary>
	/// RXgN^
	/// </summary>
	/// <param name="pos">eÛÌÊu</param>
	/// <param name="dir">eÛÌü«</param>
	/// <param name="speed">Ú®¬x</param>
	/// <param name="distance">ò£</param>
	CBullet(const CVector& pos, const CVector& dir,
		float speed, float distance, ELayer layer);

	// fXgN^
	~CBullet();


	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	// XV
	void Update() override;
	// `æ
	void Render() override;

private:
	CSound* mpSE; // SEf[^
	CColliderLine* mpColliderLine;
	CTrailEffect* mpTrailEffect;	// eÛÌOÕÌGtFNg
	float mMoveSpeed;				// Ú®¬x
	float mFlyingDistance;			// ò£
	float mCurrentFlyingDistance;	// »ÝÌò£
	CVector mMoveDir; // ­Ëûü
};