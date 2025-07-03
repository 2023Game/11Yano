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
	// 接続するインターフォンの設定
	void AddIntercom(CIntercom* intercom);
	// opemPos = 開きの位置, closePos = 閉めの位置
	void SetAnimPos(const CVector& openPos, const CVector& closePos);

	void Update() override;
	void Render() override;
	//カメラとの当たり判定取得
	CCollider* GetFieldCol() const;

	bool CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit);
private:
	bool IsOpen() const;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	CIntercom* mpIntercom;
	bool mIsOpened;

	CVector mClosePos;
	CVector mOpenPos;
	float mAnimTime;
	float mElapsedTime;
	bool mIsPlaying;
};