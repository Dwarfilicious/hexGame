/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "math.hpp"
#include "Camera.hpp"

#include <cmath>

Camera::Camera(Transform transform, float fov, float near, float far)
    : transform(transform), fov(fov), near(near), far(far) {}

void Camera::setTransform(const Transform &transform) {
    this->transform = transform;
}

const Transform &Camera::getTransform() const {
    return transform;
}

float Camera::getCameraVelocity() const {
    return cameraVelocity;
}

void Camera::move(const Vector3& direction) {
    transform.position += direction;
}

void Camera::rotate(const Quaternion& rotation) {
    transform.rotation += rotation;
}

Matrix4 Camera::getProjectionMatrix() const {
    Matrix4 projection;
    float aspectRatio = 16.0f / 9.0f;
    float fovInRadians = fov * M_PI / 180.0f;
    float f = 1.0f / std::tan(fovInRadians / 2.0f);
    projection.data[0] = f / aspectRatio;
    projection.data[5] = f;
    projection.data[10] = -(far + near) / (far - near);
    projection.data[11] = -1.0f;
    projection.data[14] = -2.0f * far * near / (far - near);
    return projection;
}

Matrix4 Camera::getViewMatrix() const {
    Matrix4 rotationMatrix = convertToRotationMatrix(transform.rotation);

    Matrix4 translationMatrix = Matrix4::identity();
    translationMatrix.data[12] = -transform.position.x;
    translationMatrix.data[13] = -transform.position.y;
    translationMatrix.data[14] = -transform.position.z;

    Matrix4 viewMatrix = translationMatrix * rotationMatrix;

    return viewMatrix;
}

Ray Camera::ndcToRay(const Vector3 &ndc) const {
    // Step 1 & 2: Convert to Clip Coordinates and then to Eye Coordinates
    Vector4 clipCoords(ndc.x, ndc.y, -1.0f, 1.0f);
    Matrix4 inverseProjectionMatrix = Matrix4::inverse(getProjectionMatrix());
    Vector4 eyeCoords = inverseProjectionMatrix * clipCoords;
    eyeCoords.z = -1.0f; eyeCoords.w = 0.0f;

    // Step 3: Convert to World Coordinates
    Matrix4 inverseViewMatrix = Matrix4::inverse(getViewMatrix());
    Vector4 rayWorld = inverseViewMatrix * eyeCoords;
    Vector3 rayDirection(rayWorld.x, rayWorld.y, rayWorld.z);
    rayDirection.normalize();

    return Ray(transform.position, rayDirection);
}
