#pragma once
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CIntercom;

class CDoor : public CObjectBase
{
public:
	CDoor(const CVector& pos, const CVector& angle, const CVector& size);
	~CDoor();
	// �ڑ�����C���^�[�t�H���̐ݒ�
	void AddIntercom(CIntercom* intercom);
	// opemPos = �J���̈ʒu, closePos = �߂̈ʒu
	void SetAnimPos(const CVector& openPos, const CVector& closePos);

	void Update() override;
	void Render() override;
	//�J�����Ƃ̓����蔻��擾
	CCollider* GetFieldCol() const;

	bool CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit);
private:
	bool IsOpen() const;

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	CIntercom* mpIntercom;
	bool mIsOpened;

	CVector mClosePos;
	CVector mOpenPos;
	float mAnimTime;
	float mElapsedTime;
	bool mIsPlaying;
};