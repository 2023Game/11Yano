#pragma once
#include "CMatrix.h"

#ifndef CVECTOR_H
#define CVECTIR_H

class CVector {
public:
	CVector Nomalize() const;//正規化（大きさ1のベクトル）
	CVector Cross(const CVector& v) const;//外積
	CVector operator*(const float& f) const;//*演算子のオーバーロード
	float Dot(const CVector& v) const;//内積
	float Length() const;
	CVector operator*(const CMatrix &m);
	CVector operator+(const CVector &v) const; //+演算子のオーバーロード
	CVector operator-(const CVector &v) const; //-演算子のオーバーロード
	CVector(); //デフォルトコンストラクタ
	CVector(float x, float y, float z); //コンストラクタ
	void Set(float x, float y, float z); //各軸での値の設定
	float X()const; //Xの値を得る
	float Y()const; //Yの値を得る
	float Z()const; //Zの値を得る
private:
	float mX, mY, mZ; //3D各軸での値を設定
};
#endif