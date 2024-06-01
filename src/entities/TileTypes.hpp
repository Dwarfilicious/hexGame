/* Author: Bas Zoeteman
 * Date of creation: 22-05-2024
 * Contains an enumeration class for tile types. */

#pragma once

#include "Color.hpp"

#include <map>

enum class TileType {
    OCEAN = 0,
    COAST = 1,
    PLAINS = 2,
    GRASSLAND = 3,
    HILLS = 4,
    FOREST = 5,
    JUNGLE = 6,
    MOUNTAIN = 7,
    DESERT = 8,
    TUNDRA = 9,
    SNOW = 10,
    COUNT
};

TileType getRandomTileType();

extern std::map<TileType, Color> tileTypeToColor;
