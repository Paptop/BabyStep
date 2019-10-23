#include "Pipeline.h"

#include <math.h>

Pipeline::Pipeline()
: _scale(1.0f, 1.0f, 1.0f)
, _rotation(0.0f, 0.0f, 0.0f)
, _worldPos(0.0f, 0.0f, 0.0f)
{
}

void Pipeline::Scale(float ScaleX, float ScaleY, float ScaleZ)
{
    _scale.x = ScaleX; _scale.y = ScaleY; _scale.z = ScaleZ;
}

void Pipeline::WorldPos(float x, float y, float z)
{
    _worldPos.x = x; _worldPos.y = y; _worldPos.z = z;
}

void Pipeline::Rotate(float RotateX, float RotateY, float RotateZ)
{
    _rotation.x = RotateX; _rotation.y = RotateY; _rotation.z = RotateZ;
}

const Matrix4f* Pipeline::GetTrans()
{
    Matrix4f Mscale(1.0f), Mrotate(1.0f), Mtranslate(1.0f);
    AssembleRotationMatrix(Mrotate);
    AssembleTranlationMatrix(Mtranslate);
    AssembleScaleMatrix(Mscale);

    _transformation = Mtranslate * Mrotate *  Mscale;
    return &_transformation;
}

void Pipeline::AssembleScaleMatrix(Matrix4f& scale)
{
    scale.m[0][0] = _scale.x; scale.m[1][1] = _scale.y; scale.m[2][2] = _scale.z;
}

void Pipeline::AssembleRotationMatrix(Matrix4f& rotation)
{
    Matrix4f mRotX(1.0f), mRotY(1.0f), mRotZ(1.0f);

    float rX = (float)TO_RADIANS(_rotation.x);
    float rY = (float)TO_RADIANS(_rotation.y);
    float rZ = (float)TO_RADIANS(_rotation.z);

    mRotX.m[1][1] = cos(rX);
    mRotX.m[1][2] = -sin(rX);
    mRotX.m[2][1] = sin(rX);
    mRotX.m[2][2] = cos(rX);

    mRotY.m[0][0] = cos(rY);
    mRotY.m[0][2] = -sin(rY);
    mRotY.m[2][0] = sin(rY);
    mRotY.m[2][2] = cos(rY);

    mRotZ.m[0][0] = cos(rZ);
    mRotZ.m[0][1] = -sin(rZ);
    mRotZ.m[1][0] = sin(rZ);
    mRotZ.m[1][1] = cos(rZ);

    //world.m[0][0] = 1.0f; world.m[0][1] = 0.0f; world.m[0][2] = 0.0f; world.m[0][3] = 0.0f;
    //world.m[1][0] = 0.0f; world.m[1][1] = 1.0f; world.m[1][2] = 0.0f; world.m[1][3] = 0.0f;
    //world.m[2][0] = 0.0f; world.m[2][1] = 0.0f; world.m[2][2] = 1.0f; world.m[2][3] = 0.0f;
    //world.m[3][0] = 0.0f; world.m[3][1] = 0.0f; world.m[3][2] = 0.0f; world.m[3][3] = 1.0f;

    rotation = mRotZ * mRotY * mRotX;
}

void Pipeline::AssembleTranlationMatrix(Matrix4f& translation)
{
    translation.m[0][3] = _worldPos.x;  translation.m[1][3] = _worldPos.y;  translation.m[2][3] = _worldPos.z;
}
