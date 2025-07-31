#ifndef CMATRIX2_H
#define CMATRIX2_H

class CVector2;


class CMatrix2
{
public:
    CMatrix2();

    // �s����N���A�i�P�ʍs��Ɂj
    void Identity();

    // �ϊ��s����\��
    void Translate(float tx, float ty);
    void Rotate(float angleRad);
    void Scale(float sx, float sy);

    // �x�N�g���Ƃ̏�Z
    CVector2 operator*(const CVector2& v) const;

    // �s�񓯎m�̏�Z
    CMatrix2 operator*(const CMatrix2& rhs) const;

    // float�z���Ԃ��i4x4�֊g�����ĕԂ��j
    const float* M() const;

    float Get(int row, int col) const { return m[row][col]; }

private:
    float m[3][3];        // 3�~3 �s��
    mutable float mGL[16]; // OpenGL�p 4�~4�s��i�s�D��j
};
#endif