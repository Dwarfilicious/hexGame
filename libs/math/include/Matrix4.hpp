/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Matrix4 class for storing
 * 4x4 matrices. The matrix is in column-major order. */

#pragma once

class Matrix4 {
public:
    float data[16];

    Matrix4();

    Matrix4 operator*(const Matrix4& other) const;
    Matrix4& operator*=(const Matrix4& other);

    static Matrix4 identity();
    static Matrix4 inverse(const Matrix4& matrix);
};
