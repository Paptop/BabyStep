#ifndef BABYSTEP2_PIPELINE_H
#define BABYSTEP2_PIPELINE_H

#include "math_3d.h"

struct SProjection
{
public:

    SProjection(float zFar, float zNear, int width, int height, float fov)
    : m_zFar(zFar)
    , m_zNear(zNear)
    , m_width(width)
    , m_height(height)
    , m_fov(fov)
    {
    }

    float m_zFar, m_zNear, m_fov;
    int m_width, m_height;
};

class Pipeline
{
public:
    Pipeline();
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    const Matrix4f* GetTrans();
    void SetCamera(const Vector3f& pos, const Vector3f& target, const Vector3f& Up);
    SProjection& GetProjection() { return _proj;}

private:
    void AssembleScaleMatrix(Matrix4f& scale, const Vector3f& sc);
    void AssembleRotationMatrix(Matrix4f& rotation, const Vector3f& rot);
    void AssembleTranlationMatrix(Matrix4f& translation, const Vector3f& pos);
    void AssembleProjectionMatrix(Matrix4f& projection, const SProjection& proj);
    void AssembleCameraTransform(Matrix4f& camT, const Vector3f& Target, const Vector3f& Up);

private:
    Vector3f        _scale;
    Vector3f        _worldPos;
    Vector3f        _rotation;

    Vector3f        _camPos;
    Vector3f        _camTarget;
    Vector3f        _camUp;

    Matrix4f        _transformation;
    SProjection     _proj;
};

#endif //BABYSTEP2_PIPELINE_H
