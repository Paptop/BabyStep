#ifndef BABYSTEP2_MATH_3D_H
#define BABYSTEP2_MATH_3D_H

#include <math.h>

#define TO_RADIANS(x) ((x) * M_PI / 180.0f)
#define TO_DEGREE(x) ((x) * 180.0f / M_PI)

inline float fLerp(const float A, const float B, float fProgress)
{
    return (1.0f - fProgress)* A + (fProgress) * B;    
}

struct Vector3f
{
    float x,y,z;

    Vector3f(float xx, float yy, float zz)
    : x(xx)
    , y(yy)
    , z(zz)
    {
    }

    Vector3f()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    {
    }

    Vector3f Cross(const Vector3f& v) const
    {
        const float _x = y * v.z - z * v.y;
        const float _y = z * v.x - x * v.z;
        const float _z = x * v.y - y * v.x;

        return Vector3f(_x, _y, _z);
    }

    Vector3f& Normalize()
    {
        const float length = Length();

        x /= length;
        y /= length;
        z /= length;

        return *this;
    }

    float Length()
    {
        return sqrtf(x * x + y * y + z * z);
    }
};

struct Matrix4f
{
    float m[4][4];

    Matrix4f()
    {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                m[i][j] = 0.0f;
            }
        }
    }

    Matrix4f(float fValue)
    {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                if(i == j)
                {
                    m[i][j] = 1.0f;
                }
                else
                {
                    m[i][j] = 0.0f;
                }
            }
        }
    }

    inline Matrix4f operator*(const Matrix4f& right)
    {
        Matrix4f res;

        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                res.m[i][j] = m[i][0] * right.m[0][j] +
                              m[i][1] * right.m[1][j] +
                              m[i][2] * right.m[2][j] +
                              m[i][3] * right.m[3][j];

            }
        }

        return res;
    }

    void InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
    {
        Matrix4f camT;

        Vector3f N = Target;
        N.Normalize();

        Vector3f U = Up;
        U = U.Cross(Target);
        U.Normalize();

        Vector3f V = N.Cross(U);

        camT.m[0][0] = U.x;
        camT.m[0][1] = U.y;
        camT.m[0][2] = U.z;
        camT.m[0][3] = 0.0f;

        camT.m[1][0] = V.x;
        camT.m[1][1] = V.y;
        camT.m[1][2] = V.z;
        camT.m[1][3] = 0.0f;

        camT.m[2][0] = N.x;
        camT.m[2][1] = N.y;
        camT.m[2][2] = N.z;
        camT.m[2][3] = 0.0f;

        camT.m[3][0] = 0.0f;
        camT.m[3][1] = 0.0f;
        camT.m[3][2] = 0.0f;
        camT.m[3][3] = 1.0f;
    }
};

#endif
