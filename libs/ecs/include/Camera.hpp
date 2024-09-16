/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Camera class used for calculation
 * of the player perspective. */

#pragma once

#include "Transform.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"
#include "RayCast.hpp"

class Camera {
private:
    Transform transform;
    float fov, near, far;
    float cameraVelocity = 30.0f;

public:
    Camera(Transform transform, float fov = 103.0f, float near = 0.1f, float far = 100.0f);

    void setTransform(const Transform& transform);
    const Transform& getTransform() const;

    float getCameraVelocity() const;

    void move(const Vector3& direction);
    void rotate(const Quaternion& rotation);

    Matrix4 getProjectionMatrix() const;
    Matrix4 getViewMatrix() const;

    Ray ndcToRay(const Vector3& ndc) const;
};
