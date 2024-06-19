/* Author: Bas Zoeteman
 * Date of creation: 22-05-2024 */

#include "TileTypes.hpp"

#include <cstdlib>
#include <ctime>

void seedRandom() {
    srand(time(nullptr));
}

auto dummy = (seedRandom(), 0);

TileType getRandomTileType() {
    return static_cast<TileType>(rand() % static_cast<int> (TileType::COUNT));
}

std::map<TileType, Color> tileTypeToColor = {
    {TileType::OCEAN, Color(0.0f, 0.0f, 1.0f)},
    {TileType::COAST, Color(0.5f, 0.8f, 1.0f)},
    {TileType::PLAINS, Color(0.8f, 0.8f, 0.0f)},
    {TileType::GRASSLAND, Color(0.0f, 1.0f, 0.0f)},
    {TileType::HILLS, Color(0.5f, 0.3f, 0.0f)},
    {TileType::FOREST, Color(0.0f, 0.5f, 0.0f)},
    {TileType::JUNGLE, Color(0.0f, 0.3f, 0.0f)},
    {TileType::MOUNTAIN, Color(0.5f, 0.5f, 0.5f)},
    {TileType::DESERT, Color(1.0f, 1.0f, 0.0f)},
    {TileType::TUNDRA, Color(0.8f, 0.8f, 0.8f)},
    {TileType::SNOW, Color(1.0f, 1.0f, 1.0f)}
};
