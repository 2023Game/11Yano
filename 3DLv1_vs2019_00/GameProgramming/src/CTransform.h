#pragma once
#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"

class CTransform {
public:
	const CVector& Position() const;//位置の取得
	void Position(const CVector& v);//位置の設定
	void Rotation(const CVector& v);//回転地の設定
	void Scale(const CVector& v);//拡大縮小の設定
	const CMatrix& Matrix() const;//合成行列の取得
	const CMatrix& MatrixRotate() const;//回転行列の取得
	void Update();//行列更新処理
	//Update(位置、回転、スケール)
	void Update(const CVector& pos, const CVector& rot, const CVector& scale);
protected:
	CVector mPosition;//位置
	CVector mRotation;//回転
	CVector mScale;//拡大縮小
	CMatrix mMatrixTranslate;//平行移動行列
	CMatrix mMatrixRotate;//回転行列
	CMatrix mMatrixScale;//拡大縮小行列
	CMatrix mMatrix;//合成行列
};

#endif