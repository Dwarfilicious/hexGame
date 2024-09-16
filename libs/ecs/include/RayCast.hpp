/* Author: Bas Zoeteman
 * Date of creation: 16-09-2024
 * Ray class and ray cast functions */

#pragma once

#include "Vector3.hpp"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {}

    const Vector3 rayCastToXYPlane(float z) const;
};
