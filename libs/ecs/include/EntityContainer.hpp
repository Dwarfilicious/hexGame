/* Author: Bas Zoeteman
 * Date of creation: 19-06-2024
 * Contains an EntityContainer class to hold the information
 * of entities to render. */

#pragma once

#include "Entity.hpp"

#include <vector>
#include <memory>

class Entity; // Forward declaration

class EntityContainer {
public:
    void addEntity(std::unique_ptr<Entity> entity);
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

private:
    std::vector<std::unique_ptr<Entity>> entities;
};
