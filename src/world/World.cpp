/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "World.hpp"
#include "Tile.hpp"

#include <cmath>
#include <iostream>

World::World(int q, int r, float tileRadius) {
    float tileWidth = tileRadius * std::sqrt(3.0);
    float tileHeight = tileRadius * 2.0f;

    width = tileWidth * q;
    height = tileHeight * r;

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            float x = i * tileWidth + (j % 2) * (tileWidth / 2.0f);
            float y = j * tileHeight * 0.75f;
            entityContainer.addEntity(std::make_unique<Tile>(Vector3(x, y, 0), tileRadius));
        }
    }
}

Tile* World::getTileAt(Vector3 worldPosition) const {
    for (const auto& entity : entityContainer.getEntities()) {
        if (entity->contains2D(worldPosition)) {
            return dynamic_cast<Tile*>(entity.get());
        }
    }

    return nullptr;
}

const EntityContainer& World::getEntityContainer() const {
    return entityContainer;
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entityContainer.getEntities();
}

float World::getWidth() const {
    return width;
}

float World::getHeight() const {
    return height;
}
