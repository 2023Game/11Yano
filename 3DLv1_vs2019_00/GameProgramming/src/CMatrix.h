#pragma once
#ifndef CMATRIX_H
#define CMATRIX_H

class CVector;

class CMatrix {
public:
	//クォータニオンで回転行列を設定する
	CMatrix Quaternion(float x, float y, float z, float w);
	//要素数の取得
	int Size();
	CVector VectorZ() const; //Z軸ベクトルの取得
	CVector VectorX() const; //X軸ベクトルの取得
	CVector VectorY() const; //Y軸ベクトルの取得
	CMatrix Transpose() const;
	float* M() const;
	const CMatrix operator*(const CMatrix& m) const;
	void M(int row, int col, float value); //行列値の代入
	CMatrix Translate(float mx, float my, float mz); //移動行列の作成
	CMatrix RotateX(float degree);
	CMatrix RotateZ(float degree);
	CMatrix RotateY(float degree); //回転行列(Y軸)の作成
	float M(int r, int c) const; //行列地の取得
	CMatrix Scale(float sx, float sy, float sz); //拡大縮小行列の作成
	void Print(); //4x4の行列を画面出力
	CMatrix(); //デフォルトコンストラクタ
	CMatrix Identity(); //単位行列の作成
private:
	float mM[4][4]; //4x4の行列データを設定
};

#endif