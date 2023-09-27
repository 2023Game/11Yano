#pragma once
#ifndef CVECTOR_H
#define CVECTIR_H

class CVector {
public:
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