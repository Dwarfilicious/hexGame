/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a HexagonGrid class to hold the information
 * of an entire grid of hexagons using axial coordinates. */

#pragma once

#include "EntityContainer.hpp"
#include "Tile.hpp"

#include <vector>
#include <memory>

class World {
private:
    EntityContainer entityContainer;
    int q, r;
    float width, height;

public:
    World(int q, int r);
    static World randomMap(int q, int r);

    Tile* getTileAt(Vector3 worldPosition) const;

    const EntityContainer& getEntityContainer() const;
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    float getWidth() const;
    float getHeight() const;

    void exportToFile(const std::string& filename) const;
    static World importFromFile(const std::string& filename);
};
