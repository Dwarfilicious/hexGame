/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "math.hpp"

Vector3 operator*(float scalar, const Vector3& vector) {
    return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

float dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3& a, const Vector3& b) {
    return Vector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vector3 operator*(const Quaternion& q, const Vector3& v) {
    Vector3 u(q.x, q.y, q.z);
    float s = q.w;

    return 2.0f * dot(u, v) * u
        + (s * s - dot(u, u)) * v
        + 2.0f * s * cross(u, v);
}

Matrix4 convertToTranslationMatrix(const Vector3& translation) {
    Matrix4 result = Matrix4::identity();
    result.data[12] = translation.x;
    result.data[13] = translation.y;
    result.data[14] = translation.z;
    return result;
}

Matrix4 convertToRotationMatrix(const Quaternion& rotation) {
    return rotation.getMatrix();
}

Matrix4 convertToScalingMatrix(const Vector3& scale) {
    Matrix4 result = Matrix4::identity();
    result.data[0] = scale.x;
    result.data[5] = scale.y;
    result.data[10] = scale.z;
    return result;
}
