#pragma once
#include "CXCharacter.h"

class CInteractObject : public CXCharacter
{
public: 
	CInteractObject(
		ETaskPriority prio = ETaskPriority::eDefault,
		int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eDefault);
	virtual ~CInteractObject();

	// 調べれる状態か
	virtual bool CanInteract() const;
	virtual void Interact() = 0;

	// 調べる内容のテキストを返す
	std::string GetInteractStr() const;

	// デバッグ表示用の名前を取得
	std::string GetDebugName() const;
	// デバッグ表示用の名前を設定
	void SetDebugName(std::string name);
protected:
	std::string mInteractStr; // 調べる内容のテキスト

#if _DEBUG
	std::string mDebugName;
#endif
};