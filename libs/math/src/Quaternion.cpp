/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Quaternion.hpp"

#include <cmath>

Quaternion::Quaternion(float w, float x, float y, float z)
        : w(w), x(x), y(y), z(z) {}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion Quaternion::operator/(float scalar) const {
    return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
}

Quaternion& Quaternion::operator+=(const Quaternion& other) {
    w += other.w;
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other) {
    w -= other.w;
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Quaternion& Quaternion::operator*=(float scalar) {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Quaternion& Quaternion::operator/=(float scalar) {
    w /= scalar;
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

float Quaternion::magnitude() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::normalized() const {
    float magnitude = this->magnitude();
    return Quaternion(w / magnitude, x / magnitude, y / magnitude, z / magnitude);
}

Matrix4 Quaternion::getMatrix() const {
    Matrix4 matrix;
    matrix.data[0] = 2 * (w * w + x * x) - 1;
    matrix.data[1] = 2.0f * (x * y + w * z);
    matrix.data[2] = 2.0f * (x * z - w * y);
    matrix.data[3] = 0.0f;
    matrix.data[4] = 2.0f * (x * y - w * z);
    matrix.data[5] = 2.0f * (w * w + y * y) - 1;
    matrix.data[6] = 2.0f * (y * z + w * x);
    matrix.data[7] = 0.0f;
    matrix.data[8] = 2.0f * (x * z + w * y);
    matrix.data[9] = 2.0f * (y * z - w * x);
    matrix.data[10] = 2.0f * (w * w + z * z) - 1;
    matrix.data[11] = 0.0f;
    matrix.data[12] = 0.0f;
    matrix.data[13] = 0.0f;
    matrix.data[14] = 0.0f;
    matrix.data[15] = 1.0f;
    return matrix;
}

void Quaternion::normalize() {
    float magnitude = this->magnitude();
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

bool Quaternion::operator==(const Quaternion& other) const {
    return w == other.w && x == other.x && y == other.y && z == other.z;
}

bool Quaternion::operator!=(const Quaternion& other) const {
    return !(*this == other);
}
