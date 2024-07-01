/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Mesh.hpp"
#include <iostream>

bool rayIntersectsEdge2D(const Vector3& point, const Vector3& edgeStart, const Vector3& edgeEnd) {
    if ((point.y < edgeStart.y) != (point.y < edgeEnd.y)) {
        float xIntersect = edgeStart.x + (point.y - edgeStart.y) * (edgeEnd.x - edgeStart.x) / (edgeEnd.y - edgeStart.y);
        if (point.x < xIntersect) {
            return true;
        }
    }
    return false;
}

bool Mesh::contains2D(const Vector3& point, const Transform& transform) const {
    int intersections = 0;
    for (size_t i = 0; i < indices.size(); i += 3) {
        const Vertex& v0 = vertices[indices[i]];
        const Vertex& v1 = vertices[indices[i + 1]];
        const Vertex& v2 = vertices[indices[i + 2]];

        Vector3 p0 = transform.transformPoint(v0.position);
        Vector3 p1 = transform.transformPoint(v1.position);
        Vector3 p2 = transform.transformPoint(v2.position);

        if (rayIntersectsEdge2D(point, p0, p1)) intersections++;
        if (rayIntersectsEdge2D(point, p1, p2)) intersections++;
        if (rayIntersectsEdge2D(point, p2, p0)) intersections++;
    }

    return (intersections % 2) != 0;
}

const std::vector<Vertex>& Mesh::getVertices() const {
    return vertices;
}

const std::vector<unsigned int>& Mesh::getIndices() const {
    return indices;
}

void Mesh::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

void Mesh::addIndex(unsigned int index) {
    indices.push_back(index);
}

void Mesh::clear() {
    vertices.clear();
    indices.clear();
}

bool Mesh::isEmpty() const {
    return vertices.empty() && indices.empty();
}

size_t Mesh::getVertexCount() const {
    return vertices.size();
}

size_t Mesh::getIndexCount() const {
    return indices.size();
}

void Mesh::setColor(const Color& color) {
    for (Vertex& vertex : vertices) {
        vertex.color = color;
    }
}
