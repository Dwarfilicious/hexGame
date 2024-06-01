/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Vertex.hpp"

Vertex::Vertex(Vector3 position, Color color)
    : position(position), color(color) {}

const Vector3& Vertex::getPosition() const {
    return position;
}

const Color& Vertex::getColor() const {
    return color;
}
