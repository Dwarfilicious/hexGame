/* Author: Bas Zoeteman
 * Date of creation: 29-06-2024
 * Contains the Vector4 class for storing
 * 4-dimensional vectors. */

#pragma once

class Vector4 {
public:
    float x, y, z, w;

    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator*(float scalar) const;
    Vector4 operator/(float scalar) const;
    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*=(float scalar);
    Vector4& operator/=(float scalar);
    float dot(const Vector4& other) const;

    float magnitude() const;
    Vector4 normalized() const;

    void normalize();

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;
};
