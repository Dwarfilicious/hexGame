/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "World.hpp"
#include "Tile.hpp"

#include <cmath>
#include <utility>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <nlohmann/json.hpp>

std::pair<float, float> qrToXY(int q, int r) {
    float tileWidth = std::sqrt(3.0f);
    float tileHeight = 2.0f;

    float x = q * tileWidth + r * (tileWidth / 2.0f);
    float y = r * tileHeight * 0.75f;

    return std::make_pair(x, y);
}

World::World(int q, int r)
: q(q), r(r) {}

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
            tileJson["q"] = tile->getQ();
            tileJson["r"] = tile->getR();
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
        Tile tile(position, q, r, tileType);
        world.entityContainer.addEntity(std::make_unique<Tile>(tile));
    }

    return world;
}

World World::randomMap(int q, int r) {
    World world(q, r);

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            std::pair<float, float> xy = qrToXY(i, j);
            float x = xy.first;
            float y = xy.second;
            world.entityContainer.addEntity(std::make_unique<Tile>(Vector3(x, y, 0), i, j, getRandomTileType()));
        }
    }

    return world;
}

#define WATER_BORDER_RANGE 3
#define INIT_POS_MARGIN 5
#define PATH_LENGTH_MAX 64

World World::pangaeaMap(int q, int r) {
    World world(q, r);
    int numTiles = q * r;
    float desiredLandMass = 0.3f;

    int totalLandMass = 0;
    int geographyMap[q][r];
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            geographyMap[i][j] = 0;
        }
    }

    int stencilMap[q][r];
    while ((float) totalLandMass / numTiles < desiredLandMass) {
        for (int i = 0; i < q; i++) {
            for (int j = 0; j < r; j++) {
                stencilMap[i][j] = 0;
            }
        }

        int pathLength = (rand() % PATH_LENGTH_MAX) + 1;

        int i = rand() % (q - 2 * INIT_POS_MARGIN) + INIT_POS_MARGIN;
        int j = rand() % (r - 2 * INIT_POS_MARGIN) + INIT_POS_MARGIN;
        while (pathLength > 0) {
            if (i < 0 + WATER_BORDER_RANGE || i >= q - 1 - WATER_BORDER_RANGE || j < 0 + WATER_BORDER_RANGE || j >= r - 1 - WATER_BORDER_RANGE) {
                break;
            }

            stencilMap[i][j] = 1;
            stencilMap[i + 1][j] = 1;
            stencilMap[i][j + 1] = 1;

            int direction = rand() % 6;
            switch (direction) {
                case 0:
                    i++;
                    break;
                case 1:
                    j++;
                    break;
                case 2:
                    i--;
                    j++;
                    break;
                case 3:
                    i--;
                    break;
                case 4:
                    j--;
                    break;
                case 5:
                    i++;
                    j--;
                    break;
            }
        }

        for (int i = 0; i < q; i++) {
            for (int j = 0; j < r; j++) {
                if (geographyMap[i][j] == 0 && stencilMap[i][j] == 1) {
                    totalLandMass++;
                }
                geographyMap[i][j] += stencilMap[i][j];
            }
        }
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < r; j++) {
            std::pair<float, float> xy = qrToXY(i, j);
            float x = xy.first;
            float y = xy.second;
            TileType tileType = geographyMap[i][j] == 0 ? TileType::OCEAN : TileType::GRASSLAND;
            world.entityContainer.addEntity(std::make_unique<Tile>(Vector3(x, y, 0), i, j, tileType));
        }
    }

    return world;
}
