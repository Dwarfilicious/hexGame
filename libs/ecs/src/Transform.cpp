/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "math.hpp"
#include "Transform.hpp"

Transform::Transform(Vector3 position, Quaternion rotation, float scale)
    : position(position), rotation(rotation), scale(scale) {}

Vector3 Transform::transformPoint(const Vector3& point) const {
    return rotation * (scale * point) + position;
}

Matrix4 Transform::getMatrix() const {
    Matrix4 translation = convertToTranslationMatrix(position);
    Matrix4 rotationMatrix = convertToRotationMatrix(rotation);
    Matrix4 scaleMatrix = convertToScalingMatrix(Vector3(scale, scale, scale));

    return translation * rotationMatrix * scaleMatrix;
}
