#include "CXCharacter.h"

void CXCharacter::Init(CModelX* model) {
	mpModel = model;
	mAnimationIndex = 0;//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationLoopFlg = true;//�J��Ԃ��Đ�����
	//�P�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFrameSize =
		model->AnimationSet()[0]->MaxTime();
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(1.0f);
}

/*
index:�A�j���[�V�����̔ԍ�
looop:true �J��Ԃ�
Framesize:�Ō�܂ōĐ�����̂Ɏg�p�����t���[����*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�͐ؑւȂ�
	if (mAnimationIndex == index) return;
	//���̃A�j���[�V�����̏d�݂�0.0(0%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(0.0f);
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->AnimationSet().size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(1.0f);
}

void CXCharacter::Update(CMatrix& matrix) {
	//�Ō�܂ōĐ�����
	if (mAnimationFrame <= mAnimationFrameSize) {
		//�A�j���[�V�������Ԃ��v�Z
		mpModel->AnimationSet()[mAnimationIndex]->Time(
			mpModel->AnimationSet()[mAnimationIndex]->MaxTime() *
			mAnimationFrame / mAnimationFrameSize);
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�̓t���[����0�ɖ߂�
		if (mAnimationLoopFlg) {
			mAnimationFrame = 0.0f;
			mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
		}
		else {
			mpModel->AnimationSet()[mAnimationIndex]->
				Time(mpModel->AnimationSet()[mAnimationIndex]->MaxTime());
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->Frames()[0]->AnimateCombined(&matrix);
	//���_�ɃA�j���[�V������K�p����
	mpModel->AnimateVertex();
}

void CXCharacter::Render() {
	mpModel->Render();
}

bool CXCharacter::IsAnimationFinished() {
	return mAnimationFrame >= mAnimationFrameSize;
}

int CXCharacter::AnimationIndex() {
	return mAnimationIndex;
}