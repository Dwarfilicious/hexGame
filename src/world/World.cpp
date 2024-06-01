/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "World.hpp"
#include "Tile.hpp"

#include <cmath>

World::World(int q, int r, float tileRadius) {
    float tileWidth = tileRadius * std::sqrt(3.0);
    float tileHeight = 2 * tileRadius;

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            float x = (tileWidth / 2.0f) * (i + (j / 2.0f));
            float y = (3.0f / 4.0f) * tileHeight * (j / 2.0f);
            entities.push_back(std::make_unique<Tile>(Vector3(x, y, 0), tileRadius));
        }
    }
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entities;
}

void World::addEntity(std::unique_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}
