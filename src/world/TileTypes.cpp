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
    {TileType::WATER, Color(0.2f, 0.6f, 1.0f)},
    {TileType::GRASSLAND, Color(0.0f, 1.0f, 0.0f)},
    {TileType::HILLS, Color(0.5f, 0.3f, 0.0f)},
    {TileType::FOREST, Color(0.0f, 0.5f, 0.0f)},
    {TileType::MOUNTAIN, Color(0.7f, 0.7f, 0.7f)},
};
