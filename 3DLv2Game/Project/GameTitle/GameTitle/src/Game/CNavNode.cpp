#include "CNavNode.h"
#include "CNavManager.h"
#include "Primitive.h"

#define NODE_OFFSET_Y 5.0f // �́[�ǂ�Y���W�̃I�t�Z�b�g�l
#define FIND_NODE_DISTANCE 70.0f // �T���m�[�h�̋����̌��E�l

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

	// ���W��ݒ�
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
	// �n�ʂƏd�Ȃ�Ȃ��悤�Ƀm�[�h�̈ʒu���班����ɂ������ʒu��Ԃ�
	return mPosition + CVector(0.0f, NODE_OFFSET_Y, 0.0f);
}

void CNavNode::SetPos(const CVector& pos)
{
	// �m�[�h�̍��W�X�V
	mPosition = pos;

	// �m�[�h�̍��W���ς�����̂Őڑ����Ă���m�[�h�𒲂�naosu
	CNavManager* navMgr = CNavManager::Instance();
	if (navMgr != nullptr)
	{
		navMgr->FindConnectNavNodes(this, FIND_NODE_DISTANCE);
	}
	
}

void CNavNode::AddConnect(CNavNode* node)
{
	// ���ɐڑ����X�g�ɓo�^���Ă���m�[�h�Ȃ炷��[
	for (CNavConnectData& connect : mConnectData)
	{
		if (connect.node == node)return;
	}

	float cost = (node->GetPos() - mPosition).Length();

	// ���g�Ƌ󂢂Ă��ꂼ��̐ڑ����Ă���m�[�h���X�g�ɂ��݂����w��
	mConnectData.push_back(CNavConnectData(node, cost));
	node->mConnectData.push_back(CNavConnectData(this, cost));
}

void CNavNode::RemoveConnect(CNavNode* node)
{
	auto itr = mConnectData.begin();
	auto end = mConnectData.end();
	while (itr != end)
	{
		// �m�[�h����v����΃��X�g�����菜��
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
	// �ڑ�����̐ڑ����X�g���玩�g����菜��
	for (CNavConnectData& connect : mConnectData)
	{
		connect.node->RemoveConnect(this);
	}
	// ���g�̐ڑ����X�g���N���A
	mConnectData.clear();
}

void CNavNode::SetColor(const CColor& color)
{
	mColor.Set(color.R(), color.G(), color.B());
}

void CNavNode::Render()
{
	// �ڑ���̃m�[�h�܂Ń��C����`��
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


