/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Matrix4.hpp"

Matrix4::Matrix4() {
    for (int i = 0; i < 16; i++) {
        data[i] = 0.0f;
    }
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.data[i * 4 + j] += data[k * 4 + j] * other.data[i * 4 + k];
            }
        }
    }
    return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

Matrix4 Matrix4::identity() {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        result.data[i * 4 + i] = 1.0f;
    }
    return result;
}
