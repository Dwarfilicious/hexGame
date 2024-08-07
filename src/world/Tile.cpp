/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Tile.hpp"
#include "Vertex.hpp"
#include "Transform.hpp"
#include "Quaternion.hpp"
#include "Color.hpp"

#include <cmath>

Tile::Tile(Vector3 center, int q, int r)
: Entity(Transform(center, Quaternion(), 1.0f)), q(q), r(r) {
    mesh = Mesh();

    tileType = getRandomTileType();
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

const Color Tile::getColor() const {
    return tileTypeToColor[tileType];
}

const TileType Tile::getTileType() const {
    return tileType;
}

void Tile::setColor(const Color& color) {
    mesh.setColor(color);
}

void Tile::setTileType(TileType tileType) {
    this->tileType = tileType;
    mesh.setColor(tileTypeToColor[tileType]);
}
