#ifndef CMATRIX2_H
#define CMATRIX2_H

class CVector2;


class CMatrix2
{
public:
    CMatrix2();

    // 行列をクリア（単位行列に）
    void Identity();

    // 変換行列を構成
    void Translate(float tx, float ty);
    void Rotate(float angleRad);
    void Scale(float sx, float sy);

    // ベクトルとの乗算
    CVector2 operator*(const CVector2& v) const;

    // 行列同士の乗算
    CMatrix2 operator*(const CMatrix2& rhs) const;

    // float配列を返す（4x4へ拡張して返す）
    const float* M() const;

    float Get(int row, int col) const { return m[row][col]; }

private:
    float m[3][3];        // 3×3 行列
    mutable float mGL[16]; // OpenGL用 4×4行列（行優先）
};
#endif