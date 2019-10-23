#ifndef BABYSTEP2_PIPELINE_H
#define BABYSTEP2_PIPELINE_H

#include "math_3d.h"

class Pipeline
{
public:
    Pipeline();
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    const Matrix4f* GetTrans();

private:
    void AssembleScaleMatrix(Matrix4f& scale);
    void AssembleRotationMatrix(Matrix4f& rotation);
    void AssembleTranlationMatrix(Matrix4f& translation);

private:
    Vector3f _scale;
    Vector3f _worldPos;
    Vector3f _rotation;
    Matrix4f _transformation;
};

#endif //BABYSTEP2_PIPELINE_H
