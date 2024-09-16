/* Author: Bas Zoeteman
 * Date of creation: 16-09-2024 */

#include "RayCast.hpp"

const Vector3 Ray::rayCastToXYPlane(float z) const {
    float t = (z - origin.z) / direction.z;
    return origin + direction * t;
}
