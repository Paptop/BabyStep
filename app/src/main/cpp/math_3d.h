#ifndef BABYSTEP2_MATH_3D_H
#define BABYSTEP2_MATH_3D_H

#include <math.h>

#define TO_RADIANS(x) ((x) * M_PI / 180.0f)
#define TO_DEGREE(x) ((x) * 180.0f / M_PI)

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
};

#endif
