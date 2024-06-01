/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a HexagonGrid class to hold the information
 * of an entire grid of hexagons using axial coordinates. */

#pragma once

#include "Entity.hpp"

#include <vector>
#include <memory>

class World {
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    World(int q, int r, float tileRadius = 1.0f);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    void addEntity(std::unique_ptr<Entity> entity);
};
