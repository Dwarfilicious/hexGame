/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Entity.hpp"

Entity::Entity(Transform transform)
    : transform(transform) {}

const Transform& Entity::getTransform() const {
    return transform;
}

void Entity::setTransform(const Transform& transform) {
    this->transform = transform;
}

const Mesh& Entity::getMesh() const {
    return mesh;
}
