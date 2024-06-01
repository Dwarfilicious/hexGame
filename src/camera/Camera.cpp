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

void Camera::move(const Vector3& direction) {
    transform.position += direction;
}

void Camera::rotate(const Quaternion& rotation) {
    transform.rotation += rotation;
}

Matrix4 Camera::getProjectionMatrix(int windowWidth, int windowHeight) const {
    Matrix4 projection;
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
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
