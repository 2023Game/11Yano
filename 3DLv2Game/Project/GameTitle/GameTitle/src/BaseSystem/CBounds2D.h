#pragma once

// バウンディングボックス情報
class CBounds2D
{
public:
	// コンストラクタ
	CBounds2D();
	// デストラクタ
	~CBounds2D();


	void SetRange(const CVector2& min, const CVector2& max);
	/// 中心位置とサイズで設定
	/// </summary>
	/// <param name="center">中心位置</param>
	/// <param name="size">サイズ</param>
	void SetPos(const CVector2& center, const CVector2& size);

	// 最小位置を設定
	void Min(const CVector2& min);
	// 最小位置を取得
	const CVector2& Min() const;
	// 最大位置を設定
	void Max(const CVector2& max);
	// 最大位置を取得
	const CVector2& Max() const;

	// 中心位置を設定
	void Center(const CVector2& center);
	// 中心位置を取得
	CVector2 Center() const;
	// サイズを設定
	void Size(const CVector2& size);
	// サイズを取得
	CVector2 Size() const;

	/// <summary>
	/// 2つのバウンディングボックスが交差するかどうか
	/// </summary>
	/// <param name="b0">1つ目のバウンディングボックス</param>
	/// <param name="b1">2つ目のバウンディングボックス</param>
	/// <returns>trueならば、交差している</returns>
	static bool Intersect(const CBounds2D& b0, const CBounds2D& b1);

	
	/// <summary>
	/// 円のバウンディングボックスを取得
	/// </summary>
	/// <param name="pos">円の座標</param>
	/// <param name="rad">円の半径</param>
	/// <returns>バウンディングボックス</returns>
	static CBounds2D GetCircleBounds(const CVector2& pos, float rad);
	
private:
	CVector2 mMin;	// 最小位置
	CVector2 mMax;	// 最大位置

};
