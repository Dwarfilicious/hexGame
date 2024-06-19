/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains the Mesh class for storing
 * the vertices and indices of a mesh. */

#pragma once

#include <vector>

#include "Vector3.hpp"
#include "Vertex.hpp"

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Mesh() = default;

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    void addVertex(const Vertex& vertex);
    void addIndex(unsigned int index);
    void clear();

    bool isEmpty() const;
    size_t getVertexCount() const;
    size_t getIndexCount() const;
};
