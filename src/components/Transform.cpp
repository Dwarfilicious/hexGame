/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "math.hpp"
#include "Transform.hpp"

Transform::Transform(Vector3 position, Quaternion rotation, float scale)
    : position(position), rotation(rotation), scale(scale) {}

Matrix4 Transform::getMatrix() const {
    Matrix4 translation = convertToTranslationMatrix(position);
    Matrix4 rotationMatrix = convertToRotationMatrix(rotation);
    Matrix4 scaleMatrix = convertToScalingMatrix(Vector3(scale, scale, scale));

    return translation * rotationMatrix * scaleMatrix;
}
