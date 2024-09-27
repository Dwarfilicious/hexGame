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

std::pair<float, float> uvToQR(int u, int v) {
    int q = u - (v / 2);
    int r = v;
    return std::make_pair(q, r);
}

std::pair<int, int> qrToUV(int q, int r) {
    int u = q + (r / 2);
    int v = r;
    return std::make_pair(u, v);
}

std::pair<float, float> uvToXY(int u, int v) {
    std::pair<int, int> qr = uvToQR(u, v);
    return qrToXY(qr.first, qr.second);
}

World::World(int u, int v)
: u(u), v(v) {}

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
    json["u"] = u;
    json["v"] = v;
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

    int u = json["u"];
    int v = json["v"];
    World world(u, v);

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

#define WATER_BORDER_RANGE 3
#define INIT_POS_MARGIN 5
#define PATH_LENGTH_MIN 10
#define PATH_LENGTH_MAX 64

World World::randomMap(int u, int v) {
    World world(u, v);
    int numTiles = u * v;
    float desiredLandMass = 0.3f;

    int totalLandMass = 0;
    int geographyMap[u][v];
    for (int i = 0; i < u; i++) {
        for (int j = 0; j < v; j++) {
            geographyMap[i][j] = 0;
        }
    }

    int stencilMap[u][v];
    while ((float) totalLandMass / numTiles < desiredLandMass) {
        for (int i = 0; i < u; i++) {
            for (int j = 0; j < v; j++) {
                stencilMap[i][j] = 0;
            }
        }

        int pathLength = (rand() % PATH_LENGTH_MAX - (PATH_LENGTH_MIN - 1)) + PATH_LENGTH_MIN;

        int i = rand() % (u - 2 * INIT_POS_MARGIN) + INIT_POS_MARGIN;
        int j = rand() % (v - 2 * INIT_POS_MARGIN) + INIT_POS_MARGIN;

        while (pathLength > 0) {
            pathLength--;

            // check boundaries in u,v
            if (i < 0 + WATER_BORDER_RANGE || i >= u - WATER_BORDER_RANGE) {
                break;
            }
            if (j < 0 + WATER_BORDER_RANGE || j >= v - WATER_BORDER_RANGE) {
                break;
            }

            // drawing based on q,r, but in u,v
            std::pair<int, int> qr = uvToQR(i, j);
            i = qr.first;
            j = qr.second;

            std::pair<int, int> brush = qrToUV(i, j);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i + 1, j);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i, j + 1);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i - 1, j + 1);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i - 1, j);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i, j - 1);
            stencilMap[brush.first][brush.second] = 1;

            brush = qrToUV(i + 1, j - 1);
            stencilMap[brush.first][brush.second] = 1;

            // movement in q,r
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

            std::pair<int, int> uv = qrToUV(i, j);
            i = uv.first;
            j = uv.second;
        }

        for (int i = 0; i < u; i++) {
            for (int j = 0; j < v; j++) {
                if (geographyMap[i][j] == 0 && stencilMap[i][j] == 1) {
                    totalLandMass++;
                }
                geographyMap[i][j] += stencilMap[i][j];
            }
        }
    }

    for (int i = 0; i < u; i++) {
        for (int j = 0; j < v; j++) {
            std::pair<float, float> xy = uvToXY(i, j);
            float x = xy.first;
            float y = xy.second;
            std::pair<int, int> qr = uvToQR(i, j);
            int q = qr.first;
            int r = qr.second;
            TileType tileType = geographyMap[i][j] == 0 ? TileType::OCEAN : TileType::GRASSLAND;
            world.entityContainer.addEntity(std::make_unique<Tile>(Vector3(x, y, 0), q, r, tileType));
        }
    }

    return world;
}
