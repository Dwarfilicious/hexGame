/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Quaternion class for storing
 * 4-dimensional rotation vectors.
 * Format: Q = w + xi + yj + zk. */

#pragma once

#include "Matrix4.hpp"

class Quaternion {
public:
    float w, x, y, z;

    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);

    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator-(const Quaternion& other) const;
    Quaternion operator*(float scalar) const;
    Quaternion operator/(float scalar) const;
    Quaternion& operator+=(const Quaternion& other);
    Quaternion& operator-=(const Quaternion& other);
    Quaternion& operator*=(float scalar);
    Quaternion& operator/=(float scalar);

    float magnitude() const;
    Quaternion normalized() const;
    Matrix4 getMatrix() const;

    void normalize();

    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;
};
