/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Entity.hpp"

Entity::Entity(Transform transform)
    : transform(transform) {}

bool Entity::contains2D(const Vector3& point) const {
    return mesh.contains2D(point, transform);
}

const Transform& Entity::getTransform() const {
    return transform;
}

void Entity::setTransform(const Transform& transform) {
    this->transform = transform;
}

const Mesh& Entity::getMesh() const {
    return mesh;
}

void Entity::setColor(const Color& color) {
    mesh.setColor(color);
}
