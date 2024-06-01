/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Camera class used for calculation
 * of the player perspective. */

#pragma once

#include "Transform.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"

class Camera {
private:
    Transform transform;
    float fov, near, far;

public:
    Camera(Transform transform, float fov = 103.0f, float near = 0.1f, float far = 100.0f);

    void setTransform(const Transform& transform);
    const Transform& getTransform() const;

    void move(const Vector3& direction);
    void rotate(const Quaternion& rotation);

    Matrix4 getProjectionMatrix(int windowWidth, int windowHeight) const;
    Matrix4 getViewMatrix() const;
};
