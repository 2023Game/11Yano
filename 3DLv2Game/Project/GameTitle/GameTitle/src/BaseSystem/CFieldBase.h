#pragma once

class CFieldBase
{
public:
	CFieldBase();
	~CFieldBase();
	//インスタンスのポインタの取得
	static CFieldBase* Instance();

	// レイとフィールドオブジェクトとの衝突判定
	virtual bool CollisionRay(const CVector& start, const CVector& end,
		CHitInfo* hit);
private:
	static CFieldBase* spInstance;
};