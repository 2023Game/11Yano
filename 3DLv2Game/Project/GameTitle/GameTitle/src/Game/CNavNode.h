#pragma once
#include <list>

class CNavManager;
class CNavNode;

// �o�H�T���m�[�h�̐ڑ����
class CNavConnectData
{
public:
	CNavNode* node; //�Ȃ����Ă���m�[�h
	float cost; // �Ȃ����Ă���m�[�h�܂ł̈ړ��R�X�g
	CNavConnectData(CNavNode* n, float c)
		: node(n), cost(c) {}
};

class CNavNode
{
	friend CNavManager;
public:
	CNavNode(const CVector& pos, bool isDestNode = false);
	~CNavNode();

	// �m�[�h�̍��W�擾
	const CVector& GetPos() const;
	// �Օ����`�F�b�N��\���p�ɏ�����ɂ������m�[�h���W��Ԃ�
	CVector GetOffsetPos() const;
	// �m�[�h�̍��W�ݒ�
	void SetPos(const CVector& pos);

	// �ڑ�����m�[�h��ǉ�
	void AddConnect(CNavNode* node);
	// �ڑ����Ă���m�[�h����菜��
	void RemoveConnect(CNavNode* node);
	// �ڑ����Ă��邷�ׂẴm�[�h������
	void ClearConnects();

	// �m�[�h�̐F�ݒ�f�o�b�O�p
	void SetColor(const CColor& color);
	// �m�[�h�`��f�o�b�O�p
	void Render();

private:
	// �ŒZ�o�H�v�Z�p�̃f�[�^���Z�b�g
	void ResetCalcData();
	// �o�H�T�����Ɍo�R�ł��Ȃ��ړI�n��p�̃m�[�h��
	bool mIsDestNode;
	CVector mPosition; // �m�[�h�̍��W
	// �ڑ����Ă���m�[�h�̏�񃊃X�g
	std::list<CNavConnectData> mConnectData;

	// �ŒZ�o�H�v�Z���ɋL�����Ă������
	float mCalcMoveCost; // �J�n�m�[�h���炱�̃m�[�h�܂ł��������ړ��R�X�g
	CNavNode* mpCalcFromNode; // �T���Z�����ł̑O�̃m�[�h�̃|�C���^

	// �f�o�b�O�֘A
	CColor mColor; // �m�[�h�̐F
};