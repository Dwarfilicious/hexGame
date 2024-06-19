/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * This code holds several essential mathematical equations
 * between different math class types. */

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"

Vector3 operator*(float scalar, const Vector3& vector);

float dot(const Vector3& a, const Vector3& b);
Vector3 cross(const Vector3& a, const Vector3& b);

Vector3 operator*(const Quaternion& rotation, const Vector3& vector);

Matrix4 convertToTranslationMatrix(const Vector3& translation);
Matrix4 convertToRotationMatrix(const Quaternion& rotation);
Matrix4 convertToScalingMatrix(const Vector3& scale);
