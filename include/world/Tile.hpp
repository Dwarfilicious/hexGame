/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a Tile class to store the information of
 * a tile object. All tiles are drawn on the z plane. */

#pragma once

#include "TileTypes.hpp"
#include "Entity.hpp"
#include "Vector3.hpp"
#include "Mesh.hpp"
#include "Color.hpp"

#include <array>

class Tile : public Entity {
private:
    TileType tileType;

public:
    Tile(Vector3 center, float radius = 1.0f);

    const Color getColor() const;

    void setColor(const Color& color);
};
