/* Author: Bas Zoeteman
 * Date of creation: 22-05-2024
 * Contains an enumeration class for tile types. */

#pragma once

#include "Color.hpp"

#include <map>

enum class TileType {
    OCEAN = 0,
    COAST = 1,
    GRASSLAND = 2,
    HILLS = 3,
    FOREST = 4,
    MOUNTAIN = 5,
    COUNT
};

TileType getRandomTileType();

extern std::map<TileType, Color> tileTypeToColor;
