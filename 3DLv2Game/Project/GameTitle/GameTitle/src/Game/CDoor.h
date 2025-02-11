#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CIntercom;

class CDoor : public CObjectBase
{
public:
	CDoor(const CVector& pos, const CVector& angle, const CVector& size);
	~CDoor();
	
	void AddIntercom(CIntercom* intercom);
	void SetAnimPos(const CVector& openPos, const CVector& closePos);

	void Update() override;
	void Render() override;

private:
	bool IsOpen() const;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	std::list<CIntercom*> mpIntercoms;
	bool mIsOpened;

	CVector mClosePos;
	CVector mOpenPos;
	float mAnimTime;
	float mElapsedTime;
	bool mIsPlaying;
};