#pragma once
#include <list>
#include <vector>
#include "CTask.h"

class CNavNode;

class CNavManager : public CTask
{
public:
	// 経路管理クラスのインスタンスを取得
	static CNavManager* Instance();

	CNavManager();
	~CNavManager();

	// 経路探索用のノードを追加
	void AddNode(CNavNode* node);
	// 経路探索用のノードを取り除く
	void RemoveNode(CNavNode* node);

	// 指定したノードに接続できるノードを検索して設定
	int FindConnectNavNodes(CNavNode* node, float distance);

	// 指定した開始ノードから目的地ノードまでの最短距離を求める
	bool Navigate(CNavNode* start, CNavNode* goal, std::vector<CNavNode*>& route);

	// すべてのノードと経路を描画
	void Render() override;
private:
	// 最短経路計算用のデータリセっと
	void ResetCalcData();
	void CalcNextMoveCost(CNavNode* node, CNavNode* goal);
	// 経路管理クラスのインスタンスへのポインタ
	static CNavManager* spInstance;

	// 経路探索用ノードのリスト
	std::list<CNavNode*> mNodes;

	// 経路探索のデバッグ表示を行うか
	bool mIsRender;

	// 最後に計算した最短経路のデバッグ表示用
	std::vector<CNavNode*> mLastCalcRoute;
};