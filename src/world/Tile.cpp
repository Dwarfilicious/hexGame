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

    TileType type = getRandomTileType();
    Color color = tileTypeToColor[type];

    Vertex centerVertex = Vertex(center, color);
    mesh.addVertex(centerVertex);

    float angle = -M_PI / 2.0f;
    for (int i = 0; i < 6; i++) {
        Vertex vertex = Vertex(Vector3(center.x + radius * cos(angle),
                                       center.y + radius * sin(angle),
                                       center.z),
                               color);
        mesh.addVertex(vertex);
        angle += 2 * M_PI / 6;
    }

    for (int i = 1; i <= 6; i++) {
        mesh.addIndex(0);
        mesh.addIndex(i);
        mesh.addIndex(i % 6 + 1);
    }
}
