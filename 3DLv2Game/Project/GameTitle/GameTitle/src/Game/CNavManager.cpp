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

	// �T���m�[�h�����ׂč폜
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
	// ���݂̐ڑ���̏������ׂăN���A���Ă���
	node->ClearConnects();
	for (CNavNode* findNode : mNodes)
	{
		if (findNode == node)continue;

		// �ړI�n��p�m�[�h�͋������l�����Ȃ�
		if(!node->mIsDestNode)
		{ 
			// �w�肳�ꂽ�����Ɍ��E�l�𒴂���ꍇ�X���[
			float dist = (findNode->GetPos() - node->GetPos()).Length();
			if (dist > distance)continue;
		}

		// �t�B�[���h�Ƃ̃��C����ŎՕ����`�F�b�N���s��
		CVector start = node->GetOffsetPos();
		CVector end = findNode->GetOffsetPos();
		CHitInfo hit;
		if (CField::Instanse()->CollisionRay(start, end, &hit))
		{
			// �����Ƀq�b�g�����ꍇ�Օ���������̂Őڑ��ł��Ȃ�
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

	// �ڑ����Ă���m�[�h�ւ̈ړ��R�X�g�����߂�
	for (CNavConnectData& connect : node->mConnectData)
	{
		// �ڑ����Ă���m�[�h���ړI�n��p�m�[�h�̏ꍇ
		// ����̌o�H�T���̖ړI�n�m�[�h�ȊO�͌o�R���Ȃ����߃X���[
		if (connect.node->mIsDestNode && connect.node != goal) continue;

		float cost = node->mCalcMoveCost + connect.cost;
		if (connect.node->mCalcMoveCost < 0 || cost < connect.node->mCalcMoveCost)
		{
			// �ڑ���̃m�[�h�̈ړ��R�X�g�ƂP�O�̃m�[�h�̃|�C���^���X�V
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

	// ���ׂẴm�[�h�̍ŒZ�o�H�v�Z�p�f�[�^���N���A
	ResetCalcData();

	// �J�n�m�[�h�ւ̈ړ��R�X�g���O�ɐݒ�
	start->mCalcMoveCost = 0.0f;
	// �J�n�m�[�h���珇�ԂɈړ��R�X�g�v�Z
	CalcNextMoveCost(start, goal);

	// �ŒZ�o�H�̃��X�g���N���A���čŏ��ɖړI�n�m�[�h��o�^
	route.clear();
	route.push_back(goal);

	// �ړI�n�m�[�h���珇�ɍŒZ�o�H��1�O�̃m�[�h�����݂�����胋�[�v��
	// �ŒZ�o�H�̃��X�g�ɓo�^���Ă���
	CNavNode* node = goal;
	while (node->mpCalcFromNode != nullptr)
	{
		route.insert(route.begin(), node->mpCalcFromNode);
		node = node->mpCalcFromNode;
	}

	// ���߂��ŒZ�o�H���f�o�b�O�\���p�̍ŒZ�o�H���X�g�ɃR�s�[
	mLastCalcRoute = route;

	// �J�n�m�[�h����ړI�n�m�[�h�܂Ōo�H���Ȃ����Ă���
	return route[0] == start;
}

void CNavManager::Render()
{
	// �X�y�[�X�L�[�Ōo�H�T���m�[�h�̕`�惂�[�h�ؑ�
	if (CInput::PushKey('N'))
	{
		mIsRender = !mIsRender;
	}

	// �o�H�T���m�[�h��`�悵�Ȃ��Ȃ�ȍ~�������Ȃ�
	if (!mIsRender) return;

	// ���X�g���̃m�[�h�����ׂĕ`��
	for (CNavNode* node : mNodes)
	{
		node->Render();
	}

	// �Ō�ɋ��߂��ŒZ�o�H�̃��C��������
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


