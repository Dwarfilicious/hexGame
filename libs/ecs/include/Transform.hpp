/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a Transform class for holding
 * the transform of entities. */

#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"

class Transform {
public:
    Vector3 position;
    Quaternion rotation;
    float scale;

    Transform(Vector3 position = Vector3(), Quaternion rotation = Quaternion(), float scale = 1.0f);

    Vector3 transformPoint(const Vector3& point) const;

    Matrix4 getMatrix() const;
};
