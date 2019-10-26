#include "Pipeline.h"

#include <math.h>

Pipeline::Pipeline()
: _scale(1.0f, 1.0f, 1.0f)
, _rotation(0.0f, 0.0f, 0.0f)
, _worldPos(0.0f, 0.0f, 0.0f)
, _proj(10, 1.0f, 1024, 768, 45.0f)
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

    //world
    AssembleRotationMatrix(Mrotate, _rotation);
    AssembleTranlationMatrix(Mtranslate, _worldPos);
    AssembleScaleMatrix(Mscale, _scale);

    //Camera
    Matrix4f camRot(1.0f), camTransl(1.0f), Mperspective(1.0f);
    AssembleCameraTransform(camRot, _camTarget, _camUp);
    AssembleTranlationMatrix(camTransl, _camPos);
    AssembleProjectionMatrix(Mperspective, _proj);

    _transformation = Mperspective * camTransl * camRot * Mtranslate * Mrotate *  Mscale;
    //_transformation = Mtranslate * Mrotate *  Mscale;
    return &_transformation;
}

void Pipeline::SetCamera(const Vector3f& pos, const Vector3f& target, const Vector3f& up)
{
    _camPos = pos;
    _camTarget = target;
    _camUp = up;
}

void Pipeline::AssembleScaleMatrix(Matrix4f& scale, const Vector3f& sc)
{
    scale.m[0][0] = sc.x; scale.m[1][1] = sc.y; scale.m[2][2] = sc.z;
}

void Pipeline::AssembleRotationMatrix(Matrix4f& rotation, const Vector3f& rot)
{
    Matrix4f mRotX(1.0f), mRotY(1.0f), mRotZ(1.0f);

    float rX = (float)TO_RADIANS(rot.x);
    float rY = (float)TO_RADIANS(rot.y);
    float rZ = (float)TO_RADIANS(rot.z);

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

    rotation = mRotZ * mRotY * mRotX;
}

void Pipeline::AssembleProjectionMatrix(Matrix4f& projection, const SProjection& proj)
{
    const float ar = (float) proj.m_width / proj.m_height;
    const float zNear = proj.m_zNear;
    const float zFar = proj.m_zFar;
    const float zRange = zNear - zFar;
    float tanHalfFov = tanf(TO_RADIANS(proj.m_fov * 0.5f));

    projection.m[0][0] = 1.0f / (tanHalfFov * ar);
    projection.m[0][1] = 0.0f;
    projection.m[0][2] = 0.0f;
    projection.m[0][3] = 0.0f;

    projection.m[1][0] = 0.0f;
    projection.m[1][1] = 1.0f / tanHalfFov;
    projection.m[1][2] = 0.0f;
    projection.m[1][3] = 0.0f;

    projection.m[2][0] = 0.0f;
    projection.m[2][1] = 0.0f;
    projection.m[2][2] = (-zNear - zFar) / zRange;
    projection.m[2][3] = 2.0f * zFar * zNear / zRange;

    projection.m[3][0] = 0.0f;
    projection.m[3][1] = 0.0f;
    projection.m[3][2] = 1.0f;
    projection.m[3][3] = 0.0f;
}

void Pipeline::AssembleTranlationMatrix(Matrix4f& translation, const Vector3f& pos)
{
    translation.m[0][3] = pos.x;  translation.m[1][3] = pos.y;  translation.m[2][3] = pos.z;
}

void Pipeline::AssembleCameraTransform(Matrix4f& camT, const Vector3f& target, const Vector3f& Up)
{
    //Front
    Vector3f N = target;
    N.Normalize();

    //Right
    Vector3f U = Up;
    U = U.Cross(target);
    U.Normalize();

    //Up
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
