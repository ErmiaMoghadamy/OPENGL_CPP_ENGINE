#pragma once
#include "config.h"
#include "IndexBuffer.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class Mesh {
public:
    Mesh(
        std::vector<Vertex>& vertices,
        std::vector<unsigned int>& indices
    );
    ~Mesh();

    void draw() const;
    void bind() const;

private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;
};
