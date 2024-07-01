/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Vertex class for storing
 * the position and color of a vertex. */

#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

class Vertex {
public:
    Vector3 position;
    Color color;

    Vertex(Vector3 position = Vector3(), Color color = Color());

    const Vector3& getPosition() const;
    const Color& getColor() const;
};
