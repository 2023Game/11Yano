#pragma once
#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
#include "CInput.h"

class CActionCamera : public CTransform {
public:
	//カメラのX軸取得
	CVector VectorX();
	//カメラのZ軸取得
	CVector VectorZ();
	CActionCamera();
	static CActionCamera* Instance();//インスタンスの取得
	void Set(float distance, float xaxis, float yaxis);//設定メソッド(距離, X回転,Y回転)
	void Update();//カメラ更新
	void Render();//カメラ適用
private:
	static CActionCamera* spInstance;//インスタンス
	CVector mEye;//視点
	CVector mCenter;//注視点
	CVector mUp;//上方向
	CMatrix mModelView;//モデルビュー行列
	CInput mInput;//入力クラス
};
#endif