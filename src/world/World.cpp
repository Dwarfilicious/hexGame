/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "World.hpp"
#include "Tile.hpp"

#include <cmath>
#include <utility>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

std::pair<float, float> qrToXY(int q, int r) {
    float tileWidth = std::sqrt(3.0f);
    float tileHeight = 2.0f;

    float x = q * tileWidth + (r % 2) * (tileWidth / 2.0f);
    float y = r * tileHeight * 0.75f;

    return std::make_pair(x, y);
}

World::World(int q, int r)
: q(q), r(r) {}

World World::randomMap(int q, int r) {
    World world(q, r);

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            std::pair<float, float> xy = qrToXY(i, j);
            float x = xy.first;
            float y = xy.second;
            world.entityContainer.addEntity(std::make_unique<Tile>(Vector3(x, y, 0), i, j));
        }
    }

    return world;
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

void World::exportToFile(const std::string& filename) const {
    nlohmann::json json;
    json["q"] = q;
    json["r"] = r;
    for (const auto& entity : entityContainer.getEntities()) {
        Tile* tile = dynamic_cast<Tile*>(entity.get());
        if (tile != nullptr) {
            nlohmann::json tileJson;
            tileJson["q"] = tile->q;
            tileJson["r"] = tile->r;
            tileJson["tileType"] = tile->getTileType();
            json["tiles"].push_back(tileJson);
        }
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << json.dump(4);
        file.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

World World::importFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    nlohmann::json json;
    file >> json;
    file.close();

    int q = json["q"];
    int r = json["r"];
    World world(q, r);

    for (const auto& tileJson : json["tiles"]) {
        int q = tileJson["q"];
        int r = tileJson["r"];
        std::pair<float, float> xy = qrToXY(q, r);
        Vector3 position(xy.first, xy.second, 0.0f);
        TileType tileType = tileJson["tileType"];
        Tile tile(position, q, r);
        tile.setTileType(tileType);
        world.entityContainer.addEntity(std::make_unique<Tile>(tile));
    }

    return world;
}
