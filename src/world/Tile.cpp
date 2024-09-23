/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Tile.hpp"
#include "Vertex.hpp"
#include "Transform.hpp"
#include "Quaternion.hpp"
#include "Color.hpp"

#include <cmath>

Tile::Tile(Vector3 center, int q, int r, TileType tileType)
: Entity(Transform(center, Quaternion(), 1.0f)), q(q), r(r), tileType(tileType) {
    mesh = Mesh();

    Color color = tileTypeToColor[tileType];

    Vertex centerVertex = Vertex(Vector3(0, 0, 0), color);
    mesh.addVertex(centerVertex);

    float angle = -M_PI / 2.0f;
    for (int i = 0; i < 6; i++) {
        Vertex vertex = Vertex(Vector3(cos(angle),
                                       sin(angle),
                                       0),
                               color);
        mesh.addVertex(vertex);
        angle += M_PI / 3.0f;
    }

    for (int i = 1; i <= 6; i++) {
        mesh.addIndex(0);
        mesh.addIndex(i);
        mesh.addIndex(i % 6 + 1);
    }
}

const int Tile::getQ() const {
    return q;
}

const int Tile::getR() const {
    return r;
}

const Color Tile::getColor() const {
    return tileTypeToColor[tileType];
}

const TileType Tile::getTileType() const {
    return tileType;
}

void Tile::setQ(int q) {
    this->q = q;
}

void Tile::setR(int r) {
    this->r = r;
}

void Tile::setColor(const Color& color) {
    mesh.setColor(color);
}

void Tile::setTileType(TileType tileType) {
    this->tileType = tileType;
    mesh.setColor(tileTypeToColor[tileType]);
}
