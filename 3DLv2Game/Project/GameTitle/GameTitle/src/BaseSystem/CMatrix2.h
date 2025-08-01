#ifndef CMATRIX2_H
#define CMATRIX2_H

class CVector2;


class CMatrix2
{
public:
    CMatrix2();

    // sρπNAiPΚsρΙj
    void Identity();

    // Ο·sρπ\¬
    void Translate(float tx, float ty);
    void Rotate(float angleRad);
    void Scale(float sx, float sy);

    // xNgΖΜζZ
    CVector2 operator*(const CVector2& v) const;

    // sρ―mΜζZ
    CMatrix2 operator*(const CMatrix2& rhs) const;

    // floatzρπΤ·i4x4Φg£΅ΔΤ·j
    const float* M() const;

    float Get(int row, int col) const { return m[row][col]; }

private:
    float m[3][3];        // 3~3 sρ
    mutable float mGL[16]; // OpenGLp 4~4sρisDζj
};
#endif