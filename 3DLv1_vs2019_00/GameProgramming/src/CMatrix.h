#pragma once

#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix {
public:
	void Point(); //4x4の行列を画面出力
	CMatrix(); //デフォルトコンストラクタ
	CMatrix Identity(); //単位行列の作成
private:
	float mM[4][4]; //4x4の行列データを設定
};

#endif