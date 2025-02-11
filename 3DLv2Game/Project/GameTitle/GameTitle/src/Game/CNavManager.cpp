#include "CNavManager.h"
#include "CNavNode.h"
#include "CInput.h"
#include <assert.h>
#include "CField.h"
#include "Primitive.h"

CNavManager* CNavManager::spInstance = nullptr;

CNavManager* CNavManager::Instance()
{
	return spInstance;
}

CNavManager::CNavManager()
	: CTask(ETaskPriority::eNavigation,0,ETaskPauseType::eGame)
	, mIsRender(false)
{
	assert(spInstance == nullptr);
	spInstance = this;
}

CNavManager::~CNavManager()
{
	spInstance = nullptr;

	// 探索ノードをすべて削除
	auto itr = mNodes.begin();
	auto end = mNodes.end();
	while (itr != end)
	{
		CNavNode* del = *itr;
		itr = mNodes.erase(itr);
		delete del;
	}
}

void CNavManager::AddNode(CNavNode* node)
{
	mNodes.push_back(node);
}

void CNavManager::RemoveNode(CNavNode* node)
{
	mNodes.remove(node);
}

int CNavManager::FindConnectNavNodes(CNavNode* node, float distance)
{
	// 現在の接続先の情報をすべてクリアしておく
	node->ClearConnects();
	for (CNavNode* findNode : mNodes)
	{
		if (findNode == node)continue;

		// 目的地専用ノードは距離を考慮しない
		if(!node->mIsDestNode)
		{ 
			// 指定された距離に限界値を超える場合スルー
			float dist = (findNode->GetPos() - node->GetPos()).Length();
			if (dist > distance)continue;
		}

		// フィールドとのレイ判定で遮蔽物チェックを行う
		CVector start = node->GetOffsetPos();
		CVector end = findNode->GetOffsetPos();
		CHitInfo hit;
		if (CField::Instanse()->CollisionRay(start, end, &hit))
		{
			// 何かにヒットした場合遮蔽物があるので接続できない
			continue;
		}

		node->AddConnect(findNode);
	}

	return node->mConnectData.size();
}

void CNavManager::ResetCalcData()
{
	for (CNavNode* node : mNodes)
	{
		node->ResetCalcData();
	}
}

void CNavManager::CalcNextMoveCost(CNavNode* node, CNavNode* goal)
{
	if (node == nullptr || goal == nullptr) return;

	// 接続しているノードへの移動コストを求める
	for (CNavConnectData& connect : node->mConnectData)
	{
		// 接続しているノードが目的地専用ノードの場合
		// 今回の経路探索の目的地ノード以外は経由しないためスルー
		if (connect.node->mIsDestNode && connect.node != goal) continue;

		float cost = node->mCalcMoveCost + connect.cost;
		if (connect.node->mCalcMoveCost < 0 || cost < connect.node->mCalcMoveCost)
		{
			// 接続先のノードの移動コストと１つ前のノードのポインタを更新
			connect.node->mCalcMoveCost = cost;
			connect.node->mpCalcFromNode = node;

			if (connect.node != goal)
			{
				CalcNextMoveCost(connect.node, goal);
			}
		}
	}
}

bool CNavManager::Navigate(CNavNode* start, CNavNode* goal, std::vector<CNavNode*>& route)
{
	if (start == nullptr && goal == nullptr)return false;

	// すべてのノードの最短経路計算用データをクリア
	ResetCalcData();

	// 開始ノードへの移動コストを０に設定
	start->mCalcMoveCost = 0.0f;
	// 開始ノードから順番に移動コスト計算
	CalcNextMoveCost(start, goal);

	// 最短経路のリストをクリアして最初に目的地ノードを登録
	route.clear();
	route.push_back(goal);

	// 目的地ノードから順に最短経路の1つ前のノードが存在する限りループし
	// 最短経路のリストに登録していく
	CNavNode* node = goal;
	while (node->mpCalcFromNode != nullptr)
	{
		route.insert(route.begin(), node->mpCalcFromNode);
		node = node->mpCalcFromNode;
	}

	// 求めた最短経路をデバッグ表示用の最短経路リストにコピー
	mLastCalcRoute = route;

	// 開始ノードから目的地ノードまで経路がつながっている
	return route[0] == start;
}

void CNavManager::Render()
{
	// スペースキーで経路探索ノードの描画モード切替
	if (CInput::PushKey('N'))
	{
		mIsRender = !mIsRender;
	}

	// 経路探索ノードを描画しないなら以降処理しない
	if (!mIsRender) return;

	// リスト内のノードをすべて描画
	for (CNavNode* node : mNodes)
	{
		node->Render();
	}

	// 最後に求めた最短経路のラインを引く
	glDisable(GL_DEPTH_TEST);
	int size = mLastCalcRoute.size();
	for (int i = 0; i < size - 1; i++)
	{
		CVector start = mLastCalcRoute[i]->GetOffsetPos();
		CVector end = mLastCalcRoute[i + 1]->GetOffsetPos();
		Primitive::DrawLine(start, end, CColor::cyan, 4.0f);
		
	}
	glEnable(GL_DEPTH_TEST);
}


