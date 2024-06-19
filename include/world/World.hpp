/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a HexagonGrid class to hold the information
 * of an entire grid of hexagons using axial coordinates. */

#pragma once

#include "EntityContainer.hpp"

#include <vector>
#include <memory>

class World {
private:
    EntityContainer entityContainer;

public:
    World(int q, int r, float tileRadius = 1.0f);

    const EntityContainer& getEntityContainer() const;
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
};
