/* Author: Bas Zoeteman
 * Date of creation: 22-05-2024
 * Contains an enumeration class for tile types. */

#pragma once

#include "Color.hpp"

#include <map>

enum class TileType {
    WATER = 0,
    GRASSLAND = 1,
    HILLS = 2,
    FOREST = 3,
    MOUNTAIN = 4,
    COUNT
};

TileType getRandomTileType();

extern std::map<TileType, Color> tileTypeToColor;
