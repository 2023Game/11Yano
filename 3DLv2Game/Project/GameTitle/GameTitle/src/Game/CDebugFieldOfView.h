#pragma once
#include "CObjectBase.h"

//視野範囲を表示するデバッグ機能
class CDebugFieldOfView : public CObjectBase
{
public:
	enum class EType
	{
		eSector,
		eCone,
	};
	CDebugFieldOfView(CObjectBase* owner,
		float fovAngle, float fovLength, EType type);
	~CDebugFieldOfView();

	// 視野範囲を表示する対象を設定
	void SetOwner(CObjectBase* owner);
	// 視野範囲を設定
	void Set(float angle, float length, EType type);
	void Update() override;
	void Render() override;
private:
	
	CObjectBase* mpOwner; // 表示する対象のポインタ
	float mFovAngle; // 視野範囲の角度（ディグリー）
	float mFovLength; // 視野範囲の距離
	EType mType;
};