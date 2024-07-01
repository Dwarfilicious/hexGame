/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains an Entity class to hold the information
 * of an entity in the game world. */

#pragma once

#include "Mesh.hpp"
#include "Transform.hpp"

#include <stdexcept>

class Entity {
protected:
    Transform transform;
    Mesh mesh;

public:
    Entity(Transform transform = Transform());

    virtual ~Entity() = default;

    bool contains2D(const Vector3& point) const;

    const Transform& getTransform() const;
    void setTransform(const Transform& transform);

    const Mesh& getMesh() const;

    void setColor(const Color& color);
};
