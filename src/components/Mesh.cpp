/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "Mesh.hpp"

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
