#include "CNavNode.h"
#include "CNavManager.h"
#include "Primitive.h"

#define NODE_OFFSET_Y 5.0f // のーどのY座標のオフセット値
#define FIND_NODE_DISTANCE 70.0f // 探すノードの距離の限界値

CNavNode::CNavNode(const CVector& pos, bool isDestNode)
	: mIsDestNode(isDestNode)
	, mPosition(pos)
	, mColor(0.0f, 1.0f, 0.0f, 1.0f)
	, mCalcMoveCost(-1.0f)
	, mpCalcFromNode(nullptr)
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		navMgr->AddNode(this);
	}

	// 座標を設定
	SetPos(mPosition);

}

CNavNode::~CNavNode()
{
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		navMgr->RemoveNode(this);
	}
}

void CNavNode::ResetCalcData()
{
	mCalcMoveCost = -1.0f;
	mpCalcFromNode = nullptr;
}

const CVector& CNavNode::GetPos() const
{
	return mPosition;
}

CVector CNavNode::GetOffsetPos() const
{
	// 地面と重ならないようにノードの位置から少し上にあげた位置を返す
	return mPosition + CVector(0.0f, NODE_OFFSET_Y, 0.0f);
}

void CNavNode::SetPos(const CVector& pos)
{
	// ノードの座標更新
	mPosition = pos;

	// ノードの座標が変わったので接続しているノードを調べnaosu
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		navMgr->FindConnectNavNodes(this, FIND_NODE_DISTANCE);
	}
	
}

void CNavNode::AddConnect(CNavNode* node)
{
	// 既に接続リストに登録してあるノードならするー
	for (CNavConnectData& connect : mConnectData)
	{
		if (connect.node == node)return;
	}

	float cost = (node->GetPos() - mPosition).Length();

	// 自身と空いてそれぞれの接続しているノードリストにお互いを指定
	mConnectData.push_back(CNavConnectData(node, cost));
	node->mConnectData.push_back(CNavConnectData(this, cost));
}

void CNavNode::RemoveConnect(CNavNode* node)
{
	auto itr = mConnectData.begin();
	auto end = mConnectData.end();
	while (itr != end)
	{
		// ノードが一致すればリストから取り除く
		if (itr->node == node)
		{
			itr = mConnectData.erase(itr);
			continue;
		}
		itr++;
	}
}

void CNavNode::ClearConnects()
{
	// 接続相手の接続リストから自身を取り除く
	for (CNavConnectData& connect : mConnectData)
	{
		connect.node->RemoveConnect(this);
	}
	// 自身の接続リストをクリア
	mConnectData.clear();
}

void CNavNode::SetColor(const CColor& color)
{
	mColor.Set(color.R(), color.G(), color.B());
}

void CNavNode::Render()
{
	// 接続先のノードまでラインを描画
	for (CNavConnectData& connect : mConnectData)
	{
		Primitive::DrawLine
		(
			GetOffsetPos(),
			connect.node->GetOffsetPos(),
			CColor(0.11f, 0.1f, 0.1f, 1.0f),
			2.0f
		);
	}
	//CMatrix m;
	//m.Translate(GetOffsetPos());
	//Primitive::DrawWireSphere(m, 1.0f, mColor);
	Primitive::DrawWireBox(GetOffsetPos(), CVector::one,
		mColor);
}


