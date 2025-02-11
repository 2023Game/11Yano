#pragma once
#include <list>

class CNavManager;
class CNavNode;

// 経路探索ノードの接続情報
class CNavConnectData
{
public:
	CNavNode* node; //つながっているノード
	float cost; // つながっているノードまでの移動コスト
	CNavConnectData(CNavNode* n, float c)
		: node(n), cost(c) {}
};

class CNavNode
{
	friend CNavManager;
public:
	CNavNode(const CVector& pos, bool isDestNode = false);
	~CNavNode();

	// ノードの座標取得
	const CVector& GetPos() const;
	// 遮蔽物チェックや表示用に少し上にあげたノード座標を返す
	CVector GetOffsetPos() const;
	// ノードの座標設定
	void SetPos(const CVector& pos);

	// 接続するノードを追加
	void AddConnect(CNavNode* node);
	// 接続しているノードを取り除く
	void RemoveConnect(CNavNode* node);
	// 接続しているすべてのノードを解除
	void ClearConnects();

	// ノードの色設定デバッグ用
	void SetColor(const CColor& color);
	// ノード描画デバッグ用
	void Render();

private:
	// 最短経路計算用のデータリセット
	void ResetCalcData();
	// 経路探索時に経由できない目的地専用のノードか
	bool mIsDestNode;
	CVector mPosition; // ノードの座標
	// 接続しているノードの情報リスト
	std::list<CNavConnectData> mConnectData;

	// 最短経路計算時に記憶しておく情報
	float mCalcMoveCost; // 開始ノードからこのノードまでかかった移動コスト
	CNavNode* mpCalcFromNode; // サン短距離での前のノードのポインタ

	// デバッグ関連
	CColor mColor; // ノードの色
};