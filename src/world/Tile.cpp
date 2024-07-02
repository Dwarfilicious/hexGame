/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Tile.hpp"
#include "Vertex.hpp"
#include "Transform.hpp"
#include "Quaternion.hpp"
#include "Color.hpp"

#include <cmath>

Tile::Tile(Vector3 center, float radius)
    : Entity(Transform(center, Quaternion(), 1.0f)) {
    mesh = Mesh();

    tileType = getRandomTileType();
    Color color = tileTypeToColor[tileType];

    Vertex centerVertex = Vertex(Vector3(0, 0, 0), color);
    mesh.addVertex(centerVertex);

    float angle = -M_PI / 2.0f;
    for (int i = 0; i < 6; i++) {
        Vertex vertex = Vertex(Vector3(radius * cos(angle),
                                       radius * sin(angle),
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

void Tile::setColor(const Color& color) {
    mesh.setColor(color);
}
