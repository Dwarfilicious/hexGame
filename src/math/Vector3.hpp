/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Vector3 class for storing
 * 3-dimensional vectors. */

#pragma once

class Vector3 {
public:
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);
    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;

    float Magnitude() const;
    Vector3 Normalized() const;

    void Normalize();

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
};
