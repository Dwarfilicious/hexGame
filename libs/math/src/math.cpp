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

Vector3 operator*(const Matrix4& matrix, const Vector3& vector) {
    Vector3 result = Vector3(
        matrix.data[0] * vector.x + matrix.data[4] * vector.y + matrix.data[8] * vector.z + matrix.data[12],
        matrix.data[1] * vector.x + matrix.data[5] * vector.y + matrix.data[9] * vector.z + matrix.data[13],
        matrix.data[2] * vector.x + matrix.data[6] * vector.y + matrix.data[10] * vector.z + matrix.data[14]
    );
    float w = matrix.data[3] * vector.x + matrix.data[7] * vector.y + matrix.data[11] * vector.z + matrix.data[15];

    return result / w;
}

Vector4 operator*(const Matrix4& matrix, const Vector4& vector) {
    return Vector4(
        matrix.data[0] * vector.x + matrix.data[4] * vector.y + matrix.data[8] * vector.z + matrix.data[12] * vector.w,
        matrix.data[1] * vector.x + matrix.data[5] * vector.y + matrix.data[9] * vector.z + matrix.data[13] * vector.w,
        matrix.data[2] * vector.x + matrix.data[6] * vector.y + matrix.data[10] * vector.z + matrix.data[14] * vector.w,
        matrix.data[3] * vector.x + matrix.data[7] * vector.y + matrix.data[11] * vector.z + matrix.data[15] * vector.w
    );
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
