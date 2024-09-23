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
    int q, r;
    TileType tileType;

public:
    Tile(Vector3 center, int q, int r, TileType tileType);

    const int getQ() const;
    const int getR() const;
    const Color getColor() const;
    const TileType getTileType() const;

    void setQ(int q);
    void setR(int r);
    void setColor(const Color& color);
    void setTileType(TileType tileType);
};
