#pragma once
#include <list>
#include <vector>
#include "CTask.h"

class CNavNode;

class CNavManager : public CTask
{
public:
	// �o�H�Ǘ��N���X�̃C���X�^���X���擾
	static CNavManager* Instance();

	CNavManager();
	~CNavManager();

	// �o�H�T���p�̃m�[�h��ǉ�
	void AddNode(CNavNode* node);
	// �o�H�T���p�̃m�[�h����菜��
	void RemoveNode(CNavNode* node);

	// �w�肵���m�[�h�ɐڑ��ł���m�[�h���������Đݒ�
	int FindConnectNavNodes(CNavNode* node, float distance);

	// �w�肵���J�n�m�[�h����ړI�n�m�[�h�܂ł̍ŒZ���������߂�
	bool Navigate(CNavNode* start, CNavNode* goal, std::vector<CNavNode*>& route);

	// ���ׂẴm�[�h�ƌo�H��`��
	void Render() override;
private:
	// �ŒZ�o�H�v�Z�p�̃f�[�^���Z����
	void ResetCalcData();
	void CalcNextMoveCost(CNavNode* node, CNavNode* goal);
	// �o�H�Ǘ��N���X�̃C���X�^���X�ւ̃|�C���^
	static CNavManager* spInstance;

	// �o�H�T���p�m�[�h�̃��X�g
	std::list<CNavNode*> mNodes;

	// �o�H�T���̃f�o�b�O�\�����s����
	bool mIsRender;

	// �Ō�Ɍv�Z�����ŒZ�o�H�̃f�o�b�O�\���p
	std::vector<CNavNode*> mLastCalcRoute;
};