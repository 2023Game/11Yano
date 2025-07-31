#include "CMatrix2.h"
#include <cmath>

CMatrix2::CMatrix2() 
{
    Identity();
}

void CMatrix2::Identity() 
{
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
}

void CMatrix2::Translate(float tx, float ty) 
{
    CMatrix2 t;
    t.m[0][2] = tx;
    t.m[1][2] = ty;
    *this = *this * t;
}

void CMatrix2::Rotate(float angleRad) 
{
    float c = cosf(angleRad);
    float s = sinf(angleRad);
    CMatrix2 r;
    r.m[0][0] = c;  r.m[0][1] = -s;
    r.m[1][0] = s;  r.m[1][1] = c;
    *this = *this * r;
}

void CMatrix2::Scale(float sx, float sy) 
{
    CMatrix2 s;
    s.m[0][0] = sx;
    s.m[1][1] = sy;
    *this = *this * s;
}

CVector2 CMatrix2::operator*(const CVector2& v) const 
{
    float x = m[0][0] * v.X() + m[0][1] * v.Y() + m[0][2];
    float y = m[1][0] * v.X() + m[1][1] * v.Y() + m[1][2];
    return CVector2(x, y);
}

CMatrix2 CMatrix2::operator*(const CMatrix2& rhs) const 
{
    CMatrix2 result;
    for (int row = 0; row < 3; ++row) 
    {
        for (int col = 0; col < 3; ++col) 
        {
            result.m[row][col] =
                m[row][0] * rhs.m[0][col] +
                m[row][1] * rhs.m[1][col] +
                m[row][2] * rhs.m[2][col];
        }
    }
    return result;
}

const float* CMatrix2::M() const 
{
    // 2Ds—ñ‚ð4x4‚É“WŠJi—ñ—Dæj
    for (int i = 0; i < 16; ++i) mGL[i] = 0.0f;
    mGL[0] = m[0][0]; mGL[4] = m[0][1]; mGL[12] = m[0][2];
    mGL[1] = m[1][0]; mGL[5] = m[1][1]; mGL[13] = m[1][2];
    mGL[10] = 1.0f; 
    mGL[15] = 1.0f; 

    return mGL;
}
